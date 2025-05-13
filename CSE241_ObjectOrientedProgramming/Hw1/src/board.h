#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "piece.h"
    
class ChessBoard{
public:
    ChessBoard();
    
    void Start();
private:
    /*Member Data*/
    std::vector<std::vector<Piece> > board;

    bool checkStatus; 
    /*Is true if the board is in a check situation, false if not*/

    Piece::Color Turn; 
    /*Color of the player who has the turn*/

    static const int defaultDepth;
    /*Depth the calculations will be made by suggest function*/

    int boardRSize; /*For later purposes*/
    int boardCSize;

    /*Member Functions*/
    void changeTurn(){Turn == Piece::Color::White ? Turn = Piece::Color::Black : Turn = Piece::Color::White;} 
    /*Sets the turn to the other player*/

    void initBoard(); /*Initializes the pieces on the board to correct values*/

    int Play();       /*Main function that starts the gameplay*/

    int move(std::vector<int> val); /*Main move function, returns the error code. Returns 0 if a move has been made*/

    void printBoard(std::ostream& out)const; /*Prints the board to given std::ostream*/

    static bool coordinateValues(std::string input,std::vector<int>& res); 
    /*Returns the coordinate indexes of the given input in a vector of ints*/

    static void notation(const std::vector<int> vec);
    /*Prints the given coordinate values in chess notation*/

    bool validateMove(const std::vector<int> values)const;
    /*Validates the move according to piece spesific rules*/

    void applyMove(int cRow,int cCol,int dRow,int dCol);
    /*Applies the validated move to the board*/

    static bool specialInputs(const std::string input); /*Checks if the given input is a special input*/
                                                        /*like: 0-0,0--0,suggest,save,load,forfeit etc.*/

    bool underAttack(const Piece& p)const;        /*True if given piece is under attack, false if not*/

    const Piece& findKing()const; 
    /*Returns the referance to king piece of the player who has the turn*/

    int calcPoint(Piece::Color T)const; /*Calculates the point of the board for the given color*/

    bool gameEnded()const; /*Returns true if there is a check mate*/

    std::vector<int> suggest(int depth)const;
    /*Calculates the best board according to the points, then returns the move thats leading up to it*/

    static void possibleBoards(std::vector<ChessBoard>& boards);
    /*calculates all of the possible moves from the initial boards at given vector*/
    /*pust them into the vector then deletes the initial boards*/

    void possibleMoves(std::vector<std::vector<int> >& moves)const;
    /*calculates all of the possible moves from the callers board and puts them in given vector*/

    static void playBestMove(ChessBoard& b); 
    /*Plays the best move for the given board at depth 1*/

    void loadBoard();                        /*Loads the board from the given filename*/
    void saveBoard()const;                   /*Saves the board to a file*/
    bool validateBoard()const;

    static void printMenu();
    static void errorCodes(int code);
    static void help();
};

#endif