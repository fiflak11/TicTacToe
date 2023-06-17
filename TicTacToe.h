#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <vector>

class DisplayGame;

class TicTacToe
{
    std::vector<std::vector<int>> board;
    bool turn = true; // true X, false O
    int numSymbols;
    TicTacToe(int);
    bool makeMove(int,int); //return true if move is possible and change board
    void makeRandomMove();
    bool makeLastMove(); //return true if is there only one move to win for random player
    bool findSequence(std::vector<int>,int,int);
    int isEnd(std::vector<std::vector<int>>);
    friend class DisplayGame;
};
#endif
