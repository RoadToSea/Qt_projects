#include "TableWid.h"
#include "qtimer.h"
#include "ui_TableWid.h"
#include "config.h"
#include "sqliteoperator.h"

#include <AutoCloseDialog.h>
#include <qfile.h>


TableWid::TableWid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TableWid),m_curPage(1),m_totalPage(-1),m_lines(0),m_totalNum(0)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground, true); // 启用 QSS
    UIinit();

    connect(ui->exportBtn,&QPushButton::clicked,this,&TableWid::slot_exportData);

    m_timer = new QTimer();
    //开启定时器,1秒查询一次
    m_timer->start(1000);
}

TableWid::~TableWid()
{
    if(m_timer->isActive())
        m_timer->stop();
    delete ui;
}

void TableWid::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    int tableHeight = ui->tableWidget->height(); // 获取整个 QTableWidget 的高度
    int headerHeight = ui->tableWidget->horizontalHeader()->height(); // 表头高度
    int contentHeight = ui->tableWidget->viewport()->height();

    m_lines = contentHeight/30;
    qDebug()<<"可容纳的行数:"<<m_lines;

    //加载完后才连接信号,否则m_lines为0

    //获取输入框当前页数
    connect(ui->inputPage,&QLineEdit::textChanged,this,&TableWid::slot_curPage);
    //按钮点击上一页
    connect(ui->prePageBtn,&QPushButton::clicked,this,&TableWid::slot_prePage);
    //按钮点击下一页
    connect(ui->nextPageBtn,&QPushButton::clicked,this,&TableWid::slot_nextPage);
    //按钮点击首页
    connect(ui->firstPageBtn,&QPushButton::clicked,this,&TableWid::slot_firstPage);
    //按钮点击尾页
    connect(ui->lastPageBtn,&QPushButton::clicked,this,&TableWid::slot_lastPage);
    //每秒获取一次数据库表页数
    connect(m_timer,&QTimer::timeout,this,&TableWid::slot_getTotalPage);

    updateCurPage();
}

void TableWid::UIinit()
{

    QStringList header;
    header << "X轴" << "Y轴" << "Z轴" << "温度" << "湿度" << "大气压力" << "光照" << "动作标签";
    ui->tableWidget->setColumnCount(header.size()); // 设置列数
    ui->tableWidget->setHorizontalHeaderLabels(header); // 设置表头
    //设置表头高度
    ui->tableWidget->horizontalHeader()->setFixedHeight(HEADER_HEIGHT);
    //设置单元格高度
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(CELL_HEIGHT);
    // 隐藏行号
    ui->tableWidget->verticalHeader()->setVisible(false);
    // 设置列宽填满表格
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 创建一个 QFont 对象，设置字体大小和字体类型
    QFont font("Arial", 12);  // 字体为 Arial，大小为 11pt
    font.setWeight(QFont::Bold);
    // 应用字体到 QTableWidget
    ui->tableWidget->horizontalHeader()->setFont(font);
    //设置初始页数
    ui->totalPage->setText("0");


}

void TableWid::setCurPage(int page)
{
    m_curPage = page;
    ui->inputPage->setText(QString::number(m_curPage));
}

void TableWid::updateCurPage()
{
    if(m_curPage<=0)
        return;
    m_data = SqliteOperator::getInstance()->querydataById((m_curPage-1)*m_lines+1,m_curPage*m_lines);
    slot_receiveData(m_data);
}

void TableWid::slot_receiveData(QVector<QVector<QString>> &data)
{
    m_data = data;
    int rows = data.size();
    int columns = data[0].size();



    // 清空表格内容，但保留表头
    ui->tableWidget->setRowCount(0); // 清空现有行
    ui->tableWidget->setColumnCount(columns); // 确保列数匹配数据

    // 填充数据
    for (int row = 0; row < rows; ++row) {
        ui->tableWidget->insertRow(row); // 插入新行
        for (int column = 0; column < columns; ++column) {
            QTableWidgetItem *item = new QTableWidgetItem(data[row][column]);
            item->setTextAlignment(Qt::AlignCenter); // 数据居中对齐
            ui->tableWidget->setItem(row, column, item);
        }

    }
}

void TableWid::slot_curPage()
{
    QString content = ui->inputPage->text();
    // 使用正则表达式提取数字
    static QRegularExpression re("\\d+"); // 匹配一个或多个连续数字
    QRegularExpressionMatch match = re.match(content);

    if (match.hasMatch()) {
        QString numberOnly = match.captured(0); // 获取匹配的数字部分
        m_curPage = numberOnly.toInt(); // 转换为整数
        //qDebug() << "提取数字:" << numberOnly;
    } else {
        m_curPage = 1; // 如果没有匹配到数字，设置为默认值
        //qDebug() << "未找到数字，设置为 1";
    }

    //如果还没有获取总页数,直接返回
    if(m_totalPage==-1)
        return ;

    if(m_curPage>m_totalPage)
    {
        m_curPage = m_totalPage;
    }
    else if(m_curPage<1)
    {
        m_curPage =1;
    }
    //规范用户输入
    ui->inputPage->setText(QString::number(m_curPage));
    m_data = SqliteOperator::getInstance()->querydataById((m_curPage-1)*m_lines+1,m_curPage*m_lines);
    slot_receiveData(m_data);
}

void TableWid::slot_prePage()
{
    if(m_curPage<=1)
        return; 
    m_data = SqliteOperator::getInstance()->querydataById((m_curPage-2)*m_lines+1,(m_curPage-1)*m_lines);
    setCurPage(--m_curPage);
    //slot_receiveData(m_data);
}

void TableWid::slot_nextPage()
{
    if(m_curPage>=m_totalPage)
        return;
    m_data = SqliteOperator::getInstance()->querydataById((m_curPage)*m_lines+1,(m_curPage+1)*m_lines);
    setCurPage(++m_curPage);
    //slot_receiveData(m_data);
}

void TableWid::slot_firstPage()
{
    if(m_totalPage<=0)
        return;
    //todo...
    m_data = SqliteOperator::getInstance()->querydataById(1,m_lines);
    setCurPage(1);
    //slot_receiveData(m_data);
}

void TableWid::slot_lastPage()
{
    if(m_totalPage<=0)
        return;
    //todo...
    m_data = SqliteOperator::getInstance()->querydataById(m_totalNum-m_lines+1,m_totalNum);
    setCurPage(m_totalPage);
    //slot_receiveData(m_data);
}

void TableWid::slot_getTotalPage()
{
    m_totalNum = SqliteOperator::getInstance()->getTotalNum();
    m_totalPage = m_totalNum/m_lines;
    ui->totalPage->setText(QString::number(m_totalPage));
}

void TableWid::slot_exportData()
{
    qDebug()<<"m_totalNum:"<<m_totalNum;
    qDebug()<<"m_lines:"<<m_lines;
    //如果没有数据就不做处理
    if(m_totalNum<=0)
        return;
    //每次取出的数量,默认为3页数据
    int perMount = m_totalNum<3*m_lines?m_totalNum:3*m_lines;
    //当前取出的数量
    int totalMount = 0;
    QVector<QVector<QString>> data;

    //打开文件
    QFile output("../../output.txt");
    if(!output.open(QFile::WriteOnly|QFile::Text))
    {
        AutoCloseDialog* dialog = new AutoCloseDialog(this);
        dialog->setMsg("文件打开失败");
        //qDebug()<<"文件打开失败";
        return ;
    }
    //文件输入流
    QTextStream ts(&output);

    while(totalMount<m_totalNum)
    {
        qDebug()<<"totalMount:"<<totalMount;
        if(totalMount+perMount>m_totalNum)
        {
            perMount = m_totalNum-totalMount;
        }

        data=SqliteOperator::getInstance()->queryAccById(totalMount,totalMount+perMount);

        for(const QVector<QString>& row:data)
        {
            if(row.size()==2)
            {
                ts<<row.at(0)<<","<<row.at(1)<<'\n';
            }
            else
            {
                AutoCloseDialog* dialog = new AutoCloseDialog(this);
                dialog->setMsg("出数据:读取数据错误");
                //qDebug()<<"导出数据:读取数据错误";
            }
        }

        totalMount +=perMount;
    }

    output.close();
    AutoCloseDialog* dialog = new AutoCloseDialog(this);
    dialog->setMsg("文件导出成功");
    //qDebug()<<"文件导出成功";
}












