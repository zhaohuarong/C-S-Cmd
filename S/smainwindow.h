#ifndef SMAINWINDOW_H
#define SMAINWINDOW_H

#include <QList>
#include <QMainWindow>

namespace Ui {
class SMainWindow;
}

class QTcpServer;
class QTcpSocket;

class SMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SMainWindow(QWidget *parent = 0);
    ~SMainWindow();

private slots:
    void onNewConnection();
    void onClientReadyRead();
    void onStartCliecked();

private:
    Ui::SMainWindow *ui;
    QTcpServer *m_pCmdServer;
    QList<QTcpSocket *> m_lstClient;
};

#endif // SMAINWINDOW_H
