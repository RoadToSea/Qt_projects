#ifndef MUSICWID_H
#define MUSICWID_H

#include <QDialog>
#include <QAudioOutput>
#include <QtMultimedia/QMediaPlayer>

namespace Ui {
class MusicWid;
}

class MusicWid : public QDialog
{
    Q_OBJECT

public:
    explicit MusicWid(QWidget *parent = nullptr);
    ~MusicWid();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    Ui::MusicWid *ui;
    bool m_playState;
    QPointF m_pos;
    QMap<QString,QUrl>songs;
    QMediaPlayer* m_player;
    QAudioOutput* m_device;
    void mediaInit(void);
    void uiInit(void);
    void updateTimeLabel(qint64 current,qint64 total);
signals:
    void sig_importSongs(QStringList& songs);

public slots:
    /*
        signal:用户选中音乐
        slot:  加载音乐并在下方显示
    */
    void slot_loadMusic(QString& path,QString& name);
    void slot_play(void);
    void slot_pause(void);
private slots:
    void slot_chooseMusic(void);
    void slot_playOrPause(void);
    void slot_setSlider(qint64 duration);
    void slot_updateSlider(qint64 position);
    void slot_updatePlayer(qint64 position);
    void slot_preSong(void);
    void slot_lastSong(void);
    void slot_closeWindow(void);
};

#endif // MUSICWID_H
