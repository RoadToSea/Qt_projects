#ifndef MUSICLISTWID_H
#define MUSICLISTWID_H

#include <QListWidget>
#include <QObject>

class MusicListWid : public QListWidget
{
    Q_OBJECT
public:
    MusicListWid(QWidget *parent = nullptr);
    QListWidgetItem* getCurItem(void);
    void setCurItem(QListWidgetItem* item);
private:
    QListWidgetItem* m_curItem;
    QListWidgetItem* m_firstItem;
    QListWidgetItem* m_lastItem;
    void importSongs(QString song);
public slots:
    void slot_importSongs(QStringList& songs);
private slots:
    void slot_itemPressed(QListWidgetItem* item);
    void slot_itemDoublePressed(void);
signals:
    void sig_musicChoosed(QString& path,QString& name);
    void sig_musicPlay(void);

};

#endif // MUSICLISTWID_H
