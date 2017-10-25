#ifndef CHECKERS_H
#define CHECKERS_H

#include "checkers.h"
#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>


class Checkers : public QMainWindow
{
    Q_OBJECT

public:
    Checkers(QWidget *parent = 0);
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void RandomAI();
    void ComputersMove();
    bool gameOver;
    void CheckVictory();
    ~Checkers();
};

class Piece
{
public:
    bool isRed;
    bool isKing;
    Piece(bool color);
    void draw(QPainter* paint, int x, int y);
    bool canMove(int startx, int starty, int endx, int endy);
};

#endif //CHECKERS_H
