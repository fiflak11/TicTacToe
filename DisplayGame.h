#ifndef DISPLAYGAME_H
#define DISPLAYGAME_H
#include <SFML/Graphics.hpp>
class TicTacToe;

class DisplayGame
{
    int boardSize;
    void drawBoard(sf::RenderWindow&, TicTacToe);
    int getSquareClickedID(int);
        public:
    DisplayGame(int boardSize) : boardSize(boardSize) {}
    void start(int);
};
#endif
