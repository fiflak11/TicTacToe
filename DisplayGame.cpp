#include "DisplayGame.h"
#include "TicTacToe.h"
#include <SFML/Graphics.hpp>

int DisplayGame::getSquareClickedID(int x)
{
    int a = x,i{0};
    while(a>=0)
    {
        i++;
        a-=70;
    }
    if(x%70>=20)
        return i;
    else
        return -1;
}
void DisplayGame::drawBoard(sf::RenderWindow& window, TicTacToe game)
{
    int y{20};
    int x{20};
    for(auto line : game.board)
    {
        for(auto t : line)
        {
            sf::RectangleShape rect(sf::Vector2f(50,50));
            rect.setFillColor(sf::Color::Green);
            rect.setPosition(x,y);
            window.draw(rect);
            if(t==1)
            {
                sf::CircleShape circle(23);
                circle.setFillColor(sf::Color::Red);
                circle.setPosition(x+2,y+2);
                window.draw(circle);
                circle.setFillColor(sf::Color::Green);
                circle.setPosition(x+8,y+8);
                circle.setRadius(17);
                window.draw(circle);
            }
            if(t==-1)
            {
                sf::RectangleShape line(sf::Vector2f(50,6));
                line.setFillColor(sf::Color::Red);
                line.setOrigin(25,3);
                line.setPosition(x+25,y+25);
                line.rotate(45);
                window.draw(line);
                line.rotate(90);
                window.draw(line);
            }
            x+=70;
        }
        x=20;
        y+=70;
    }
}
void DisplayGame::start(int player) // number of players
{
    bool e=false; // is end flag
    int xSize=this->boardSize*50+(this->boardSize+1)*20;
    TicTacToe game(this->boardSize);
    sf::RenderWindow window(sf::VideoMode(xSize, xSize), "Tic Tac Toe");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                int xBoard=this->getSquareClickedID(sf::Mouse::getPosition(window).x); //return -1 if mouse is on black side
                int yBoard=this->getSquareClickedID(sf::Mouse::getPosition(window).y);
                if(xBoard!=-1 && yBoard!=-1 && game.board[yBoard-1][xBoard-1]==0)
                {
                    game.makeMove(yBoard-1,xBoard-1);
                    if(game.isEnd(game.board)!=2)
                        e=true;
                    if(player==1)
                    {
                        if(game.makeLastMove()==false)
                        {
                            game.makeRandomMove();
                        }
                        if(game.isEnd(game.board)!=2)
                            e=true;
                    }
                }
            }
        }

        window.clear();
        this->drawBoard(window,game);
        if(e)
        {
            sf::Font font;
            font.loadFromFile("SansSerif.ttf");
            sf::Text win;
            win.setFont(font);
            win.setCharacterSize(30);
            win.setFillColor(sf::Color::Blue);
            if(game.isEnd(game.board)==1)
                win.setString("O   WIN");
            else
                win.setString("X   WIN");
            window.draw(win);
        }
        window.display();

    }
}
