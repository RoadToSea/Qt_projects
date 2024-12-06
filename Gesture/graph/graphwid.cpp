#include "graphwid.h"
#include "ui_graphwid.h"
#include <QRandomGenerator>


GraphWid::GraphWid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GraphWid),m_interval(-1)
{
    ui->setupUi(this);
    m_chart = new QChart();
    m_series = new QSplineSeries();
    x_Axis = new QValueAxis(this);
    y_Axis = new QValueAxis(this);
    m_timer = new QTimer();

    graphInit();
    //根据传入数据自动更新
    setUpInterval(AutoUpdate);

    connect(ui->inputBtn,&QPushButton::clicked,this,&GraphWid::slot_setUpInterVal);

}

void GraphWid::graphInit()
{
    //设置坐标临界值
    x_Axis->setMin(0);
    x_Axis->setMax(GRAPH_MAX_X);
    y_Axis->setMin(-10);
    y_Axis->setMax(15);

    m_chart->addAxis(x_Axis,Qt::AlignBottom);
    m_chart->addAxis(y_Axis,Qt::AlignLeft);

    //需要再设置依附坐标前添加进chart
    m_chart->addSeries(m_series);
    m_series->attachAxis(x_Axis);
    m_series->attachAxis(y_Axis);


    m_chart->setTitle("重力加速度");

    ui->chartView->setChart(m_chart);
    //m_chart->createDefaultAxes();

    for (int i = 0; i < GRAPH_MAX_X; ++i) {
        m_points.append(QPointF(i, 0));  // 初始化为横坐标从0到GRAPH_MAX_X，纵坐标为0
    }
    m_series->replace(m_points);


}

void GraphWid::setUpInterval(UpdateType time)
{
    m_interval = time;
    if(time<0)
    {
        //自动更新模式,如果定时器开启状态就关闭
        if(m_timer->isActive())
        {
            m_timer->stop();
        }
        //断开定时器信号防止冲突
        disconnect(m_timer,&QTimer::timeout,this,&GraphWid::updateGraph);
    }
    else
    {
        setUpInterval(static_cast<unsigned>(time));
    }
}

/*
    自定义定时器更新时间
*/
void GraphWid::setUpInterval(unsigned time)
{
    m_interval = time;

    // 停止当前定时器，防止冲突
    if (m_timer->isActive())
    {
        m_timer->stop();
    }

    // 重新连接信号，确保新的间隔时间生效
    disconnect(m_timer, &QTimer::timeout, this, &GraphWid::updateGraph);
    connect(m_timer, &QTimer::timeout, this, &GraphWid::updateGraph);
    m_timer->start(m_interval);
}

GraphWid::~GraphWid()
{
    delete ui;
}

void GraphWid::updateGraph()
{
    // 获取新的重力加速度值（这里模拟生成一个随机数作为示例）
    //double newValue = QRandomGenerator::global()->bounded(-9, 9);  // 随机重力加速度值（示例）

    // 更新曲线数据
    m_series->replace(m_points);  // 用新的数据点更新曲线

    // 刷新视图
    ui->chartView->repaint();
}

void GraphWid::slot_update(QMap<QString,QString>& data)
{
    double val;
    if(!data.isEmpty())
    {
        val = data["accel_z"].toDouble();
    }
    // 添加新的数据点
    m_points.append(QPointF(m_points.size(), val));  // 横坐标是点的数量，纵坐标是加速度值
    // 如果点数超过GRAPH_MAX_X个，删除最旧的点
    if (m_points.size() > GRAPH_MAX_X) {
        m_points.removeFirst();  // 删除最旧的点
        for(int i=0;i<GRAPH_MAX_X;i++)
        {
            m_points[i].setX(i+1);
        }
        qDebug()<<"point:"<<m_points[GRAPH_MAX_X-1].x()<<","<<m_points[GRAPH_MAX_X-1].y();
    }

    //如果是根据输入数据的频率更新
    if(m_interval<=0)
    {
        updateGraph();
    }
    //如果由定时器定时更新
    else{
        //已经绑定了定时器信号无需手动更新
        return;
    }
}

void GraphWid::slot_setUpInterVal()
{
    int index = ui->comboBox->currentIndex();
    //qDebug()<<"index:"<<index;
    switch(index)
    {
        case 0:
            setUpInterval(AutoUpdate);
            break;
        case 1:
            setUpInterval(_100msUpdate);
            break;
        case 2:
            setUpInterval(_200msUpdate);
            break;
        case 3:
            setUpInterval(_300msUpdate);
            break;
        case 4:
            setUpInterval(_400msUpdate);
            break;
        case 5:
            setUpInterval(_500msUpdate);
            break;
        case 6:
            //获取自定义值
            int time = ui->inputTime->text().toInt();
            if(time<=0)  time = 100;
            setUpInterval(time);
            break;
    }
}
