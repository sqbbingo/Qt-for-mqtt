#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mqtt/qmqtt.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString topic;
        QMQTT::Client *client;//创建QMQTT客户端指针

private slots:

    void on_connect_pushButton_clicked();

    void on_disconnect_pushButton_clicked();

    void on_Pushlish_pushButton_clicked();

private:
    Ui::MainWindow *ui;

private slots:
    void mqtt_connected();
    void mqtt_disconnected();
    void mqtt_receive_message(const QMQTT::Message &message);

    void on_Subscribe_pushButton_clicked();
};

#endif // MAINWINDOW_H
