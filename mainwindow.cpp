#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include "mqtt\qmqtt.h"
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client=new QMQTT::Client();//初始化QMQTT客户端指针
    ui->Host_comboBox->setEditable(true);
    ui->Port_comboBox->setEditable(true);
    ui->disconnect_pushButton->hide();

    connect(client,SIGNAL(connected()),this,SLOT(mqtt_connected()));
    connect(client,SIGNAL(disconnected()),this,SLOT(mqtt_disconnected()));
    connect(client,SIGNAL(received(const QMQTT::Message&)),this,SLOT(mqtt_receive_message(const QMQTT::Message&)));

}

MainWindow::~MainWindow()
{
    delete ui;
}
//与设置的mqtt服务器连接
void MainWindow::on_connect_pushButton_clicked()
{

    QHostAddress host(ui->Host_comboBox->currentText());
    QByteArray password = ui->IN_Password->text().toUtf8();
//    QMQTT::MQTTVersion version;
    quint16 port=(ui->Port_comboBox->currentText()).toUInt();

    //client->set
    client->setKeepAlive((ui->IN_Timeout->text()).toUInt());
    client->setHost(host);//设置EMQ代理服务器IP
    client->setPort(port);//设置EMQ代理服务器端口号
    client->setClientId(ui->IN_Client_ID->text());//设置一个客户端ID
    client->setUsername(ui->IN_Usernae->text());//设置一个客户端用户名
    client->setPassword(password);//设置一个客户端密码
    client->cleanSession();//清除缓存
    if (ui->mqtt_version_comboBox->currentIndex() == 0)
        client->setVersion(QMQTT::MQTTVersion::V3_1_1);//设置mqtt版本
    else if (ui->mqtt_version_comboBox->currentIndex() == 1)
        client->setVersion(QMQTT::MQTTVersion::V3_1_0);
    client->connectToHost();//连接EMQ代理服务器

    ui->connect_pushButton->hide();
    ui->disconnect_pushButton->show();
}
//与mqtt服务器断开连接
void MainWindow::on_disconnect_pushButton_clicked()
{
    client->disconnectFromHost();
    ui->connect_pushButton->show();
    ui->disconnect_pushButton->hide();
}
//发布主题
void MainWindow::on_Pushlish_pushButton_clicked()
{
    QMQTT::Message mqtt_message(0,ui->Toplic_public_lineEdit->text(),ui->Public_message_textEdit->toPlainText().toUtf8(),ui->Public_Qos->currentIndex());
    client->publish(mqtt_message);
}
//成功连接到mqtt服务器
void MainWindow::mqtt_connected()
{
    ui->show_state_browser->insertPlainText("client had connected to broker\n");
    ui->show_state_browser->moveCursor(QTextCursor::Start);
}
//与服务器断开
void MainWindow::mqtt_disconnected()
{
    ui->show_state_browser->insertPlainText("lost connect\n");
    ui->show_state_browser->moveCursor(QTextCursor::Start);
}

void MainWindow::mqtt_receive_message(const QMQTT::Message&message)
{
    QString strtopic = message.topic();
    QString strpayload = message.payload();
    ui->SubscribeMessage_Rece->insertPlainText(strtopic +":"+ strpayload + "\n");
    ui->SubscribeMessage_Rece->moveCursor(QTextCursor::Start);
}
//订阅主题
void MainWindow::on_Subscribe_pushButton_clicked()
{
    client->subscribe(ui->Subscribe_lineEdit->text(),0);
}
