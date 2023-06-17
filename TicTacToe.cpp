#include "TicTacToe.h"
#include <vector>
#include <time.h>
#include <iostream>

using namespace std;

TicTacToe::TicTacToe(int boardSize)
{
    srand(time(NULL));
    this->numSymbols=(boardSize/2)+2;
    std::vector<int> line;
    for(int i{0}; i<boardSize; i++)
    {
        line.push_back(0);
    }
    for(int i{0}; i<boardSize; i++)
    {
        this->board.push_back(line);
    }
}
bool TicTacToe::makeMove(int x, int y)
{
    if(this->board[x][y]==0)
    {
        if(this->turn)
            this->board[x][y]=1;
        else
            this->board[x][y]=-1;
        this->turn=!(this->turn);
        return true;
    }
    else
        return false;
}
void TicTacToe::makeRandomMove()
{
    while(true)
    {
        int randomX = rand()%this->board.size(), randomY = rand()%this->board.size();
        if(this->board[randomX][randomY]==0)
        {
            this->makeMove(randomX,randomY);
            break;
        }
    }
}
bool TicTacToe::makeLastMove()
{
    int x{0},y{0};
    for(auto line : this->board)
    {
        for(auto square : line)
        {
            if(square==0)
            {
                std::vector<std::vector<int>> copyBoard = this->board;
                copyBoard[y][x]=-1;
                if(isEnd(copyBoard)==-1)
                {
                    makeMove(y,x);
                    return true;
                }
            }
            x++;
        }
        x=0; y++;
    }
    return false;
}
bool TicTacToe::findSequence(std::vector<int> line, int symbol, int amount)
{
    for(int i{0}; i<line.size()-amount+1; i++)
    {
        if(line[i]==symbol)
        {
            for(int j{0}; j<amount; i++,j++)
            {
                if(line[i]!=symbol)
                    break;
                if(j==amount-1)
                    return true;
            }
        }
    }
    return false;
}
int TicTacToe::isEnd(vector<vector<int>> b)
{
    //CHECKING HORIZONTAL LINES "-"
    for(auto row : b)
    {
        if (findSequence(row,1,this->numSymbols))
            return 1;
        if (findSequence(row,-1,this->numSymbols))
            return -1;
    }
    //CHECKING VERTICAL LINES "|"
    for(int i{0}; i<b.size(); i++)
    {
        std::vector<int> column;
        for(auto row : b)
        {
            column.push_back(row[i]);
        }
        if (findSequence(column,1,this->numSymbols))
            return 1;
        if (findSequence(column,-1,this->numSymbols))
            return -1;
    }
    //CHECKING DIAGONAL LINES "\"
    for(int i{0}, j{0};i<b.size();i++,j=i)
    {
        std::vector<int> diagonal;
        for(auto row : this->board)
        {
            if(j>=b.size())
                break;
            diagonal.push_back(row[j++]);
        }
        if(this->numSymbols<=diagonal.size())
        {
            if (findSequence(diagonal,1,this->numSymbols))
                return 1;
            if (findSequence(diagonal,-1,this->numSymbols))
                return -1;
        }

    }
    for(int i{0}, j{0}, k{0}; i<b.size(); i++,j=0,k=0)
    {
        std::vector<int> diagonal;
        for(auto row : b)
        {
            if(k++<=i)
                continue;
            diagonal.push_back(row[j++]);
        }
        if(this->numSymbols<=diagonal.size())
        {
            if (findSequence(diagonal,1,this->numSymbols))
                return 1;
            if (findSequence(diagonal,-1,this->numSymbols))
                return -1;
        }
    }
    //CHECKING DIAGONAL LINES "/"
    for(int i=b.size()-1,j=i; i>=0; i--,j=i)
    {
        std::vector<int> diagonal;
        for(auto row : b)
        {
            if(j>=0)
                diagonal.push_back(row[j--]);
        }
        if(this->numSymbols<=diagonal.size())
        {
            if (findSequence(diagonal,1,this->numSymbols))
                return 1;
            if (findSequence(diagonal,-1,this->numSymbols))
                return -1;
        }
    }
    for(int i=b.size()-1,j=i,k=i; i>0; i--,j=b.size()-1,k=b.size()-1)
    {
        std::vector<int> diagonal;
        for(auto row : b)
        {
            if(k-->i)
                continue;
            diagonal.push_back(row[j--]);
        }
        if(this->numSymbols<=diagonal.size())
        {
            if (findSequence(diagonal,1,this->numSymbols))
                return 1;
            if (findSequence(diagonal,-1,this->numSymbols))
                return -1;
        }
    }
    for(auto row : b)
    {
        for(auto square : row)
        {
            if(square==0)
                return 2;
        }
    }
    return 0;
}
