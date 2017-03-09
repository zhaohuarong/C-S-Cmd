#include <QTcpSocket>
#include <QDebug>
#include <QProcess>
#include <QTimer>

#include "define.h"
#include "cmainwindow.h"
#include "ui_cmainwindow.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow),
    m_pCmdSocket(NULL),
    m_pReconnectionTimer(NULL)
{
    ui->setupUi(this);

    m_pCmdSocket = new QTcpSocket(this);
    connect(m_pCmdSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    m_pCmdSocket->connectToHost(SERVER_IP, CMD_PORT);
    m_pCmdSocket->waitForConnected(3000);

    m_pReconnectionTimer = new QTimer(this);
    connect(m_pReconnectionTimer, SIGNAL(timeout()), this, SLOT(onReconnectionTimer()));
    m_pReconnectionTimer->start(3000);
}

CMainWindow::~CMainWindow()
{
    m_pReconnectionTimer->stop();

    m_pCmdSocket->disconnectFromHost();
    m_pCmdSocket->waitForDisconnected(3000);

    delete ui;
}

void CMainWindow::onReadyRead()
{
    QString cmd = m_pCmdSocket->readAll();
    ui->log->append(QString("read : %1").arg(cmd));

    bool ret = QProcess::startDetached(cmd);
    ui->log->append(QString("start %1").arg(ret ? "true" : "false"));
}

void CMainWindow::onReconnectionTimer()
{
    if(m_pCmdSocket->state() != QAbstractSocket::ConnectedState || m_pCmdSocket->state() != QAbstractSocket::ConnectingState)
    {
        m_pCmdSocket->connectToHost(SERVER_IP, CMD_PORT);
        m_pCmdSocket->waitForConnected(3000);
    }
}
