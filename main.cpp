#include <iostream>
#include "Board.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

using namespace std;

class Game
{
private:
    Board board;
    char turn;

    char oppositeColor(char c)
    {
        if (c == 'W')
        {
            return 'B';
        }
        return 'W';
    }

    bool isKingPiece(Piece* p)
    {
        if (p == NULL)
        {
            return false;
        }

        return p->getSymbol() == 'K' || p->getSymbol() == 'k';
    }

    bool findKing(char color, int& kr, int& kc)
    {
        char kingSymbol;

        if (color == 'W')
        {
            kingSymbol = 'K';
        }
        else
        {
            kingSymbol = 'k';
        }

        for (int r = 0; r < 8; r++)
        {
            for (int c = 0; c < 8; c++)
            {
                Piece* p = board.getPiece(r, c);

                if (p != NULL && p->getSymbol() == kingSymbol)
                {
                    kr = r;
                    kc = c;
                    return true;
                }
            }
        }

        return false;
    }

    bool isSquareAttacked(int row, int col, char attackerColor)
    {
        for (int r = 0; r < 8; r++)
        {
            for (int c = 0; c < 8; c++)
            {
                Piece* p = board.getPiece(r, c);

                if (p != NULL && p->getColor() == attackerColor)
                {
                    if (p->isValidMove(r, c, row, col, &board))
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool isInCheck(char color)
    {
        int kr;
        int kc;

        if (!findKing(color, kr, kc))
        {
            return true;
        }

        return isSquareAttacked(kr, kc, oppositeColor(color));
    }

    bool moveLeavesKingInCheck(int sr, int sc, int er, int ec, char color)
    {
        Piece* captured = NULL;

        board.tempMove(sr, sc, er, ec, captured);
        bool answer = isInCheck(color);
        board.undoTempMove(sr, sc, er, ec, captured);

        return answer;
    }

    bool hasAnyLegalMove(char color)
    {
        for (int sr = 0; sr < 8; sr++)
        {
            for (int sc = 0; sc < 8; sc++)
            {
                Piece* p = board.getPiece(sr, sc);

                if (p != NULL && p->getColor() == color)
                {
                    for (int er = 0; er < 8; er++)
                    {
                        for (int ec = 0; ec < 8; ec++)
                        {
                            Piece* target = board.getPiece(er, ec);

                            if (isKingPiece(target))
                            {
                                continue;
                            }

                            if (p->isValidMove(sr, sc, er, ec, &board))
                            {
                                if (!moveLeavesKingInCheck(sr, sc, er, ec, color))
                                {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }

        return false;
    }

    bool isCheckmate(char color)
    {
        if (isInCheck(color) && !hasAnyLegalMove(color))
        {
            return true;
        }

        return false;
    }

public:
    Game()
    {
        turn = 'W';
        setup();
    }

    void setup()
    {
        board.setPiece(0, 0, new Rook('B'));
        board.setPiece(0, 1, new Knight('B'));
        board.setPiece(0, 2, new Bishop('B'));
        board.setPiece(0, 3, new Queen('B'));
        board.setPiece(0, 4, new King('B'));
        board.setPiece(0, 5, new Bishop('B'));
        board.setPiece(0, 6, new Knight('B'));
        board.setPiece(0, 7, new Rook('B'));

        for (int c = 0; c < 8; c++)
        {
            board.setPiece(1, c, new Pawn('B'));
        }

        board.setPiece(7, 0, new Rook('W'));
        board.setPiece(7, 1, new Knight('W'));
        board.setPiece(7, 2, new Bishop('W'));
        board.setPiece(7, 3, new Queen('W'));
        board.setPiece(7, 4, new King('W'));
        board.setPiece(7, 5, new Bishop('W'));
        board.setPiece(7, 6, new Knight('W'));
        board.setPiece(7, 7, new Rook('W'));

        for (int c = 0; c < 8; c++)
        {
            board.setPiece(6, c, new Pawn('W'));
        }
    }

    void start()
    {
        char input[20];

        while (true)
        {
            board.display();

            if (turn == 'W')
            {
                cout << CYAN << "White turn: " << RESET;
            }
            else
            {
                cout << EMERALD_GREEN << "Black turn: " << RESET;
            }

            if (isInCheck(turn))
            {
                cout << CYAN << "Your king is in check." << RESET << endl;
            }

            cout << EMERALD_GREEN << "Enter move like a2a4 or q to quit: " << RESET;
            cin.width(20);
            cin >> input;

            if (input[0] == 'q' || input[0] == 'Q')
            {
                break;
            }

            if (input[0] == '\0' || input[1] == '\0' || input[2] == '\0' || input[3] == '\0' || input[4] != '\0')
            {
                cout << CYAN << "Invalid input. Use format like e2e4." << RESET << endl;
                continue;
            }

            if (input[0] < 'a' || input[0] > 'h' || input[2] < 'a' || input[2] > 'h' || input[1] < '1' || input[1] > '8' || input[3] < '1' || input[3] > '8')
            {
                cout << CYAN << "Invalid square." << RESET << endl;
                continue;
            }

            int sc = input[0] - 'a';
            int sr = 8 - (input[1] - '0');
            int ec = input[2] - 'a';
            int er = 8 - (input[3] - '0');

            Piece* p = board.getPiece(sr, sc);

            if (p == NULL)
            {
                cout << CYAN << "No piece there." << RESET << endl;
                continue;
            }

            if (p->getColor() != turn)
            {
                cout << CYAN << "That is not your piece." << RESET << endl;
                continue;
            }

            Piece* target = board.getPiece(er, ec);

            if (isKingPiece(target))
            {
                cout << CYAN << "You cannot capture the king. Give checkmate instead." << RESET << endl;
                continue;
            }

            if (!p->isValidMove(sr, sc, er, ec, &board))
            {
                cout << CYAN << "Invalid move." << RESET << endl;
                continue;
            }

            if (moveLeavesKingInCheck(sr, sc, er, ec, turn))
            {
                cout << CYAN << "Invalid move. Your king will be in check." << RESET << endl;
                continue;
            }

            board.movePiece(sr, sc, er, ec);

            char opponent = oppositeColor(turn);

            if (isCheckmate(opponent))
            {
                board.display();

                if (turn == 'W')
                {
                    cout << CYAN << "White wins by checkmate!" << RESET << endl;
                }
                else
                {
                    cout << EMERALD_GREEN << "Black wins by checkmate!" << RESET << endl;
                }

                break;
            }

            if (isInCheck(opponent))
            {
                cout << CYAN << "Check!" << RESET << endl;
            }

            turn = opponent;
        }
    }
};

int main()
{
    int choice;

    do
    {
        cout << CYAN << "Chess Game" << RESET << endl;
        cout << EMERALD_GREEN << "1. Play Game" << RESET << endl;
        cout << EMERALD_GREEN << "2. Read Instructions" << RESET << endl;
        cout << EMERALD_GREEN << "0. Quit" << RESET << endl;
        cout << CYAN << "Enter what you want to do: " << RESET;
        cin >> choice;

        if (choice == 1)
        {
            Game game;
            game.start();
        }
        else if (choice == 2)
        {
            cout << endl;
            cout << CYAN << "CHESS INSTRUCTIONS" << RESET << endl;
            cout << EMERALD_GREEN << "Enter moves like e2e4." << RESET << endl;
            cout << EMERALD_GREEN << "White pieces are capital letters." << RESET << endl;
            cout << EMERALD_GREEN << "Black pieces are small letters." << RESET << endl;
            cout << EMERALD_GREEN << "Pawn moves forward 1 square." << RESET << endl;
            cout << EMERALD_GREEN << "Pawn can move 2 squares on first move." << RESET << endl;
            cout << EMERALD_GREEN << "Pawn captures diagonally." << RESET << endl;
            cout << EMERALD_GREEN << "Rook moves straight." << RESET << endl;
            cout << EMERALD_GREEN << "Knight moves in L shape." << RESET << endl;
            cout << EMERALD_GREEN << "Bishop moves diagonally." << RESET << endl;
            cout << EMERALD_GREEN << "Queen moves straight and diagonally." << RESET << endl;
            cout << EMERALD_GREEN << "King moves one square." << RESET << endl;
            cout << EMERALD_GREEN << "This version includes check and checkmate." << RESET << endl;
            cout << EMERALD_GREEN << "This version does not include castling, en passant, or promotion." << RESET << endl;
            cout << endl;
        }
        else if (choice == 0)
        {
            cout << CYAN << "No game is played." << RESET << endl;
        }
        else
        {
            cout << CYAN << "Wrong option." << RESET << endl;
        }

    } while (choice != 0);

    return 0;
}