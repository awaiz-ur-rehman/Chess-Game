#ifndef Board_H
#define Board_H

#include "Piece.h"

#define CYAN "\033[36m"
#define EMERALD_GREEN "\033[38;2;80;200;120m"
#define RESET "\033[0m"

class Board
{
private:
    Piece* Box[8][8];

public:
    Board();
    Piece* getPiece(int r, int c);
    bool isEmpty(int r, int c);
    bool isEnemy(int r, int c, char color);
    void setPiece(int r, int c, Piece* p);
    bool isPathClear(int sr, int sc, int er, int ec);
    void movePiece(int sr, int sc, int er, int ec);
    void tempMove(int sr, int sc, int er, int ec, Piece*& captured);
    void undoTempMove(int sr, int sc, int er, int ec, Piece* captured);
    void display();
    ~Board();
};

#endif
