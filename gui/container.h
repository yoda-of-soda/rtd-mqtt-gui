#ifndef CONTAINER_H
#define CONTAINER_H

#include <QStringListModel>
#include <QListView>
#include <QLCDNumber>
#include <QLabel>

class container
{
public:
    container(QListView* _listView, QLabel* _lastUpdated, QLCDNumber* lcd);
    QStringListModel* model;
    QListView* listView;
    QLabel* lastUpdated;
    QLCDNumber* lcdDisplay;
};

#endif // CONTAINER_H
