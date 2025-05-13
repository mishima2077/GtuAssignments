#include "piece.h"

Piece::Piece(int row, int col, char tp, Piece::Color clr){
    setCol(col);
    setRow(row);
    type = tp;
    color = clr;
    hasMoved = false;
}

Piece::Piece(int r,int c){
    setCol(c);
    setRow(r);
    type = '.';
    color = Color::Empty;
    hasMoved = false;
}

Piece::Piece(char t){
    if(!isalpha(t) && t != '.')
        exit(-1);
    
    type = t;
    hasMoved = false;
}

void Piece::setCol(int num){
        if(num < 0 || num > 7)
            exit(-1);
        cCol = num;
}

void Piece::setRow(int num){
        if(num < 0 || num > 7)
            exit(-1);
        cRow = num;
}

int Piece::piecePoint()const{
    switch(type){       
        case 'R':
        case 'r': return 5;

        case 'N':
        case 'n': return 3;

        case 'B':
        case 'b': return 3;

        case 'Q':
        case 'q':  return 9;

        case 'K':
        case 'k': return 0;

        case 'P':
        case 'p': return 1;
        
        default: return 0;
    }
    return 0;
}

bool Piece::checkRules(const std::vector<std::vector<Piece> >& board,int dRow,int dCol)const{
    if(dRow > 7 || dRow < 0 || dCol > 7 || dCol < 0)             /*In bound check*/
        return false;
    if(color == board[dRow][dCol].getClr()) /*Same color pieces can't take each other*/
        return false;

    bool res = false;
    switch(type){       /*Piece spesific checks*/
        case 'R':
        case 'r': res = RpieceRule(board, dRow, dCol);
            break;

        case 'N':
        case 'n': res = NpieceRule(board, dRow, dCol);
            break;

        case 'B':
        case 'b': res = BpieceRule(board, dRow, dCol);
            break;

        case 'Q':
        case 'q': res = QpieceRule(board, dRow, dCol);
            break;

        case 'K':
        case 'k': res = KpieceRule(board, dRow, dCol);
            break;

        case 'P':
        case 'p': res = PpieceRule(board, dRow, dCol);
            break;
        
        default: break;
    }
    return res;
}

/*Piece spesific ruleset function definitions*/

bool Piece::RpieceRule(const std::vector<std::vector<Piece> >& board,int dRow, int dCol)const{
    bool res=false;
    if(dRow - cRow == 0 || dCol - cCol == 0)
        res = true;

    return res && Robstacle(board,dRow,dCol);
}

bool Piece::Robstacle(const std::vector<std::vector<Piece> >& board,int dRow, int dCol)const{
    int i;
    if(dRow - cRow == 0 && dCol > cCol){
        for(i = cCol+1; i < dCol; ++i){
            if(board[cRow][i].getType() != '.')
                return false;
        }
    }
    if(dRow - cRow == 0 && dCol < cCol){
        for(i = cCol-1; i > dCol; --i){
            if(board[cRow][i].getType() != '.')
                return false;
        }
    }
    if(dCol - cCol == 0 && dRow > cRow){
        for(i = cRow+1; i < dRow; ++i){
            if(board[i][cCol].getType() != '.')
                return false;
        }
    }
    if(dCol - cCol == 0 && dRow < cRow){
        for(i = cRow-1; i > dRow; --i){
            if(board[i][cCol].getType() != '.')
                return false;
        }
    }
    return true;
}

bool Piece::NpieceRule(const std::vector<std::vector<Piece> >& board,int dRow, int dCol)const{
    if((dRow == cRow+2 && (dCol == cCol+1 || dCol == cCol-1)) || (dRow == cRow-2 && (dCol == cCol + 1 || dCol == cCol -1)) ||
       (dCol == cCol+2 && (dRow == cRow+1 || dRow == cRow-1)) || (dCol == cCol-2 && (dRow == cRow + 1 || dRow == cRow -1)))
        return true;

    return false;
}
//There was no need for a Knight obstacle function

bool Piece::BpieceRule(const std::vector<std::vector<Piece> >& board,int dRow, int dCol)const{
    bool res = false;
    if(abs(dRow - cRow) == abs(dCol - cCol))
        res = true;

    return res && Bobstacle(board,dRow,dCol);
}

bool Piece::Bobstacle(const std::vector<std::vector<Piece> >& board,int dRow, int dCol)const{
    int i;
    if(dRow > cRow && dCol > cCol){
        for(i = 1; i < dRow-cRow; ++i){
            if(board[cRow+i][cCol+i].getType() != '.')
                return false;
        }
    }
    if(dRow > cRow && dCol < cCol){
        for(i = 1; i < dRow-cRow; ++i){
            if(board[cRow+i][cCol-i].getType() != '.')
                return false;
        }
    }
    if(dRow < cRow && dCol > cCol){
        for(i = 1; i < dCol-cCol; ++i){
            if(board[cRow-i][cCol+i].getType() != '.')
                return false;
        }
    }
    if(dRow < cRow && dCol < cCol){
        for(i = 1; i < cCol - dCol; ++i){
            if(board[cRow-i][cCol-i].getType() != '.')
                return false;
        }
    }
    return true;
}

bool Piece::QpieceRule(const std::vector<std::vector<Piece> >& board,int dRow, int dCol)const{
    bool Rrule = RpieceRule(board,dRow,dCol),Brule = BpieceRule(board,dRow,dCol);
    bool res = Rrule || Brule;

    return Rrule==true ? res && Robstacle(board,dRow,dCol) : res && Bobstacle(board,dRow,dCol);
}
//Queen obstacle function uses either Rooks or Bishops obstacle function, thus there was no need of writing one

bool Piece::KpieceRule(const std::vector<std::vector<Piece> >& board,int dRow, int dCol)const{
    if(abs(dRow-cRow)<=1 && abs(dCol-cCol)<=1)
        return true;

    return false;
}
//There was no need for a King obstacle function

bool Piece::PpieceRule(const std::vector<std::vector<Piece> >& board,int dRow, int dCol)const{ 
    bool res;
    if(color == Piece::Color::White){
        if(dCol == cCol){
            if(dRow - cRow == 1 && board[dRow][dCol].getType() == '.') return true;
            else if(dRow - cRow == 2 && cRow == 1 && board[dRow-1][dCol].getType() == '.' && board[dRow][dCol].getType() == '.') return true;
        }
        else if(abs(dCol - cCol) == 1 && dRow - cRow==1 && board[dRow][dCol].getClr()==Piece::Color::Black) return true;
    }
    else{
        if(dCol == cCol){
            if(cRow - dRow == 1 && board[dRow][dCol].getType() == '.') return true;
            else if(cRow - dRow == 2 && cRow == 6 && board[dRow+1][dCol].getType() == '.' && board[dRow][dCol].getType() == '.') return true;
        }
        else if(abs(dCol - cCol) == 1 && cRow - dRow==1 && board[dRow][dCol].getClr()==Piece::Color::White) return true;
    }

    return false;
}
//There was no need for a pawn obstacle function