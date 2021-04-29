#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <chrono>
#include <thread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(500, 400);
    ui->inputLineEd->setFocus();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(countTime()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::countTime()
{

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> time = end - startTimeCount;

    ui->TimeOutput->setText(QString::number(time.count()));
}

void MainWindow::makeField(int rows, int columns)
{
    ui->inputLineEd->setFocus();
    //Create columns
    ui->gameField->setRowCount(rows);
    ui->gameField->setColumnCount(columns);

    //initialize columns
    for (int i = 0; i < rows ; i++)
    {
        for (int j = 0;j < columns ; j++ )
        {
            ui->gameField->setItem(i, j, new QTableWidgetItem);
        }
    }

    ui->gameField->verticalHeader()->hide();
    ui->gameField->horizontalHeader()->hide();

    ui->gameField->horizontalHeader()->setDefaultSectionSize(5);
    ui->gameField->verticalHeader()->setDefaultSectionSize(5);

    //Set table size
    ui->gameField->setMaximumWidth(412);
    ui->gameField->setMinimumWidth(412);
    ui->gameField->setMaximumHeight(222);
    ui->gameField->setMinimumHeight(222);
    //

    ui->gameField->setShowGrid(false);

}

/*void MainWindow::countTime(bool &runTimer)
{
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> time;

    while(runTimer)
    {
        time = end - start;

        ui->TimeOutput->setText(QString::number(time.count()));

        end = std::chrono::system_clock::now();
    }
}*/

void MainWindow::playGame(int rows, int columns)
{
    makeField(rows, columns);

    startTimeCount = std::chrono::system_clock::now();

    timer->start(1);



}

void MainWindow::on_action20x20_triggered()
{
    playGame(10, 10);
}



void MainWindow::on_gameField_cellClicked(int row, int column)
{
    ui->inputLineEd->setFocus();
}
