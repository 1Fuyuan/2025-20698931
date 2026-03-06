#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

// VTK
#include <vtkNew.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCylinderSource.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , treeModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    // 1) Create VTK render window and attach to the promoted Qt widget
    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    ui->widget->setRenderWindow(renderWindow);

    // 2) Create a renderer and add to render window
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    // 3) Cylinder
    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(8);

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(cylinder->GetOutputPort());

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(1.0, 0.0, 0.35);
    actor->RotateX(30.0);
    actor->RotateY(-45.0);

    renderer->AddActor(actor);
    renderer->ResetCamera();
    renderWindow->Render();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTreeItemDoubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
}

void MainWindow::on_loadButton_clicked()
{
}

void MainWindow::on_resetButton_clicked()
{
}
