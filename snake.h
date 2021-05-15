#ifndef SNAKE_H
#define SNAKE_H

#include <cstdlib>
#include <list>
#include <vector>
#include <cctype>

class Snake
{
private:
    char **field;
    //unsigned prev_score;

    unsigned height, width;
    unsigned apple_coor_x, apple_coor_y;
    long int eaten_apples;
    std::list<std::vector<unsigned>> tailCoordinates;


    void setStart(unsigned rows, unsigned col);

    bool isAppleEaten();
    void snakesTail(unsigned rows, unsigned cols);
    void setChanges();
    bool isSnakeDead();


public:

    Snake(unsigned height, unsigned width, unsigned startRow = 0, unsigned startCol = 0);
    int snakeMove( char &movement);
    char** copyField();
    unsigned getHeight() const {return height;}
    unsigned getWidth() const {return width;}
    long int getScore() const {return eaten_apples;}
    void makeApple();

    unsigned getHeadX()const {return tailCoordinates.front()[0];}
    unsigned getHeadY()const {return tailCoordinates.front()[1];}



};

#endif // SNAKE_H
