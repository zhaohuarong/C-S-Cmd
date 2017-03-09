#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>

class QTcpSocket;
class QTimer;

namespace Ui {
class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

private slots:
    void onReadyRead();
    void onReconnectionTimer();

private:
    Ui::CMainWindow *ui;
    QTcpSocket *m_pCmdSocket;
    QTimer *m_pReconnectionTimer;
};

#endif // CMAINWINDOW_H
