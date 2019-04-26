#ifndef THUMBNAILTREEITEMDATA_H
#define THUMBNAILTREEITEMDATA_H

#include <QMimeData>
#include <QTreeWidgetItem>

class ThumbnailTreeItemData : public QMimeData
{
public:
    QTreeWidgetItem * getTreeItem() const{ return m_treeItem; }
    void setTreeItem(QTreeWidgetItem *treeItem) { m_treeItem = treeItem; }
private:
    QTreeWidgetItem *m_treeItem;
};

#endif // THUMBNAILTREEITEMDATA_H
