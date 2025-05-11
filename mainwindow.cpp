#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->checkBox->addState("Sine");
    ui->checkBox->addState("Square");
    ui->checkBox->addState("Triangle");
    ui->checkBox->addState("Sawtooth");
    ui->checkBox->addState("Noise");
    ui->checkBox->addState("S/H");
}

MainWindow::~MainWindow()
{
    delete ui;
}
