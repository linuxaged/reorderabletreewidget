#include "customtreewidget.h"
#include "thumbnailtreeitemdata.h"
#include <QDebug>
#include <QApplication>
#include <QDrag>

CustomTreeWidget::CustomTreeWidget(QWidget* parent):QTreeWidget(parent)
{
}

void CustomTreeWidget::dragEnterEvent(QDragEnterEvent *event){
    qDebug() << "drag enter";
    QTreeWidget::dragEnterEvent(event);
}

void CustomTreeWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    qDebug() << "drag leave" << currentItem();

    auto index = currentIndex();
    QModelIndexList indices{index};
    auto mime = model()->mimeData(indices);
    Q_ASSERT(mime);
    mime->setData("text/plain", "madi asd asdf ");
    qDebug() << mime->text();
    QTreeWidget::dragLeaveEvent(event);
}

void CustomTreeWidget::dragMoveEvent(QDragMoveEvent *event)
{
//    qDebug() << "drag move";
    QTreeWidget::dragMoveEvent(event);
}

void CustomTreeWidget::dropEvent(QDropEvent *event){
    QModelIndex droppedIndex = indexAt(event->pos());
    if( !droppedIndex.isValid() ) {
        qDebug() << "drop index not valid";
        return;
    }

    // mime data
    {
        auto mime = event->mimeData();
        qDebug() << "mime: " << mime->text();
    }

    auto sourceWidget = qobject_cast<CustomTreeWidget*>(event->source());
    Q_ASSERT(event->source());
    qDebug() << "event source class:" << event->source()->metaObject()->className();
    Q_ASSERT(sourceWidget);
    // 是不是外来的
    QTreeWidgetItem *draggedItem;
    if (sourceWidget == this) {
        draggedItem = currentItem();
    } else {
        draggedItem = sourceWidget->currentItem();
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

    event->accept();
}
