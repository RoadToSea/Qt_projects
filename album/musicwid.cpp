#include "config.h"
#include "musiclistwiditem.h"
#include "musicwid.h"
#include "ui_musicwid.h"

#include <QFileDialog>
#include <QTime>
#include <QMouseEvent>

MusicWid::MusicWid(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MusicWid)
{
    ui->setupUi(this);
    mediaInit();
    uiInit();
    //连接点击导入音乐按钮弹出对话框
    connect(ui->importMusicBtn,&picButton::clicked,this,&MusicWid::slot_chooseMusic);
    //连接存入歌曲信号
    connect(this,&MusicWid::sig_importSongs,ui->musicListWid,&MusicListWid::slot_importSongs);
    //连接单击音乐列表选中音乐并在下方展示
    connect(ui->musicListWid,&MusicListWid::sig_musicChoosed,this,&MusicWid::slot_loadMusic);
    //连接双击音乐列表播放选中的音乐
    connect(ui->musicListWid,&MusicListWid::sig_musicPlay,this,&MusicWid::slot_play);
    //连接播放按钮
    connect(ui->playBtn,&slideStateButton::sigStart,this,&MusicWid::slot_playOrPause);
    connect(ui->playBtn,&slideStateButton::sigStop,this,&MusicWid::slot_playOrPause);
    //播放上一首
    connect(ui->preSongBtn,&picButton::btnClicked,this,&MusicWid::slot_preSong);
    //播放下一首
    connect(ui->lastSongBtn,&picButton::btnClicked,this,&MusicWid::slot_lastSong);
    //关闭窗口
    connect(ui->closeBtn,&picButton::btnClicked,this,&MusicWid::slot_closeWindow);
    //音乐刚加载设置进度条
    connect(m_player,&QMediaPlayer::durationChanged,this,&MusicWid::slot_setSlider);
    //歌曲正在播放时更新音乐播放进度条
    connect(m_player,&QMediaPlayer::positionChanged,this,&MusicWid::slot_updateSlider);
    //拖动进度条更新歌曲进度
    connect(ui->songProgress,&QSlider::sliderMoved,this,&MusicWid::slot_updatePlayer);
}

MusicWid::~MusicWid()
{
    delete ui;
}

void MusicWid::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_pos = event->globalPosition() - frameGeometry().topLeft();
        event->accept();
    }
}

void MusicWid::mouseMoveEvent(QMouseEvent *event)
{
    //拖动的鼠标按键里有左键的话
    if(event->buttons() & Qt::LeftButton)
    {
        QPointF offset = event->globalPosition()-m_pos;
        move(offset.toPoint());
        event->accept();
    }
}

void MusicWid::mediaInit()
{
    m_player = new QMediaPlayer();
    m_device = new QAudioOutput();
    m_player->setAudioOutput(m_device);
}

void MusicWid::slot_loadMusic(QString &path, QString &name)
{
    QUrl url(path);
    //如果音乐路径无效
    if(!url.isValid())
        return;
    auto iter = songs.find(name);
    if(iter==songs.end())
        songs.insert(name,url);
    ui->songName->setText(name);
    m_player->setSource(url);

}

void MusicWid::slot_play()
{
    m_player->play();
    m_playState = true;
}

void MusicWid::slot_pause()
{
    m_player->pause();
    m_playState = false;
}

void MusicWid::slot_chooseMusic()
{
    QFileDialog fileDialog;
    //设置打开目录为当前目录
    fileDialog.setDirectory(QDir::currentPath());
    //设置选择模式为已存在的文件
    fileDialog.setFileMode(QFileDialog::Directory);
    //设置标题栏
    fileDialog.setWindowTitle("选择音乐");
    // 同时显示文件和文件夹
    fileDialog.setOption(QFileDialog::ShowDirsOnly, false);
    //设置显示模式
    fileDialog.setViewMode(QFileDialog::Detail);

    if(fileDialog.exec()==QFileDialog::Accepted)
    {
        QStringList musicDirectory = fileDialog.selectedFiles();
        //如果用户没有选择
        if(musicDirectory.length()<=0)
            return;
        emit sig_importSongs(musicDirectory);
    }
}

void MusicWid::slot_playOrPause()
{
    //如果是播放状态就暂停
    if(m_playState)
        slot_pause();
    else
        slot_play();
}

/*
    歌曲播放进度条设计思路:
        以player和用户操作为中心,进度条为辅,拖动进度条的时候并不改变歌曲播放状态,
    松手才改变
        player进度每改变一点,就让进度条改变一点,如果用户在拖动进度条就不更新
    进度条,但是要更新时间label
*/

void MusicWid::slot_setSlider(qint64 duration)
{
    //根据歌曲长度设置进度条长度
    ui->songProgress->setRange(0,duration);
    updateTimeLabel(0,duration);
}

void MusicWid::slot_updateSlider(qint64 position)
{
    //用户没有拖动进度条才更新进度条
    if(!ui->songProgress->isSliderDown())
        ui->songProgress->setValue(position);
    updateTimeLabel(position,m_player->duration());
}

void MusicWid::slot_updatePlayer(qint64 position)
{
    m_player->setPosition(position);
}

void MusicWid::slot_preSong()
{
    MusicListWidItem* cur=static_cast<MusicListWidItem*>(ui->musicListWid->getCurItem());
    if(!cur)
        return;
    MusicListWidItem* pre = static_cast<MusicListWidItem*>(cur->getPreItem());
    if(!pre)
        return;
    slot_loadMusic(pre->getPath(),pre->getName());
    ui->musicListWid->setCurItem(pre);
    slot_play();
}

void MusicWid::slot_lastSong()
{
    MusicListWidItem* cur=static_cast<MusicListWidItem*>(ui->musicListWid->getCurItem());
    if(!cur)
        return;
    MusicListWidItem* last = static_cast<MusicListWidItem*>(cur->getLastItem());
    if(!last)
        return;
    slot_loadMusic(last->getPath(),last->getName());
    ui->musicListWid->setCurItem(last);
    slot_play();
}

void MusicWid::slot_closeWindow()
{
    this->hide();
}

void MusicWid::updateTimeLabel(qint64 current, qint64 total)
{
    QTime currentTime = QTime::fromMSecsSinceStartOfDay(current);
    QTime totalTime = QTime::fromMSecsSinceStartOfDay(total);
    QString timeText = currentTime.toString("mm:ss")+"/"+totalTime.toString("mm:ss");
    ui->timeLabel->setText(timeText);
}

void MusicWid::uiInit()
{
    setWindowFlag(Qt::FramelessWindowHint);

    QString left_normal(LEFT_NORMAL);
    QString left_hover(LEFT_HOVER);
    QString left_clicked(LEFT_CLICKED);

    QString right_normal(RIGHT_NORMAL);
    QString right_hover(RIGHT_HOVER);
    QString right_clicked(RIGHT_CLICKED);

    ui->preSongBtn->setIcons(left_normal,left_hover,left_clicked);
    ui->lastSongBtn->setIcons(right_normal,right_hover,right_clicked);

    QString play_normal(PLAY_NORMAL);
    QString play_hover(PLAY_HOVER);
    QString play_press(PLAY_PRESS);
    QString stop_normal(STOP_NORMAL);
    QString stop_hover(STOP_HOVER);
    QString stop_press(STOP_PRESS);

    QString close_normal(CLOSE_NORMAL);
    QString close_hover(CLOSE_HOVER);
    QString close_press(CLOSE_PRESS);

    ui->playBtn->setIcons(play_normal,play_hover,play_press,stop_normal,stop_hover,stop_press);
    ui->closeBtn->setIcons(close_normal,close_hover,close_press);

}


