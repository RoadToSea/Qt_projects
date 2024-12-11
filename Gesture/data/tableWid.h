#ifndef TABLEWID_H
#define TABLEWID_H

#include <QWidget>
#include "sqliteoperator.h"


namespace Ui {
class TableWid;
}

class TableWid : public QWidget
{
    Q_OBJECT

public:
    explicit TableWid(QWidget *parent = nullptr);
    ~TableWid();
protected:
    void showEvent(QShowEvent *event) override;
private:
    Ui::TableWid *ui;
    int m_lines;
    int m_curPage;
    int m_totalPage;
    int m_totalNum;
    QTimer* m_timer;
    QVector<QVector<QString>> m_data;
    void UIinit(void);
    void setCurPage(int page);
    void updateCurPage(void);
signals:
    void sig_requestData(int page,int rows);
public slots:
    void slot_receiveData(QVector<QVector<QString>>& data);
private slots:
    void slot_curPage(void);
    void slot_prePage(void);
    void slot_nextPage(void);
    void slot_firstPage(void);
    void slot_lastPage(void);
    void slot_getTotalPage(void);
    void slot_exportData(void);
};

#endif // TABLEWID_H
