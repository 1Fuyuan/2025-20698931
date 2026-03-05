#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStatusBar>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFileInfo>
#include <QModelIndex>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->treeView, &QTreeView::doubleClicked,
            this, &MainWindow::onTreeItemDoubleClicked);

    // 创建树视图模型（Tree Model）
    treeModel = new QStandardItemModel(this);

    // 设置表头（Header）
    treeModel->setHorizontalHeaderLabels(QStringList() << "Items");

    // 第一组：Models
    QStandardItem *modelsRoot = new QStandardItem("Models");
    modelsRoot->appendRow(new QStandardItem("Part A"));
    modelsRoot->appendRow(new QStandardItem("Part B"));

    // 第二组：Settings
    QStandardItem *settingsRoot = new QStandardItem("Settings");
    settingsRoot->appendRow(new QStandardItem("Display"));
    settingsRoot->appendRow(new QStandardItem("Import"));

    // 把根节点加到模型里
    treeModel->appendRow(modelsRoot);
    treeModel->appendRow(settingsRoot);

    // 把模型绑定到 TreeView（树视图）
    ui->treeView->setModel(treeModel);

    // 展开所有节点（方便你一眼看到内容）
    ui->treeView->expandAll();

    // 状态栏提示
    statusBar()->showMessage("TreeView model loaded", 2000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Open File",
        "",
        "All Files (*.*)"
        );

    if (fileName.isEmpty()) {
        statusBar()->showMessage("No file selected");
        return;
    }

    QString shortName = QFileInfo(fileName).fileName();

    QStandardItem *modelsRoot = treeModel->item(0, 0);
    if (!modelsRoot) {
        statusBar()->showMessage("Models root not found");
        return;
    }

    // 检查是否已存在同名项（防重复）
    for (int i = 0; i < modelsRoot->rowCount(); ++i) {
        QStandardItem *child = modelsRoot->child(i);
        if (child && child->text() == shortName) {
            statusBar()->showMessage("File already in list: " + shortName, 3000);
            return;
        }
    }

    // 添加新文件名到 Models 下
    modelsRoot->appendRow(new QStandardItem(shortName));
    ui->treeView->expandAll();

    statusBar()->showMessage("Selected: " + fileName, 4000);
}


void MainWindow::on_resetButton_clicked()
{
    QStandardItem *modelsRoot = treeModel->item(0, 0);

    if (modelsRoot) {
        // 清空 Models 下所有子项
        modelsRoot->removeRows(0, modelsRoot->rowCount());

        // 恢复默认项
        modelsRoot->appendRow(new QStandardItem("Part A"));
        modelsRoot->appendRow(new QStandardItem("Part B"));
    }

    ui->treeView->expandAll();
    statusBar()->showMessage("Tree reset", 2000);
}

void MainWindow::onTreeItemDoubleClicked(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }

    QString itemText = index.data().toString();
    statusBar()->showMessage("Double-clicked: " + itemText, 3000);
}
