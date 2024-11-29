#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "musicwid.h"
#include "portraypic.h"
#include "slidedlg.h"
#include <QList>
#include <QtMultimedia/QAudio>
#include <QtMultimedia/QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PortrayPic* portrayPic;
    std::shared_ptr<SlideDlg> slideDlg;
    std::unique_ptr<MusicWid> musicWid;
    QList<QUrl> musicList;
    unsigned musicIndex;
    QMediaPlayer* musicPlayer;
    QAudioOutput* audioOutput;
    void UIinit(void);
public slots:
    void slot_createPro(void);
    void slot_openPro(void);
    void slot_showSlideDlg(QTreeWidgetItem* first,QTreeWidgetItem* last);
    void slot_chooseMusic(void);
    void slot_turnOnMusic(void);
    void slot_turnOffMusic(void);
signals:
    void slidePlay();
};
#endif // MAINWINDOW_H
