#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

#include "define.h"
#include "smainwindow.h"
#include "ui_smainwindow.h"

SMainWindow::SMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SMainWindow),
    m_pCmdServer(NULL)
{
    ui->setupUi(this);

    connect(ui->btnStart, SIGNAL(clicked()), this, SLOT(onStartCliecked()));

    m_pCmdServer = new QTcpServer(this);
    connect(m_pCmdServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    m_pCmdServer->listen(QHostAddress::Any, CMD_PORT);
}

SMainWindow::~SMainWindow()
{
    delete ui;
}

void SMainWindow::onNewConnection()
{
    QTcpSocket *pSocket = m_pCmdServer->nextPendingConnection();
    connect(pSocket, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
    QString strIP = pSocket->peerAddress().toString();
    ui->log->append(QString("%1 connected.").arg(strIP));
    m_lstClient << pSocket;
}

void SMainWindow::onClientReadyRead()
{
    // nothing
}

void SMainWindow::onStartCliecked()
{
    QString cmd = ui->ledtCmd->text();
    if(cmd.trimmed().isEmpty())
        return;

    foreach(QTcpSocket *pSocket, m_lstClient)
    {
        if(pSocket == NULL)
            continue;
//        int header = 0x01;
//        int length;
        pSocket->write(cmd.toLatin1());
        pSocket->waitForBytesWritten();
    }
}
