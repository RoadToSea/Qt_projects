#include "prelistwid.h"
#include "protreeitem.h"
#include "config.h"
#include "prelistwiditem.h"
#include <QGuiApplication>
#include <QPainter>

PreListWid::PreListWid(QWidget *parent):QListWidget(parent),
    m_count(0),m_curItem(nullptr),m_lastIndex(0)
{
    //设置成显示图片模式
    this->setViewMode(QListView::IconMode);
    this->setFlow(QListView::LeftToRight);
    this->setIconSize(QSize(PRELISTITEM_SIZE, PRELISTITEM_SIZE));//设置图片的大小
    this->setWrapping(false);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setSpacing(PRELISTITEM_INTERVAL);
    //连接预览图点击信号
    connect(this,&PreListWid::itemPressed,this,&PreListWid::slot_itemPressed);

}




void PreListWid::slot_update(QTreeWidgetItem *item)
{
    if(!item)
        return;
    ProTreeItem* curItem = static_cast<ProTreeItem*>(item);
    QString& path = curItem->getPath();
    auto iter = m_itemMap.find(path);
    //如果路径已经被保存了
    if(iter!=m_itemMap.end())
    {
        return;
    }

    addListItem(path);
}

void PreListWid::addListItem(QString &path)
{
    ++m_count;
    //绘制要显示的区域
    QPixmap picture(path);
    picture = picture.scaled(PRELISTITEM_SIZE,PRELISTITEM_SIZE,Qt::KeepAspectRatio);
    int picture_width = picture.width();
    int picture_height = picture.height();

    QPixmap base(QSize(PRELISTITEM_SIZE,PRELISTITEM_SIZE));
    base.fill(QColor(220,220,220,60));

    QPainter painter(&base);
    int x = (PRELISTITEM_SIZE-picture_width)/2;
    int y = (PRELISTITEM_SIZE-picture_height)/2;
    //将内容绘制到base基底中
    painter.drawPixmap(x,y,picture);

    //构造item节点并添加显示
    PreListWidItem* item = new PreListWidItem(base,path,m_count,this);
    item->setSizeHint(QSize(PRELISTITEM_SIZE,PRELISTITEM_SIZE));
    this->addItem(item);
    m_itemMap.insert(path,item);


    //如果是第一个就记录预览图在其父窗口的位置，这样我们可以根据
    //屏幕最右侧的预览图和该图的位置差值移动PreList
    if(m_count==1)
    {
        m_originPos = this->pos();
    }

    PreListWidItem* choosedItem = item;
    int choosedIndex = choosedItem->getIndex();

    //如果超出显示区域就要更新显示位置
    //计算窗口可容纳的item数量
    int capacity = this->width()/(PRELISTITEM_SIZE+PRELISTITEM_INTERVAL);
    qDebug()<<"capacity:"<<capacity;
    qDebug()<<"choosedIndex:"<<choosedIndex;
    qDebug()<<"lastIndex:"<<m_lastIndex;
    QPoint curPos = this->pos();
    qDebug()<<" x:"<<curPos.x()<<" y: "<<curPos.y();
    if(choosedIndex>capacity)
    {
        QPoint curPos = this->pos();
        int range =-(choosedIndex-m_lastIndex)*(PRELISTITEM_SIZE);
        qDebug()<<"move range :"<<range;
        //this->move(range,curPos.y());
        m_lastIndex = choosedIndex;
    }
    else
    {
        this->move(m_originPos);
        m_lastIndex = capacity;
    }

    this->setCurrentItem(item);
}


void PreListWid::slot_choosed(QTreeWidgetItem *item)
{
    if(!item)
    {
        qDebug()<<"slot_choosed :input item is nullptr";
        return ;
    }
    auto tmp = static_cast<ProTreeItem*>(item);
    QString path = tmp->getPath();
    //如果这个图片还没有添加进缩略图列表中直接返回
    auto iter = m_itemMap.find(path);
    if(iter== m_itemMap.end())
    {
        return;
    }

    PreListWidItem* choosedItem = static_cast<PreListWidItem*>(iter.value());
    int choosedIndex = choosedItem->getIndex();

    //如果超出显示区域就要更新显示位置
    //计算窗口可容纳的item数量
    int capacity = this->width()/(PRELISTITEM_SIZE+PRELISTITEM_INTERVAL);
    qDebug()<<"capacity"<<capacity;
    qDebug()<<"choosedIndex"<<choosedIndex;
    if(choosedIndex>capacity)
    {
        QPoint curPos = this->pos();
        this->move(curPos.x()-(choosedIndex-m_lastIndex)*(PRELISTITEM_SIZE),curPos.y());
        m_lastIndex = choosedIndex;
    }
    else
    {
        this->move(m_originPos);
        m_lastIndex = capacity;
    }
    this->setCurrentItem(choosedItem);
}


void PreListWid::slot_itemPressed(QListWidgetItem *item)
{
    //如果不是左键点击直接返回
    if(QGuiApplication::mouseButtons()!=Qt::LeftButton)
        return;
    auto curItem = static_cast<PreListWidItem*>(item);
    QString& path =  curItem->getPath();
    m_curItem = item;
    this->setCurrentItem(item);
    emit sig_select(path);
}
