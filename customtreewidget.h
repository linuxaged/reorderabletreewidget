#ifndef CUSTOMTREEWIDGET_H
#define CUSTOMTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDropEvent>

class CustomTreeWidget : public QTreeWidget
{
public:
    CustomTreeWidget(QWidget *parent = nullptr);
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
private:
    QTreeWidgetItem* draggedItem;
};

#endif // CUSTOMTREEWIDGET_H
