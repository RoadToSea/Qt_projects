#include "autoclosedialog.h"
#include "qtimer.h"

#include <qmainwindow.h>

AutoCloseDialog::AutoCloseDialog(QWidget *parent):QDialog(parent) {
    ui.setupUi(this);
    m_timer = new QTimer();
    connect(m_timer,&QTimer::timeout,this,&AutoCloseDialog::slot_closeDlg);
}

AutoCloseDialog::~AutoCloseDialog()
{

}

void AutoCloseDialog::setMsg(QString msg)
{
    ui.label->setText(msg);
    m_timer->start(1500);
    this->setFixedSize(200,100);
    this->show();

    // 获取主窗口 MainWindow 的大小和位置
    QMainWindow *mainWindow = qobject_cast<QMainWindow*>(this->parentWidget());
    if (mainWindow) {
        QRect mainWindowRect = mainWindow->geometry();  // 获取主窗口的几何信息
        int x = mainWindowRect.left() + (mainWindowRect.width() - this->width()) / 2;
        int y = mainWindowRect.top() + (mainWindowRect.height() - this->height()) / 2;
        this->move(x, y);  // 设置 AutoCloseDialog 弹窗位置为主窗口的中央
    }
}

void AutoCloseDialog::slot_closeDlg()
{
    if(m_timer->isActive())
        m_timer->stop();
    // 关闭对话框
    this->close();

    // 如果是通过 new 分配的，可以通过 deleteLater() 销毁
    this->deleteLater();
}
