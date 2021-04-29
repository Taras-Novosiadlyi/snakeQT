#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void countTime();
private slots:
    void on_action20x20_triggered();
    void makeField(int rows, int columns);
    void playGame(int rows, int colums);
    //void countTime(bool &runTimer);

    void on_gameField_cellClicked(int row, int column);



private:
    Ui::MainWindow *ui;

    QTimer *timer;
    std::chrono::time_point<std::chrono::system_clock> startTimeCount;
};
#endif // MAINWINDOW_H
