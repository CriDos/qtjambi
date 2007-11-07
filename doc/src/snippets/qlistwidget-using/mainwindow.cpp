#include <QtGui>

#include "mainwindow.h"

MainWindow::MainWindow()
{
    QMenu *fileMenu = new QMenu(tr("&File"));

    QAction *quitAction = fileMenu->addAction(tr("E&xit"));
    quitAction->setShortcut(tr("Ctrl+Q"));

    QMenu *itemsMenu = new QMenu(tr("&Items"));

    insertAction = itemsMenu->addAction(tr("&Insert Item"));
    removeAction = itemsMenu->addAction(tr("&Remove Item"));
    QAction *ascendingAction = itemsMenu->addAction(tr("Sort in &Ascending Order"));
    QAction *descendingAction = itemsMenu->addAction(tr("Sort in &Descending Order"));

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(itemsMenu);

/*  For convenient quoting:
//! [0]
    QListWidget *listWidget = new QListWidget(this);
//! [0]
*/
    listWidget = new QListWidget(this);
    listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(ascendingAction, SIGNAL(triggered()), this, SLOT(sortAscending()));
    connect(descendingAction, SIGNAL(triggered()), this, SLOT(sortDescending()));
    connect(insertAction, SIGNAL(triggered()), this, SLOT(insertItem()));
    connect(removeAction, SIGNAL(triggered()), this, SLOT(removeItem()));
    connect(listWidget,
            SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(updateMenus(QListWidgetItem *)));

    setupListItems();
    updateMenus(listWidget->currentItem());

    setCentralWidget(listWidget);
    setWindowTitle(tr("List Widget"));
}

void MainWindow::setupListItems()
{
//! [1]
    new QListWidgetItem(tr("Oak"), listWidget);
    new QListWidgetItem(tr("Fir"), listWidget);
    new QListWidgetItem(tr("Pine"), listWidget);
//! [1]
    new QListWidgetItem(tr("Birch"), listWidget);
//! [2]
    new QListWidgetItem(tr("Hazel"), listWidget);
//! [2]
    new QListWidgetItem(tr("Redwood"), listWidget);
//! [3]
    new QListWidgetItem(tr("Sycamore"), listWidget);
    new QListWidgetItem(tr("Chestnut"), listWidget);
    new QListWidgetItem(tr("Mahogany"), listWidget);
//! [3]
}

void MainWindow::sortAscending()
{
//! [4]
    listWidget->sortItems(Qt::AscendingOrder);
//! [4]
}

void MainWindow::sortDescending()
{
//! [5]
    listWidget->sortItems(Qt::DescendingOrder);
//! [5]
}

void MainWindow::insertItem()
{
    if (!listWidget->currentItem())
        return;

    QString itemText = QInputDialog::getText(this, tr("Insert Item"),
        tr("Input text for the new item:"));

    if (itemText.isNull())
        return;

//! [6]
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(itemText);
//! [6]
    int row = listWidget->row(listWidget->currentItem());
//! [7]
    listWidget->insertItem(row, newItem);
//! [7]

    QString toolTipText = tr("Tooltip:") + itemText;
    QString statusTipText = tr("Status tip:") + itemText;
    QString whatsThisText = tr("What's This?:") + itemText;
//! [8]
    newItem->setToolTip(toolTipText);
    newItem->setStatusTip(toolTipText);
    newItem->setWhatsThis(whatsThisText);
//! [8]
}

void MainWindow::removeItem()
{
    listWidget->takeItem(listWidget->row(listWidget->currentItem()));
}

void MainWindow::updateMenus(QListWidgetItem *current)
{
    insertAction->setEnabled(current != 0);
    removeAction->setEnabled(current != 0);
}
