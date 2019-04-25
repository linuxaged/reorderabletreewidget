#include "customtreewidget.h"
#include <QDebug>
CustomTreeWidget::CustomTreeWidget(QWidget* parent):QTreeWidget(parent)
{
}

void CustomTreeWidget::dragEnterEvent(QDragEnterEvent *event){
    qDebug() << "drag enter";
//    draggedItem = currentItem();
    {
        auto treeWidget = qobject_cast<QTreeWidget*>(event->source());
        draggedItem = treeWidget->currentItem();
    }
    QTreeWidget::dragEnterEvent(event);
}

void CustomTreeWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    qDebug() << "drag leave" << currentItem();
}

void CustomTreeWidget::dropEvent(QDropEvent *event){
    QModelIndex droppedIndex = indexAt(event->pos());
    if( !droppedIndex.isValid() ) {
        qDebug() << "drop index not valid";
        return;
    }

    if(draggedItem){
        QTreeWidgetItem* dragParent = draggedItem->parent();
        if(dragParent){
            qDebug() << "drop NEW 0";

            auto dropParent = itemFromIndex(droppedIndex.parent());
            if(dropParent && dropParent != dragParent) {
                qDebug() << "drop other item" << dropParent;
                dragParent->removeChild(draggedItem);
                dropParent->insertChild(droppedIndex.row(), draggedItem);
                return;
            } else {
                qDebug() << "drop NEW 1";
                dragParent->removeChild(draggedItem);
                dragParent->insertChild(droppedIndex.row(), draggedItem);
            }
        } else { //
            auto treeWidget = draggedItem->treeWidget();
            auto index = treeWidget->indexOfTopLevelItem(draggedItem);
            auto take = treeWidget->takeTopLevelItem(index);
            //
            treeWidget->insertTopLevelItem(droppedIndex.column(), take);
        }
    } else {
        qDebug() << "drop NONE";
    }
}
