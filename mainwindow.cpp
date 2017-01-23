#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    renderer = new Renderer();
    ui->openGLWidget = renderer;


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
   ui->pushButton->setText("clicked!");


   renderer->setSmall_r_value(1.8);
   renderer->setBig_R_value(9.0);
   renderer->update();


   ui->openGLWidget->update();
}
