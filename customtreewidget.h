#ifndef CUSTOMTREEWIDGET_H
#define CUSTOMTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDropEvent>

class CustomTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    CustomTreeWidget(QWidget *parent = nullptr);
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
private:
    QPoint m_dragStartPos;
};

#endif // CUSTOMTREEWIDGET_H
