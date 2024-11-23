#include "protreeitem.h"
#include "slideanimationwid.h"
#include <QTimer>
#include <QPainter>

SlideAnimationWid::SlideAnimationWid(QWidget *parent)
    : QWidget{parent},m_timer(nullptr),m_curItem(nullptr),m_factor(0),m_start(false)
{
    m_timer = new QTimer();
    //连接定时器到期事件
    connect(m_timer,&QTimer::timeout,this,&SlideAnimationWid::slot_timeout);
}

SlideAnimationWid::~SlideAnimationWid()
{
    qDebug()<<"SlideAnimationWid has been destroyed";
    m_timer->stop();
    delete m_timer;
}

void SlideAnimationWid::start()
{
    //发送动画开始信号
    //...
    m_timer->start(50);
    m_start = true;
}

void SlideAnimationWid::stop()
{
    //发送动画停止信号
    //....
    //关掉定时器
    m_timer->stop();
    m_start = false;
}


void SlideAnimationWid::slot_timeout()
{
    if(!m_curItem)
    {
        stop();
        update();
        return;
    }

    m_factor+=0.01;

    //说明当前图片播放完,需要加载后一张图片
    if(m_factor>1)
    {
        m_factor = 0;
        auto* cur = static_cast<ProTreeItem*>(m_curItem);
        auto* next = cur->getNextItem();
        if(!next)
        {
            stop();
            update();
            return;
        }
        //加载下一张图片
        setPixmap(next);
        update();
        return ;
    }
    update();
}

void SlideAnimationWid::setPixmap(QTreeWidgetItem *item)
{
    auto* _item = static_cast<ProTreeItem*>(item);
    //加载图片到变量中
    QString path = _item->getPath();
    m_curPixmap.load(path);
    //用于查找是否是新的图片,如果是,就通知下方预览图更新
    if(m_itemMap.find(path) == m_itemMap.end())
    {
        m_itemMap.insert(std::make_pair(path,_item));
        //通知下方预览图更新
        emit picListUpdate();
    }

    //更新当前节点为后一个节点
    m_curItem = item;

    auto* _next = _item->getNextItem();
    if(!_next)
    {
        return;
    }
    auto* _nextItem = static_cast<ProTreeItem*>(_next);
    path = _nextItem->getPath();
    m_nextPixmap.load(path);
    if(m_itemMap.find(path) == m_itemMap.end())
    {
        m_itemMap.insert(std::make_pair(path,_nextItem));
        //通知下方预览图更新
        emit picListUpdate();
    }
}

void SlideAnimationWid::paintEvent(QPaintEvent *event)
{
    if(m_curPixmap.isNull())
        return;

    //主画笔,用来绘制图片和透明度遮罩
    QPainter painter(this);
    //设置防锯齿效果
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect rect = geometry();
    //计算透明度,渐隐
    int alpha = 255*(1.0f-m_factor);

    //拉伸图片到图片显示区域大小
    int w = rect.width();
    int h = rect.height();
    m_curPixmap = m_curPixmap.scaled(w,h,Qt::KeepAspectRatio);

    //创建一个和图片一样大小的图层,设置成透明状态
    QPixmap alphaPix(m_curPixmap.size());
    alphaPix.fill(Qt::transparent);

    /*设置覆盖模式,将图片绘制到alphaPix区域,再设置成叠加模式,将透明度为alpha的
    矩形覆盖到图片上方,p1.end()会释放资源,并将内容绘制进alphaPix*/
    QPainter p1(&alphaPix);
    p1.setCompositionMode(QPainter::CompositionMode_Source);
    p1.drawPixmap(0,0,m_curPixmap);
    p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p1.fillRect(alphaPix.rect(),QColor(0,0,0,alpha));
    p1.end();

    //找到图片居中时左上角的坐标绘制图片
    int upleft_x = (w-m_curPixmap.width())/2;
    int upleft_y = (h-m_curPixmap.height())/2;
    painter.drawPixmap(upleft_x,upleft_y,alphaPix);

    if(m_nextPixmap.isNull())
        return;

    //计算透明度,渐显
    alpha = 255*(m_factor);

    m_nextPixmap = m_nextPixmap.scaled(w,h,Qt::KeepAspectRatio);
    QPixmap alphaPix2(m_nextPixmap.size());
    alphaPix2.fill(Qt::transparent);

    QPainter p2(&alphaPix2);
    p2.setCompositionMode(QPainter::CompositionMode_Source);
    p2.drawPixmap(0,0,m_nextPixmap);
    p2.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p2.fillRect(alphaPix2.rect(),QColor(0,0,0,alpha));
    p2.end();

    //找到图片居中时左上角的坐标绘制图片
    upleft_x = (w-m_curPixmap.width())/2;
    upleft_y = (h-m_curPixmap.height())/2;
    painter.drawPixmap(upleft_x,upleft_y,alphaPix2);

    return QWidget::paintEvent(event);
}











