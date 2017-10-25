#include "checkers.h"



Piece* pieces[8][8];
int startx, starty;
bool turn = true;
bool gameOver = false;
bool blackLost;
bool redLost;

Checkers::Checkers(QWidget *parent)
    : QMainWindow(parent)
{
    int x, y;
    qDebug() << "The constructor has started" << endl;
    resize(80*8,80*8);



    for (x = 0; x < 8; x++)
    {
        for (y = 0; y < 8; y++)
        {
            if (x % 2 == 0 && (y == 0 || y == 2))
                pieces[x][y] = new Piece(false);
            if (x % 2 == 1 && y == 1)
                pieces[x][y] = new Piece(false);
            if (x % 2 == 1 && (y == 5 || y == 7))
                pieces[x][y] = new Piece(true);
            if (x % 2 == 0 && y == 6)
                pieces[x][y] = new Piece(true);
        }
    }
}
void Checkers::paintEvent(QPaintEvent* e)
{


    qDebug() << "Paint event was called " << endl;

    QPainter paint(this);       //paint is an object for drawing

int x = 0;
int y = 0;
    //Checker Board
    for (y = 0; y < 480; y = y + 60)
    {
        for (x = 0; x < 480; x = x + 60)
        {
          if ((y/60) % 2 != 0)
        {
            if ((x/60) % 2 != 0)
        paint.fillRect(x, y, 60, 60, Qt::gray);
        else
        paint.fillRect(x, y, 60, 60, Qt::white);
        }
            else if ((y/60) % 2 == 0)
        {
             if ((x/60) % 2 != 0)
                 paint.fillRect(x, y, 60, 60, Qt::white);
                 else
                 paint.fillRect(x, y, 60, 60, Qt::gray);
        }
        }
    }
    for (x = 0; x < 8; x++)
    {
        for (y = 0; y < 8; y++)
        {
            if (pieces[x][y] != NULL)
                pieces[x][y]->draw(&paint, x, y);
        }
    }
}
//Draw pieces
void Piece::draw(QPainter* paint, int x, int y)
{

    if (isRed)
        paint -> setBrush(Qt::red);
    else
        paint -> setBrush(Qt::black);
    paint -> drawEllipse(QPoint(x*60+60/2,y*60+60/2),60/2-4,60/2-4);
    if (isKing)
    {
        paint -> setBrush(Qt::white);
        paint -> drawEllipse(QPoint(x*60+60/2,y*60+60/2),30/2-4,30/2-4);
    }

}
void Checkers::mousePressEvent(QMouseEvent* event)

{
    if (gameOver == true)
        return;

            startx = event->x()/60;
            starty = event->y()/60;
    qDebug()<<"Mouse was pressed "<<startx<<" "<<starty<<endl;
}

void Checkers::mouseReleaseEvent(QMouseEvent* event)
{
    if (gameOver == true)
        return;

    int middlex, middley;
    int endx, endy;

            endx = event->x()/60;
            endy = event->y()/60;



if (pieces[startx][starty]->canMove(startx, starty, endx, endy))
{



    if (abs(startx - endx) == 2 && abs(starty - endy) == 2 )
    {
        middlex = startx+(endx - startx)/2;
        middley = starty+(endy - starty)/2;
        pieces[middlex][middley] = NULL;
    }


    if (pieces[startx][starty]->isRed == true)
    {
        if (endy == 0)
            pieces[startx][starty]->isKing = true;
    }

    if (pieces[startx][starty]->isRed == false)
    {
        if (endy == 7)
            pieces[startx][starty]->isKing = true;
    }


    if (turn == true)
    {

      if (pieces[startx][starty] -> isRed == true)
        {
    pieces[endx][endy] = pieces[startx][starty];
    pieces[startx][starty] = NULL;
    repaint();
    }
}


turn = false;
CheckVictory();

       RandomAI();
CheckVictory();

}
}




Checkers::~Checkers()
{

}

Piece::Piece(bool color)
{
  isRed = color;
}

bool Piece::canMove(int startx, int starty, int endx, int endy)
{


    int middlex, middley;
    if (startx < 0 || startx > 7)
        return false;
    if (endx < 0 || endx > 7)
        return false;
    if (starty < 0 || starty > 7)
        return false;
    if (endy < 0 || endy > 7)
        return false;
    if (pieces[endx][endy] != NULL)
        return false;
    if (isKing == false)
    {
        if (isRed)
        {
            if (endy > starty)
              return false;
        }
        if (isRed == false)
        {
            if (endy < starty)
                return false;
        }
    }
    if ((abs(startx - endx) != 1 && abs(startx - endx) != 2) || (abs(starty - endy) != 1 && abs(starty - endy) != 2))
        return false;
    if (abs(startx - endx) != abs(starty - endy))
        return false;
     if (abs(startx - endx) == 2)
    {
        middlex = startx+(endx - startx)/2;
        middley = starty+(endy - starty)/2;

        if (pieces[middlex][middley] == NULL)
            return false;
         if (pieces[middlex][middley] -> isRed == isRed)
                return false;
     }



         return true;
  }

void Checkers::RandomAI()
{

    int endx, endy, middlex, middley;
if (gameOver == true)
    return;
    while (true)
{



        if (turn == false)
        {
            if (gameOver == true)
                break;

        //qDebug() << "Start while loop" << endl;
        startx = rand()%8;
        starty = rand()%8;
        endx = rand()%8;
        endy = rand()%8;

      //  qDebug()<<" start "<<startx << " "<<starty << endl;
    //qDebug()<<"end " <<endx << " "<< endy << endl;
    if (pieces[startx][starty] != NULL)
    {
        if (pieces[startx][starty]-> isRed == false)
        {

            if (pieces[startx][starty]->canMove(startx, starty, endx, endy))
            {

                if (pieces[startx][starty]->isRed == false)
                {
                    if (endy == 7)
                        pieces[startx][starty]->isKing = true;
                    if (abs(startx - endx) == 2 && abs(starty - endy) == 2 )
                    {
                        middlex = startx+(endx - startx)/2;
                        middley = starty+(endy - starty)/2;
                        pieces[middlex][middley] = NULL;
                    }

            pieces[endx][endy] = pieces[startx][starty];
            pieces[startx][starty] = NULL;
            repaint();

            }
                break;
          }
        }
     }
}
      }
    turn = true;
}

void Checkers::CheckVictory()
{

       blackLost = true;
       redLost = true;
       qDebug() << "blackLost equals:  " << blackLost << endl;
        for (int x = 0; x < 8; x++)
        {
            qDebug() << "Entered the x for loop: " << x << endl;
            for (int y = 0; y < 8; y++)
            {
                qDebug() << "Entered the y for loop: " << y << endl;
               if (pieces[x][y] == NULL)
                    continue;

                        qDebug() << "If statement went thru" << endl;

                     for (int a = 0; a < 8; a++)
                     {
                         for (int b = 0; b < 8; b++)
                         {
                            if (pieces[x][y] -> canMove(x, y, a, b) == true)
                              {
                                 if (pieces[x][y]-> isRed == false )

                                     blackLost = false;
                                 else
                                     redLost = false;

                               }
                         }
                    }

              }
   }

    qDebug() << "If blacklost is true then this if runs:" << endl;
    if (blackLost == true)
    {
        gameOver = true;
         setWindowTitle("Victory: Red Wins");
    }

    qDebug() << "If redlost is true then this if runs:" << endl;
    if (redLost == true)
    {
         gameOver = true;
         setWindowTitle("Victory: Black Wins");
    }
}





