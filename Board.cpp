#include "Board.h"
#include <iostream>
using namespace std;

Board::Board()
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            Box[r][c] = NULL;
        }
    }
}

Piece* Board::getPiece(int r, int c)
{
    return Box[r][c];
}

bool Board::isEmpty(int r, int c)
{
    return Box[r][c] == NULL;
}

bool Board::isEnemy(int r, int c, char color)
{
    return Box[r][c] != NULL && Box[r][c]->getColor() != color;
}

void Board::setPiece(int r, int c, Piece* p)
{
    Box[r][c] = p;
}

bool Board::isPathClear(int sr, int sc, int er, int ec)
{
    int rowStep = 0;
    int colStep = 0;

    if (er > sr)
    {
        rowStep = 1;
    }
    else if (er < sr)
    {
        rowStep = -1;
    }

    if (ec > sc)
    {
        colStep = 1;
    }
    else if (ec < sc)
    {
        colStep = -1;
    }

    int r = sr + rowStep;
    int c = sc + colStep;

    while (r != er || c != ec)
    {
        if (!isEmpty(r, c))
        {
            return false;
        }

        r += rowStep;
        c += colStep;
    }

    return true;
}

void Board::movePiece(int sr, int sc, int er, int ec)
{
    if (Box[er][ec] != NULL)
    {
        delete Box[er][ec];
    }

    Box[er][ec] = Box[sr][sc];
    Box[sr][sc] = NULL;
}

void Board::tempMove(int sr, int sc, int er, int ec, Piece*& captured)
{
    captured = Box[er][ec];
    Box[er][ec] = Box[sr][sc];
    Box[sr][sc] = NULL;
}

void Board::undoTempMove(int sr, int sc, int er, int ec, Piece* captured)
{
    Box[sr][sc] = Box[er][ec];
    Box[er][ec] = captured;
}

void Board::display()
{
    cout << endl;
    cout << CYAN << "  a b c d e f g h" << RESET << endl;

    for (int r = 0; r < 8; r++)
    {
        cout << CYAN << 8 - r << " " << RESET;

        for (int c = 0; c < 8; c++)
        {
            if (Box[r][c] == NULL)
            {
                cout << ". ";
            }
            else
            {
                if (Box[r][c]->getColor() == 'W')
                {
                    cout << CYAN << Box[r][c]->getSymbol() << RESET << " ";
                }
                else
                {
                    cout << EMERALD_GREEN << Box[r][c]->getSymbol() << RESET << " ";
                }
            }
        }

        cout << CYAN << 8 - r << RESET << endl;
    }

    cout << CYAN << "  a b c d e f g h" << RESET << endl;
    cout << endl;
}

Board::~Board()
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (Box[r][c] != NULL)
            {
                delete Box[r][c];
            }
        }
    }
}