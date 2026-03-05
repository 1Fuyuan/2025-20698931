#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTreeItemDoubleClicked(const QModelIndex &index);

    void on_loadButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *treeModel;
};
#endif // MAINWINDOW_H
