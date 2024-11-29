#ifndef SLIDEANIMATIONWID_H
#define SLIDEANIMATIONWID_H

#include <QWidget>
#include <QTreeWidget>

class SlideAnimationWid : public QWidget
{
    Q_OBJECT
public:
    explicit SlideAnimationWid(QWidget *parent = nullptr);
    ~SlideAnimationWid();
    void setPixmap(QTreeWidgetItem* item);

signals:
    void picListUpdate(QTreeWidgetItem* item);
    void picListChoosed(QTreeWidgetItem* item);
protected:
    void paintEvent(QPaintEvent *event) override;
public slots:
    void slot_timeout(void);
    void slot_pauseTimeout(void);
    void slot_selected(QString& path);
    void slot_prePic(void);
    void slot_nextPic(void);
    void start();
    void stop();
private:
    QTimer* m_timer;
    QTimer* m_pauseTimer;
    QTreeWidgetItem* m_curItem;
    QPixmap m_curPixmap;
    QPixmap m_nextPixmap;
    float m_factor;
    bool  m_start;
    QMap<QString,QTreeWidgetItem*> m_itemMap;
    void set_updateCurPic(QString& path);

};

#endif // SLIDEANIMATIONWID_H
