#ifndef GRAPHWID_H
#define GRAPHWID_H

#include <QWidget>
#include <QtCharts/QtCharts>
#include "config.h"

namespace Ui {
class GraphWid;
}

class GraphWid : public QWidget
{
    Q_OBJECT

public:
    explicit GraphWid(QWidget *parent = nullptr);
    void graphInit(void);
    void setUpInterval(UpdateType time);
    void setUpInterval(unsigned time);
    ~GraphWid();

private:
    Ui::GraphWid *ui;
    QChart* m_chart;
    QSplineSeries* m_series;
    QValueAxis* x_Axis;
    QValueAxis* y_Axis;
    QVector<QPointF> m_points;
    QTimer* m_timer;
    int m_interval;

private slots:
    void updateGraph();
    void slot_setUpInterVal(void);
public slots:
    void slot_update(QMap<QString,QString>& data);
};

#endif // GRAPHWID_H
