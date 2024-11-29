#include "musiclistwid.h"
#include "musiclistwiditem.h"
#include <QDir>
#include <QFileInfo>


MusicListWid::MusicListWid(QWidget *parent):QListWidget(parent),m_firstItem(nullptr),m_lastItem(nullptr)
    ,m_curItem(nullptr)
{
    //单击选择音乐
    connect(this,&MusicListWid::itemClicked,this,&MusicListWid::slot_itemPressed);
    //双击双击播放音乐
    connect(this,&MusicListWid::itemDoubleClicked,this,&MusicListWid::slot_itemDoublePressed);
}

QListWidgetItem *MusicListWid::getCurItem()
{
    return m_curItem;
}

void MusicListWid::setCurItem(QListWidgetItem *item)
{
    m_curItem = item;
    this->setCurrentItem(item);
}

void MusicListWid::slot_importSongs(QStringList &songs)
{
    for(QString& song: songs)
    {
        importSongs(song);
    }
}

void MusicListWid::slot_itemPressed(QListWidgetItem *item)
{
    m_curItem = item;
    MusicListWidItem* cur = static_cast<MusicListWidItem*>(m_curItem);
    emit sig_musicChoosed(cur->getPath(),cur->getName());
}

void MusicListWid::slot_itemDoublePressed()
{
    emit sig_musicPlay();
}

void MusicListWid::importSongs(QString song)
{

    QDir importDir(song);
    //设置文件过滤,只要文件夹和文件,不要linux下的. ..格式
    importDir.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
    //设置找到的文件的排序方式
    importDir.setSorting(QDir::Name);
    QFileInfoList infoList = importDir.entryInfoList();

    for(QFileInfo& info:infoList)
    {
        if(info.isDir())
        {
            //递归检索
            importSongs(info.filePath());
        }
        else
        {
            //获取后缀
            QString suffix = info.completeSuffix();
            //如果不是MP3或者MP4
            if(suffix!="mp3"&&suffix!="mp4")
                return;

            MusicListWidItem* item = new MusicListWidItem(QIcon(":/res/icon/music.svg"),info.filePath(),info.fileName());
            this->addItem(item);
            if(!m_firstItem)
            {
                m_firstItem = item;
                m_lastItem = item;
            }
            else
            {
                if(m_lastItem)
                {
                    item->setPreItem(m_lastItem);
                    auto lastItem = static_cast<MusicListWidItem*>(m_lastItem);
                    lastItem->setLastItem(item);
                }
                m_lastItem = item;
            }


        }
    }
}


