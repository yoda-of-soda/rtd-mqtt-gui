#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QListView>
#include <QtWebSockets>

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
    void initWebsocket();
    void onWsDisconnect();
    void onWsMessage(const QString &message);
    void addItem(const QString &message);
    void updateLcdDisplay(QString &numValue);

private:
    Ui::MainWindow *ui;
    QListView *listView;
    QStringListModel *model;
    QWebSocket *webSocket;
};
#endif // MAINWINDOW_H
