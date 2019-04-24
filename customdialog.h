#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QTreeWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QHeaderView>
#include "customtreewidget.h"
#include <QTreeWidgetItemIterator>

class CustomDialog : public QDialog
{
    Q_OBJECT
public:
    CustomDialog(QWidget *parent = Q_NULLPTR);
public slots:
    void save();
private:
    QTreeWidget* widget;
    QDialogButtonBox* buttonBox;
    QGroupBox* viewBox;
    QPushButton* saveButton;
    QPushButton* closeButton;

    void createTreeWidget();
    void createOtherWidgets();
    void createLayout();
    void createConnections();
};

#endif // CUSTOMDIALOG_H
