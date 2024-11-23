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
    void picListUpdate();
protected:
    void paintEvent(QPaintEvent *event) override;
public slots:
    void slot_timeout(void);
    void start();
    void stop();
private:
    QTimer* m_timer;
    QTreeWidgetItem* m_curItem;
    QPixmap m_curPixmap;
    QPixmap m_nextPixmap;
    float m_factor;
    bool  m_start;
    std::map<QString,QTreeWidgetItem*> m_itemMap;

};

#endif // SLIDEANIMATIONWID_H
