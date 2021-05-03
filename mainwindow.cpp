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
    movement = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(countTime()));
    connect(timer, SIGNAL(timeout()), this, SLOT(printField()));
    connect(movement, SIGNAL(timeout()), this, SLOT(move()));

    game = nullptr;


}

MainWindow::~MainWindow()
{
    delete ui;

    if(game != nullptr)
    {
        delete game;
    }
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
    QTableWidgetItem item;
    for (int i = 0; i < rows ; i++)
    {
        for (int j = 0;j < columns ; j++ )
        {
            ui->gameField->setItem(i, j, new QTableWidgetItem);
            ui->gameField->item(i, j)->setFlags(ui->gameField->item(i, j)->flags() & ~Qt::ItemIsSelectable);
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

    game = new Snake(rows, columns);

}

int MainWindow::move()
{
    game->makeApple();
    QString direction = ui->inputLineEd->text();

    if(direction.size() == 0)
    {
        return 0;
    }

    if(direction.size() > 1)
    {
        char buf = direction.toStdString()[direction.size()-1];

        ui->inputLineEd->setText(QChar(buf));
    }

    char move = ui->inputLineEd->text().toStdString()[0];

    if(move == '0')
    {
        return 1;
    }

    game->snakeMove(move);


    return 0;

}

void MainWindow::printField()
{
    char **field = game->copyField();

    for(unsigned i = 0; i < game->getHeight(); i++)
    {
        for (unsigned j = 0; j < game->getWidth() ; j++)
        {
            if(field[i][j] == '*')
            {
                ui->gameField->item(i, j)->setBackground(Qt::red);
            }
            else if(field[i][j] == 'A')
            {
                ui->gameField->item(i, j)->setBackground(Qt::yellow);
            }
            else
            {
                ui->gameField->item(i, j)->setBackground(Qt::green);
            }
        }
    }

    delete [] field;
}

void MainWindow::playGame(int rows, int columns)
{
    ui->inputLineEd->setText(QChar('d'));
    makeField(rows, columns);

    startTimeCount = std::chrono::system_clock::now();

    timer->start(1);
    movement->start(400);

}

void MainWindow::on_action20x20_triggered()
{

    playGame(10, 10);
}



void MainWindow::on_gameField_cellClicked(int row, int column)
{
    ui->inputLineEd->setFocus();
}
