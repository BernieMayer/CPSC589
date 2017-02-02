#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    QVBoxLayout * layout = new QVBoxLayout();



    renderer = new Renderer();
    layout->addWidget(renderer);

    ui->setupUi(this);


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
   renderer->redrawGraph();
   renderer->update();
   renderer->t = 0;

}
