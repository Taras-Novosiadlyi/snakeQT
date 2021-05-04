#include "snake.h"
#include <fstream>

Snake::Snake(unsigned height, unsigned width, unsigned startRow, unsigned startCol)
{   
    eaten_apples = 0; // Тут -1 тому що після початку гри яблук не буде, і алгоритм зразу додасть до цієї змінної 1
    apple_coor_y = 0;
    apple_coor_x = 1;// Тут одиниця щоб яблуко не появилося на місці створення змійки

    this->height = height;
    this->width = width;

    field = new char*[height];
    for (unsigned i = 0; i < height; i++)
    {
        field[i] = new char[width];
        for (unsigned j = 0; j < width; j++)
        {
            field[i][j] = ' ';
        }

    }
    setStart(startRow, startCol);
    makeApple();
}

void Snake::setStart(unsigned int rows, unsigned int col)
{
    field[rows][col] = '*';

    if(tailCoordinates.size() == 0)
    {
        tailCoordinates.push_back({rows, col});
    }
    else
    {
        tailCoordinates.clear();
        tailCoordinates.push_back({rows, col});
    }

}

char** Snake::copyField()
{
    char **cField;
    cField = new char*[height];

    for(unsigned i = 0; i < height; i++)
    {
        cField[i] = new char[width];
        for(unsigned j = 0; j < width; j++)
        {
            cField[i][j] = field[i][j];
        }
    }

    return cField;
}

bool Snake::isAppleEaten()
{
    if(field[apple_coor_y][apple_coor_x] == 'A')
    {
        return false;
    }
    else
    {
        eaten_apples++;
        return true;
    }

}

void Snake::snakesTail(unsigned rows, unsigned cols)
{
    static unsigned int prev_score = 0;

    if(eaten_apples != 1)
    {
        tailCoordinates.push_front({rows, cols});

        if (prev_score < eaten_apples)
        {
            prev_score = eaten_apples;
            return;
        }


        field[tailCoordinates.back()[0]][tailCoordinates.back()[1]] = ' ';
        tailCoordinates.pop_back();
    }
    else
    {
        // зачищається попередня *
        field[rows][cols] = ' ';
    }

}

bool Snake::isSnakeDead()
{
    auto iter = tailCoordinates.begin();
    int currentX = 0, currentY = 0;
    while(iter != tailCoordinates.end())
    {
        currentX = (*iter)[0];
        currentY = (*iter)[1];

        iter++;

        if(currentX == (*iter)[0] && currentY == (*iter)[1])
        {
            return true;
        }
    }

    return false;
}

void Snake::setChanges()
{

    // Виводить '*' на місця колишніх координат змійки для створення іллюзії повзання
    if (tailCoordinates.size() != 0)
    {
        auto iter = tailCoordinates.begin();

        for (int i = 0; i < tailCoordinates.size(); i++)
        {
            field[(*iter)[0]][(*iter)[1]] = '*';
            iter++;
        }
    }


}

void Snake::snakeMove(char &movement)
{
    // Відбувається проста перевірка на те, який символ був введений
    if (tolower(movement) == 'w')
    {
        if(tailCoordinates.front()[0] != 0)
        {
            snakesTail(tailCoordinates.front()[0], tailCoordinates.front()[1]);
            tailCoordinates.front()[0]--;
        }
        else
        {
            snakesTail(tailCoordinates.front()[0], tailCoordinates.front()[1]);
            tailCoordinates.front()[0] = height-1;
        }

    }
    else if (tolower(movement) == 's')
    {
        if(tailCoordinates.front()[0] != height-1)
        {
            snakesTail(tailCoordinates.front()[0], tailCoordinates.front()[1]);
            tailCoordinates.front()[0]++;
        }
        else
        {
            snakesTail(tailCoordinates.front()[0], tailCoordinates.front()[1]);
            tailCoordinates.front()[0] = 0;
        }
    }
    else if (tolower(movement) == 'a')
    {
        if(tailCoordinates.front()[1] != 0)
        {
            snakesTail(tailCoordinates.front()[0], tailCoordinates.front()[1]);
            tailCoordinates.front()[1]--;
        }
        else
        {
            snakesTail(tailCoordinates.front()[0], tailCoordinates.front()[1]);
            tailCoordinates.front()[1] = width-1;
        }

    }
    else if (tolower(movement) == 'd')
    {
        if(tailCoordinates.front()[1] != width-1)
        {
            snakesTail(tailCoordinates.front()[0], tailCoordinates.front()[1]);
            tailCoordinates.front()[1]++;
        }
        else
        {
            snakesTail(tailCoordinates.front()[0], tailCoordinates.front()[1]);
            tailCoordinates.front()[1] = 0;
        }
    }

    setChanges();
}

void Snake::makeApple()
{
    // Перевіряється чи ще існує яблуко, якщо ні, то ствовюється нове, у протилежному випадку нічого не відбувається
    if (isAppleEaten())
    {
        to_initialization:    apple_coor_x = (unsigned)(rand() % width-1); // goto знаходиться в наступних двох if
                              apple_coor_y = (unsigned)(rand() % height-1);

        if (apple_coor_x > width || apple_coor_y > height) // Перевіряє чи не виходять х і у за межі поля, якщо так, то їм присвоюється нове значення
        {
            goto to_initialization;
        }

        if (field[apple_coor_y][apple_coor_x] == '*')
        {
            goto to_initialization;
        }

        field[apple_coor_y][apple_coor_x] = 'A';
    }

}
