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
    containers["Item A"] = new container(ui->recordListA, ui->lastUpdatedValueA, ui->lcdNumberA);
    containers["Item B"] = new container(ui->recordListB, ui->lastUpdatedValueB, ui->lcdNumberB);
    containers["Item C"] = new container(ui->recordListC, ui->lastUpdatedValueC, ui->lcdNumberC);
    onWsDisconnect();
    initWebsocket({"Item A", "Item B", "Item C"});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAddRecord_clicked()
{
    addItem(QString("Clickbait"), "Item A");
}

const QString INDICATOR_BUTTON_DISCONNECT = "Disconnect";
const QString INDICATOR_BUTTON_CONNECT = "Connect";
const QString INDICATOR_LABEL_DISCONNECTED = "Not connected";
const QString INDICATOR_LABEL_CONNECTED = "Connected";
const QString INDICATOR_STYLE_DISCONNECTED = "background-color: red; color: black; font-weight:bold;";
const QString INDICATOR_STYLE_CONNECTED = "background-color: green; color: black; font-weight:bold;";
const QUrl WEBSOCKET_URL = QUrl("ws://127.0.0.1:4000/subscribe");

void MainWindow::on_btnConnect_clicked()
{
    changeConnectionIndicator();
}

void MainWindow::changeConnectionIndicator(bool shouldBeConnected){
    if(shouldBeConnected)
    {
        connectWebsocket();
        ui->wsConnectedIndicator->setStyleSheet(INDICATOR_STYLE_CONNECTED);
        ui->wsConnectedIndicator->setText(INDICATOR_LABEL_CONNECTED);

        QString newText = ui->btnConnect->text() == INDICATOR_BUTTON_CONNECT ? INDICATOR_BUTTON_DISCONNECT:INDICATOR_BUTTON_CONNECT;
        ui->btnConnect->setText(newText);
    }
    else
    {
        webSocket->disconnect();
        onWsDisconnect();
    }
}

void MainWindow::changeConnectionIndicator(){
    changeConnectionIndicator(ui->wsConnectedIndicator->text() == INDICATOR_LABEL_DISCONNECTED);
}

container* MainWindow::determineContainer(QString containerId)
{
    auto container = containers.find(containerId);
    if(container != containers.end())
    {
        return container->second;
    }
    return containers.begin()->second;
}

void MainWindow::addItem(const QString &value, QString containerId)
{
    QString now = QDateTime::currentDateTime().toString("dd/MM-yy hh:mm:ss");
    container* container = determineContainer(containerId);
    QStringList itemList = container->model->stringList();
    itemList.prepend(QString(now + ": " + value));
    container->model->setStringList(itemList);
    container->lastUpdated->setText(now);
}

void MainWindow::initWebsocket(QStringList topics)
{
    webSocket = new QWebSocket();
    connectWebsocket();

    // Handling signals for websocket
    QObject::connect(webSocket, &QWebSocket::connected, [=](){
        ui->wsConnectedIndicator->setStyleSheet(INDICATOR_STYLE_CONNECTED);
        ui->wsConnectedIndicator->setText(INDICATOR_LABEL_CONNECTED);
        ui->btnConnect->setText(INDICATOR_BUTTON_DISCONNECT);
        qDebug() << "Connected to WebSocket server";
        QJsonArray arr;
        for(const QString& str: topics)
        {
            arr.append(str);
        }
        QJsonObject obj;
        obj["topics"] = arr;
        webSocket->sendTextMessage(QJsonDocument(obj).toJson(QJsonDocument::Compact));
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

void MainWindow::connectWebsocket()
{
    webSocket->open(WEBSOCKET_URL);
}

void MainWindow::onWsDisconnect()
{
    ui->wsConnectedIndicator->setStyleSheet(INDICATOR_STYLE_DISCONNECTED);
    ui->wsConnectedIndicator->setText(INDICATOR_LABEL_DISCONNECTED);
    ui->btnConnect->setText(INDICATOR_BUTTON_CONNECT);
    qDebug() << "Disconnected from WebSocket server";
}

void MainWindow::onWsMessage(const QString &message)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    if(!jsonDoc.isNull())
    {
        QJsonObject jsonObject = jsonDoc.object();

        QString value = jsonObject["message"].toString();
        QString topic = jsonObject["topic"].toString();
        addItem(value, topic);
        updateLcdDisplay(value, topic);
    }
}

void MainWindow::updateLcdDisplay(QString &numValue, QString containerId)
{
    container* container = determineContainer(containerId);
    container->lcdDisplay->display(numValue.toFloat());
}
