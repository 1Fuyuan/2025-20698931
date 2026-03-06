#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

#include <vtkSmartPointer.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class vtkRenderer;
class vtkGenericOpenGLRenderWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTreeItemDoubleClicked(const QModelIndex &index);
    void on_loadButton_clicked();
    void on_resetButton_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *treeModel;

    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
};

#endif // MAINWINDOW_H
