#include "TableWid.h"
#include "ui_TableWid.h"
#include "config.h"


TableWid::TableWid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TableWid),m_curPage(0),m_totalPage(0),m_lines(0)
{
    ui->setupUi(this);
    UIinit();

    //获取输入框当前页数
    connect(ui->inputPage,&QLineEdit::editingFinished,this,&TableWid::slot_curPage);
    //按钮点击上一页
    connect(ui->prePageBtn,&QPushButton::clicked,this,&TableWid::slot_prePage);
    //按钮点击下一页
    connect(ui->nextPageBtn,&QPushButton::clicked,this,&TableWid::slot_nextPage);
    //按钮点击首页
    connect(ui->firstPageBtn,&QPushButton::clicked,this,&TableWid::slot_firstPage);
    //按钮点击尾页
    connect(ui->lastPageBtn,&QPushButton::clicked,this,&TableWid::slot_lastPage);
}

TableWid::~TableWid()
{
    delete ui;
}

void TableWid::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    int tableHeight = ui->tableWidget->height(); // 获取整个 QTableWidget 的高度
    int headerHeight = ui->tableWidget->horizontalHeader()->height(); // 表头高度
    int contentHeight = ui->tableWidget->viewport()->height();

    m_lines = contentHeight/30;
    //qDebug()<<"lines:"<<m_lines;
    //qDebug() << "表格高度:" << tableHeight;
    //qDebug() << "表头高度:" << headerHeight;
    //qDebug() << "内容高度:" << contentHeight;

    // 模拟测试数据填充
    // QVector<QVector<double>> testData;
    // for (int i = 0; i < m_lines; ++i) {
    //     QVector<double> rowData;
    //     for (int j = 0; j < 8; ++j) {
    //         rowData.append(i * 10 + j + 1); // 模拟数据
    //     }
    //     testData.append(rowData);
    // }

    // // 调用槽函数进行测试
    // slot_receiveData(testData);
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


    //设置初始页数
    ui->totalPage->setText("0");
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
        qDebug() << "提取数字:" << numberOnly;
    } else {
        m_curPage = 1; // 如果没有匹配到数字，设置为默认值
        qDebug() << "未找到数字，设置为 1";
    }
}

void TableWid::slot_prePage()
{
    if(m_curPage<=1)
        return;
    //todo...

    emit sig_requestData(m_curPage-1,m_lines);
}

void TableWid::slot_nextPage()
{
    if(m_curPage>=m_totalPage)
        return;
    //todo...
    emit sig_requestData(m_curPage+1,m_lines);
}

void TableWid::slot_firstPage()
{
    if(m_totalPage<=0)
        return;
    //todo...
    emit sig_requestData(1,m_lines);
}

void TableWid::slot_lastPage()
{
    if(m_totalPage<=0)
        return;
    //todo...
    emit sig_requestData(m_totalPage,m_lines);
}












