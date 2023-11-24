#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("主窗口");
    setWindowIcon(QIcon(":/icon.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_Update_triggered()
{
    Window *updateWindow=new Window();
    updateWindow->show();
}
