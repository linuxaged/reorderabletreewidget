#include "customdialog.h"
#include <QDebug>
#include <QProcess>

CustomDialog::CustomDialog(QWidget *parent): QDialog(parent)
{
    setWindowTitle(tr("Reorderable QTreeWidget"));

    createTreeWidget();
    createOtherWidgets();
    createLayout();
    createConnections();

    resize(350,400);
}

void CustomDialog::createTreeWidget(){
    widget = new CustomTreeWidget;
    widget->setDragDropMode(QAbstractItemView::DragDrop);
    widget->header()->close();

    QMap<QString, QStringList> treeMap;
    treeMap.insert("Asia", QStringList() << "Beijing Capital International Airport"
                   << "Dubai International Airport" << "Hong Kong International Airport"
                   << "Shanghai Pudong International Airport" << "Soekarno-Hatta International Airport"
                   << "Singapore Changi Airport");
    treeMap.insert("Europe", QStringList() << "Heathrow Airport" << "Charles de Gaulle Airport"
                   << "Amsterdam Airport Schiphol" << "Frankfurt Airport"
                   << "Istanbul AtatĆ¼rk Airport" << "Adolfo Suarez Madridā€“Barajas Airport");
    treeMap.insert("Jiangsu", QStringList() << "Nanjing" << "Wuxi" << "Changzhou" << "Xuzhou");
    QTreeWidgetItem *parentItem = Q_NULLPTR;
    QTreeWidgetItem *childItem = Q_NULLPTR;

    QMapIterator<QString, QStringList> i(treeMap);
    while (i.hasNext()) {
        i.next();
        parentItem = new QTreeWidgetItem(widget);
        parentItem->type();
        parentItem->setText(0, i.key());
        parentItem->setData(0,0, QVariant(i.key()));
        foreach (const auto& str, i.value()) {
           childItem = new QTreeWidgetItem;
           childItem->setText(0, str);
           childItem->setData(0,0, QVariant(str));
           parentItem->addChild(childItem);
        }
    }
}

void CustomDialog::createOtherWidgets(){
    viewBox = new QGroupBox(tr("Major airports"));
    buttonBox = new QDialogButtonBox;
    saveButton = buttonBox->addButton(QDialogButtonBox::Save);
    closeButton = buttonBox->addButton(QDialogButtonBox::Close);
}

void CustomDialog::createLayout(){
    QVBoxLayout* viewLayout = new QVBoxLayout;
    viewLayout->addWidget(widget);
    viewBox->setLayout(viewLayout);

    QHBoxLayout* horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(buttonBox);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(viewBox);
    mainLayout->addLayout(horizontalLayout);

    setLayout(mainLayout);
}

void CustomDialog::createConnections(){
    QObject::connect(saveButton,  &QPushButton::clicked, this, &CustomDialog::save);
    QObject::connect(closeButton, &QPushButton::clicked, this, &CustomDialog::close);
}

void CustomDialog::save(){
    QFile file("majorairports.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << "Major airports" << "\n";

    QTreeWidgetItemIterator it(widget);
    while (*it) {
        if((*it)->parent())
            out << (*it)->text(0) << "\n";
        else {
            out << "\n";
            out << (*it)->text(0) << ":\n";
        }
        ++it;
    }

    QMessageBox::information(this, tr("Reorderable QTreeWidget"),
                                   tr("The data was saved."),
                             QMessageBox::Ok);
}

void CustomDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F1) {
        qDebug() << "a pressed!";
        QProcess process(this);
        process.startDetached("reorderabletreewidget.exe");
    }
}
