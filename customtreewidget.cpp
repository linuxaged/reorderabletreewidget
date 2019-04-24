#include "customtreewidget.h"
#include <QDebug>
CustomTreeWidget::CustomTreeWidget(QWidget* parent):QTreeWidget(parent)
{
}

void CustomTreeWidget::dragEnterEvent(QDragEnterEvent *event){
    qDebug() << "drag enter";
    draggedItem = currentItem();
    QTreeWidget::dragEnterEvent(event);
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

        }
    } else {
        qDebug() << "drop NONE";
    }
}
