#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStringListModel>
#include <QTime>
#include <QJsonDocument>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    listView = new QListView();
    model = new QStringListModel();

    ui->recordListA->setModel(model);
    onWsDisconnect();
    initWebsocket();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAddRecord_clicked()
{
    addItem(QString("New stuff"));
}

void MainWindow::addItem(const QString &value)
{
    QString now = QDateTime::currentDateTime().toString("dd/MM-yy hh:mm:ss");
    QStringList itemList = model->stringList();
    itemList << QString(now + ": " + value);
    model->setStringList(itemList);
    ui->lastUpdatedValue->setText(now);
}

void MainWindow::initWebsocket()
{
    webSocket = new QWebSocket();
    webSocket->open(QUrl("ws://127.0.0.1:4000/subscribe"));
    QObject::connect(webSocket, &QWebSocket::connected, [=](){
        ui->wsConnectedIndicator->setStyleSheet(QString("background-color: green; color: black; font-weight:bold;"));
        ui->wsConnectedIndicator->setText(QString("Connected"));
        qDebug() << "Connected to WebSocket server";
        webSocket->sendTextMessage(QString("{\"topic\":\"FUN\"}"));
    });
    QObject::connect(webSocket, &QWebSocket::errorOccurred, [=](QAbstractSocket::SocketError error){
        qDebug() << "WebSocket error:" << error;
    });
    QObject::connect(webSocket, &QWebSocket::disconnected, [=](){
        onWsDisconnect();
    });
    QObject::connect(webSocket, &QWebSocket::textMessageReceived, [=](const QString &message){
        onWsMessage(message);
    });
}

void MainWindow::onWsDisconnect()
{
    ui->wsConnectedIndicator->setStyleSheet(QString("background-color: red; color: black; font-weight:bold;"));
    ui->wsConnectedIndicator->setText(QString("Not connected"));
    qDebug() << "Disconnected from WebSocket server";
}

void MainWindow::onWsMessage(const QString &message)
{
    qDebug() << "Received message:" << message;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    if(!jsonDoc.isNull())
    {
        QJsonObject jsonObject = jsonDoc.object();

        QString value = jsonObject["message"].toString();
        addItem(value);
        updateLcdDisplay(value);
    }
}

void MainWindow::updateLcdDisplay(QString &numValue)
{
    qDebug() << "Parsed value: " << numValue.toFloat();
    ui->lcdNumber->display(numValue.toFloat());
}
