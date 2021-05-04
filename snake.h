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
    void snakeMove( char &movement);
    char** copyField();
    unsigned getHeight() const {return height;}
    unsigned getWidth() const {return width;}
    long int getScore() const {return eaten_apples;}
    void makeApple();



};

#endif // SNAKE_H
