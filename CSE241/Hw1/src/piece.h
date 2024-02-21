#ifndef PIECE_H
#define PIECE_H
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>

class Piece{
public:
    enum class Color {
        White = 'w',
        Black = 'b',
        Empty = 'e'
    };

    Piece():cCol(0),cRow(0),type('.'),hasMoved(false),color(Piece::Color::Empty){/*Left blank intentionally*/}
    /*Initializes a null piece at row->0 and collumn->0*/

    Piece(char t); 
    /*Initializes a piece with given type at coordinates 0,0*/

    Piece(int r,int c); 
    /*Initializes a null piece at row->r and collumn->c*/

    Piece(int row, int col, char type, Piece::Color clr);

    void setCol(int num);
    void setRow(int num);
    int getCol()const{ return cCol;}
    int getRow()const{ return cRow;}
    void setClr(Color clr){color = clr;}
    void changeMoved(){ hasMoved = true;}
    Color getClr()const{ return color;}
    char getType()const{ return type;}

    bool checkRules(const std::vector<std::vector<Piece> >& board,int dRow,int dCol)const;

    /*Piece spesific rulesets*/
    bool PpieceRule(const std::vector<std::vector<Piece> >& board,int dRow, int dCol)const;  
    bool NpieceRule(const std::vector<std::vector<Piece> >& board,int dRow, int dCol)const;  
    bool BpieceRule(const std::vector<std::vector<Piece> >& board,int dRow, int dCol)const;  
    bool RpieceRule(const std::vector<std::vector<Piece> >& board,int dRow, int dCol)const;  
    bool QpieceRule(const std::vector<std::vector<Piece> >& board,int dRow, int dCol)const;  
    bool KpieceRule(const std::vector<std::vector<Piece> >& board,int dRow, int dCol)const;  
    

    /*Obstacle functions checks whether or not piece can move to said coorditanes according to pieces ruleset*/
    /*There was no need for a Pawn,Knight ,Queen or King obstacle function*/
    bool Bobstacle(const std::vector<std::vector<Piece> >& board,int dRow, int dCol)const; 
    bool Robstacle(const std::vector<std::vector<Piece> >& board,int dRow, int dCol)const; 

    int piecePoint()const; /*Returns the point of the piece*/
    
private:
    int cCol, cRow;
    char type;
    bool hasMoved;

    Color color;
};

#endif