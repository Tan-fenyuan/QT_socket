#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QByteArray>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("5000");

    this->m_socket = new QTcpSocket(this);//初始化

    connect(m_socket,&QTcpSocket::readyRead,this,[=](){
        QByteArray data = m_socket->readAll();
        ui->textEdit->append("接收到: "+data);
    });
    connect(m_socket,&QTcpSocket::disconnected,this,[=](){
        m_socket->close();
        lable->setPixmap(QPixmap(":/close.png").scaled(20,20));
        ui->textEdit->setText("已断开连接");
    });
    connect(m_socket,&QTcpSocket::connected,this,[=](){
        lable->setPixmap(QPixmap(":/open.png").scaled(20,20));
        ui->textEdit->setText("已连接到服务端...");
    });
    lable = new QLabel(this);
    lable->setPixmap(QPixmap(":/close.png").scaled(20,20));
    ui->statusbar->addWidget(new QLabel("当前状态"));
    ui->statusbar->addWidget(lable);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton outcome  =
            QMessageBox::question(this,"Warning","do you want close this window?");
    switch (outcome) {
    case QMessageBox::Yes:
        event->accept();
        break;
    default:
        event->ignore();
        break;
    }
}
//监听按钮被按下
void MainWindow::on_pushButton_clicked()
{
    unsigned short port = ui->lineEdit->text().toUShort();//获取端口号
    QString IP = ui->lineEdit_2->text();//获取IP地址
    m_socket->connectToHost(QHostAddress(IP),port);
    ui->pushButton->setDisabled(true);
    ui->pushButton_3->setDisabled(false);
}
//send 被按下
void MainWindow::on_pushButton_2_clicked()
{
    QString msg = ui->textEdit_2->toPlainText();//取出输入的数据(纯文本格式)
    m_socket->write(msg.toUtf8());
    ui->textEdit->append("发送"+msg);
    ui->textEdit_2->clear();
}
//断开连接被按下
void MainWindow::on_pushButton_3_clicked()
{
    this->m_socket->close();
    ui->pushButton->setDisabled(false);
    ui->pushButton_3->setDisabled(true);
    lable->setPixmap(QPixmap(":/close.png").scaled(20,20));
    ui->statusbar->addWidget(new QLabel("当前状态"));
    ui->statusbar->addWidget(lable);

}

