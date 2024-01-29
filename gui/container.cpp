#include "container.h"

container::container(QListView* _listView, QLabel* _lastUpdated, QLCDNumber* lcd)
{
    listView = _listView;
    model = new QStringListModel();
    listView->setModel(model);
    lastUpdated = _lastUpdated;
    lcdDisplay = lcd;
}
