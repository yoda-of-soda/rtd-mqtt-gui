#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QListView>
#include <QtWebSockets>
#include "container.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAddRecord_clicked();
    void on_btnConnect_clicked();
    void initWebsocket(QStringList topics);
    void connectWebsocket();
    void onWsDisconnect();
    void onWsMessage(const QString &message);
    container* determineContainer(QString containerId);
    void addItem(const QString &message, QString containerId);
    void updateLcdDisplay(QString &numValue, QString containerId);
    void changeConnectionIndicator();
    void changeConnectionIndicator(bool shouldBeConnected);

private:
    Ui::MainWindow *ui;
    std::map<QString, container*> containers;
    QWebSocket *webSocket;
};
#endif // MAINWINDOW_H
