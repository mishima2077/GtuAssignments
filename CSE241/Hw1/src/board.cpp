#include "board.h"
const int ChessBoard::defaultDepth = 3; /*Default depth for suggest functions calculations*/

ChessBoard::ChessBoard():board{
    {'R','N','B','Q','K','B','N','R'},
    {'P','P','P','P','P','P','P','P'},
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.'},
    {'p','p','p','p','p','p','p','p'},
    {'r','n','b','q','k','b','n','r'}
}{
    initBoard();
    boardCSize = 8;
    boardRSize = 8;
}

void ChessBoard::initBoard(){
    for(int row = 0; row < 8; ++row){
        for(int col = 0; col < 8; ++col){
            board[row][col].setRow(row);
            board[row][col].setCol(col);
        }
    }

    for(int row = 0; row < 2; ++row)
        for(int col = 0; col < 8; ++col)
            board[row][col].setClr(Piece::Color::White);

    for(int row = 2; row < 6; ++row)
        for(int col = 0; col < 8; ++col)
            board[row][col].setClr(Piece::Color::Empty);

    for(int row = 6; row < 8; ++row)
        for(int col = 0; col < 8; ++col)
            board[row][col].setClr(Piece::Color::Black);

    Turn = Piece::Color::White;
    checkStatus = false;
}

void ChessBoard::Start(){
    bool session_ended = false;
    bool game_played = false;
    char input;
    std::cout << "WELCOME TO THE CHESS GAME\n\nGTU 241 HOMEWORK_1\n\nADIL MERT ERGORUN\n";
    do{
        if(game_played) *this = ChessBoard(); /*Sets the board to its default position if a game has been played on it*/
        ChessBoard::printMenu();
        input = std::cin.get();
        switch(input){
            case '1': std::cout << "!Type exit if you want to end the game, do not terminate the code in any other way!\n Good Luck!\n\n";
                    Play();
                    game_played = true;
                    session_ended = false;
                    break;
            case '2': loadBoard();
                    if(validateBoard()){
                        std::cout << "Board loaded succesfully! Good Luck!!\n\n";
                        Play();
                        game_played = true;
                        session_ended = false;
                    }
                    else{
                        std::cout << "Invalid board. Check if the filename is correct, or try another file.\n";
                        game_played = false;
                        session_ended = false;
                    }
                    break;
            case '3': ChessBoard::help();
                      game_played = false;
                      session_ended = false;
                    break;
            case '4': session_ended = true;
                      game_played = false;
                    break;
            default:std::cout << "Invalid input! Try again.\n";
                    session_ended = false;
                    game_played = false;
                    break;
        }
        while(std::cin.get() != '\n'); /*Clears the buffer*/
    }while(session_ended == false);
}

int ChessBoard::Play(){
    std::string in;
    std::vector<int> values;
    bool ended = false;
    bool moveMade = false;
    int msgCode;
    while(!ended){
        checkStatus = underAttack(findKing());
        
        if(checkStatus && gameEnded()){
            if(Turn == Piece::Color::White) std::cout << "Black Won!\n";
            else std::cout << "White Won!\n";
            ended = true;
            return 0;
        }
        else if(checkStatus) std::cout <<  "    !CHECK!    \n";

        printBoard(std::cout);

        do{
            if(Turn == Piece::Color::White)
                std::cout << "\n[White Players Turn]\n";
            else
                std::cout << "\n[Black Players Turn]\n";

            std::cin >> in;
            if(in == "suggest"){
                std::cout << "Calculating...\n";
                values = suggest(ChessBoard::defaultDepth);
                applyMove(values[0],values[1],values[2],values[3]);
                std::cout << "Suggestion: ";
                notation(values);
                moveMade = true;
                msgCode = 0;
            }
            else if(in == "save"){
                saveBoard();
                moveMade = false;
                msgCode = 0;
            }
            else if(in == "load"){
                loadBoard();
                if(validateBoard()){
                    std::cout << "Board loaded succesfully!\n";
                    printBoard(std::cout);
                    moveMade = false;
                    msgCode = 0;
                }
                else{
                    std::cout << "Invalid board. Exitting the game.\n\n";
                    ended = true;
                    return -1;
                }
            }
            else if(in == "exit"){
                std::cout << "Ending the game.\n";
                return 0;
            }
            else if(in == "help"){
                ChessBoard::help();
                moveMade = false;
                msgCode = 0;
            }
            else if(coordinateValues(in,values)){
                msgCode = move(values);
                if(msgCode==0) moveMade = true;
                else moveMade = false;
            }
            else{
                moveMade = false;
                msgCode = 1;
            }
            ChessBoard::errorCodes(msgCode);
        }while(moveMade == false);
        changeTurn();
    }
    return -1;
}

int ChessBoard::move(std::vector<int> values){
    for(int i = 0; i < 4; ++i){ /*Input must be in bounds of the board*/
        if(values[i] < 0 || values[i] > 7) return 2;
    }

    if(!validateMove(values)){ /*This part checks the move according to chess rules*/
        return 3;
    }

    int cRow = values[0], cCol = values[1];
    int dRow = values[2], dCol = values[3];

    applyMove(cRow,cCol,dRow,dCol);
    board[dRow][dCol].changeMoved();
    return 0;
}

bool ChessBoard::validateMove(const std::vector<int> values)const{
    int cRow = values[0], cCol = values[1];
    int dRow = values[2], dCol = values[3];
    if(Turn != board[cRow][cCol].getClr()) /*Checks if the player is moving its own*/
        return false;                      /*pieces or not*/  

    if(cRow == dRow && cCol == dCol)
        return false;             /*Current position and destination can't be same*/

    bool res = board[cRow][cCol].checkRules(board,dRow,dCol);

    Piece tempP;
    ChessBoard tempB = *this;
    bool isResultaCheck;
    if(res){
        tempP = board[dRow][dCol];
        tempB.applyMove(cRow,cCol,dRow,dCol);
        isResultaCheck = tempB.underAttack(tempB.findKing());
        if(isResultaCheck) res = false;
    }
    
    return res;
}

void ChessBoard::printBoard(std::ostream& out)const{
    for(int row = 7; row >= 0; --row){
        out << row+1 << " | ";
        for(int col = 0; col < 8; ++col)
            out << board[row][col].getType() << " ";

        out << "\n";
    }

    out << "    ";
    for(int i = 0; i < 15; ++i)
        out << "-";
    out << "\n";

    char files = 'a';
    out << "    ";
    for(int i = 0; i < 8; ++i){
        out << files << " ";
        ++files;
    }
    out << "\n";
}

void ChessBoard::loadBoard(){
    std::ifstream in;
    std::string filename;
    std::cout << "Filename to load the game: ";
    std::cin >> filename;
    in.open(filename);
    if(!in.is_open()){
        std::cout << "File couldn't be opened. Terminating the program.\n";
        exit(-1);
    }

    std::string turn;
    Piece::Color side;
    char ch;
    in >> turn;

    if(turn == "White") Turn = Piece::Color::White;
    else if(turn == "Black") Turn = Piece::Color::Black;
    else Turn = Piece::Color::Empty;

    in.get();
    for(int r = 7; r >= 0; --r){
        for(int i = 0; i < 4; ++i) in.get();
        for(int c = 0; c < 8; ++c){
            ch = in.get();
            in.get();
            if(ch == '.') side = Piece::Color::Empty;
            else if(isupper(ch)) side = Piece::Color::White;
            else side = Piece::Color::Black;
            board[r][c] = Piece(r,c,ch,side);
        }
        in.get();
    }

    in.close();
}

bool ChessBoard::validateBoard()const{
    ChessBoard temp = *this;
    bool check1,check2;
    check1 = temp.underAttack(findKing());
    temp.changeTurn();
    check2 = temp.underAttack(findKing());

    if(check1 && check2) return false;
    return true;
}

void ChessBoard::saveBoard()const{
    std::ofstream outFile;
    std::string file_name;
    std::cout << "File name to write: ";
    std::cin >> file_name;
    outFile.open(file_name);
    if(!outFile.is_open()){
        std::cout << "File couldn't be opened. Terminating the program.\n";
        exit(-1);
    }
    
    if(Turn == Piece::Color::White) outFile << "White\n";
    else outFile << "Black\n";
    printBoard(outFile);
    outFile.close();
    std::cout << "Board saved succesfully! You can continue your game.\n";
}

bool ChessBoard::coordinateValues(std::string input,std::vector<int>& res){
    bool valid= true;

    if(input.length()!=4)
        valid = false;

    if(!isalpha(input[0]) || !isdigit(input[1]) || !isalpha(input[2]) || !isdigit(input[3]))
        valid = false;             /*This parts checks if the input is in the desired notation*/

    if(valid == false) return false;
    
    res.clear();
    res.push_back(input[1] - '0' - 1); /*Current Row index*/
    res.push_back(input[0] - 97);      /*Current Collumn index*/

    res.push_back(input[3] - '0' - 1); /*Destination Row index*/
    res.push_back(input[2] - 97);      /*Destination Collumn index*/
    return valid;
}

void ChessBoard::notation(const std::vector<int> vec){
    char cCol = vec[1] + 97;
    char cRow = vec[0] + '0' + 1;
    char dCol = vec[3] + 97;
    char dRow = vec[2] + '0' + 1;
    std::cout << cCol << cRow << dCol << dRow << "\n";
}  

bool ChessBoard::underAttack(const Piece& p)const{
    int cRow = p.getRow(), cCol = p.getCol();

    int row,col;
    for(row = 0; row < 8; ++row){
        for(col = 0; col < 8; ++col){
            if(board[row][col].getClr() != p.getClr()){
                if(p.RpieceRule(board,row,col) && (board[row][col].getType() == 'r' || board[row][col].getType() == 'R'||
                                                   board[row][col].getType() == 'q' || board[row][col].getType() == 'Q'))
                    return true;
                else if(p.BpieceRule(board,row,col) && (board[row][col].getType() == 'b' || board[row][col].getType() == 'B'||
                                                        board[row][col].getType() == 'q' || board[row][col].getType() == 'Q'))
                    return true;
                else if(p.NpieceRule(board,row,col) && (board[row][col].getType() == 'n' || board[row][col].getType() == 'N'))
                    return true;
                else if(row == cRow+1 && (col == cCol-1 || col == cCol+1) && board[row][col].getType() == 'p')
                    return true;
                else if(row == cRow-1 && (col == cCol-1 || col == cCol+1) && board[row][col].getType() == 'P')
                    return true;
            }
        }
    }
    return false;
}

void ChessBoard::applyMove(int cRow,int cCol,int dRow,int dCol){
    board[dRow][dCol] = board[cRow][cCol];
    board[dRow][dCol].setCol(dCol);
    board[dRow][dCol].setRow(dRow);
    board[cRow][cCol] = Piece(cRow,cCol);
}

const Piece& ChessBoard::findKing()const{
    for(int row = 0; row < 8; ++row){
        for(int col = 0; col < 8; ++col){
            if((board[row][col].getType() == 'K' && Turn == Piece::Color::White)||(board[row][col].getType() == 'k' && Turn == Piece::Color::Black))
                return board[row][col];
        }
    }
    std::cout << "\n!!There is no king of given color in at the board, terminating the program.\n";
    exit(-1); 
}

int ChessBoard::calcPoint(Piece::Color T)const{
    double totalP = 0.0,p;
    for(int r = 0; r < 8; ++r){
        for(int c = 0; c < 8; ++c){
            p = board[r][c].piecePoint();    

            if(underAttack(board[r][c])) p = p/2;

            if(board[r][c].getClr() == T) totalP += p;
            else totalP -= p;
        }
    }
    return totalP;
}

bool ChessBoard::gameEnded()const{
    int row,col,mRow,mCol;
    ChessBoard temp = *this;

    for(row = 0; row < 8; ++row){
        for(col = 0; col < 8; ++col){
            if(temp.board[row][col].getClr() == temp.Turn){
                for(mRow = 0; mRow < 8; ++mRow){
                    for(mCol = 0; mCol < 8; ++mCol){
                        if(temp.validateMove({row,col,mRow,mCol})) return false;
                    }
                }
            }
        }
    }
    return true;
}

bool ChessBoard::specialInputs(const std::string in){
    return false;
}

std::vector<int> ChessBoard::suggest(int depth)const{
    std::vector<ChessBoard> firstBoards; /*firstBoards holds all of the possible moves after 1 move*/

    std::vector<ChessBoard> laterBoards; /*laterBoards holds all of the possible boards of given depth for*/
                                         /*one of the possible first moves*/
    std::vector<std::vector<int> > firstMoves;  /*firstMoves holds all of the possible first moves*/
    firstBoards.push_back(*this);
    
    firstBoards[0].possibleMoves(firstMoves); 
    ChessBoard::possibleBoards(firstBoards); /*possibleBoards takes a board vector which already has at least one board in it. Function */
                                             /*generates all of the possible boards (at given depth) from the initial boards at the vector*/
                                             /*and puts the generated boards to the vector. Function then erases the initial boards*/
    int fBoardNum = firstBoards.size();

    int bestMoveIndex=0;
    double currentScore,bestScore;
    bool mated_board;

    for(int i = 0; i < fBoardNum; ++i) if(firstBoards[i].gameEnded()) return firstMoves[i];
    /*This part checks for mate in ones.*/

    double loadBarCount = static_cast<double>(fBoardNum);
    for(int i = 0; i < fBoardNum; ++i){
        laterBoards.clear();
        laterBoards.push_back(firstBoards[i]);
        mated_board = false;
        for(int j = 1; j < depth; ++j){
            for(int k = 0; k < laterBoards.size(); ++k){ /*This part checks if there is a mated board in the vector*/
                if(laterBoards[k].gameEnded()){          /*If that is the case, program doesn't try to calculate the boards for more depths*/
                    mated_board = true;
                    j = depth;
                }
            }
            if(mated_board == false){
                for(int k = 0; k < laterBoards.size(); ++k){ ChessBoard::playBestMove(laterBoards[k]);} /*playBestMove plays the best move for the opponent,*/
                possibleBoards(laterBoards);                                                            /*which is basically a depth 1 suggestion in our case*/
            }
        }

        if(i==0 && laterBoards.size()!=0){ 
                        /*Score can be negative, so initializing the bestScore with a value would be a bad design choice*/
                        /*Instead, bestScore starts with the first of the generated boards score*/
                bestScore = laterBoards[0].calcPoint(Turn);
                bestMoveIndex = i;
        }
        for(int j = 0; j < laterBoards.size(); ++j){
            currentScore = laterBoards[j].calcPoint(Turn);
            if(currentScore > bestScore){
                bestScore = currentScore;
                bestMoveIndex = i;
            }
        }
    }

    return firstMoves[bestMoveIndex];
}

void ChessBoard::possibleBoards(std::vector<ChessBoard>& boards){
    int row,col,mRow,mCol;
    int fSize = boards.size();
    ChessBoard temp;
    Piece tempP;
    for(int i = 0; i < fSize; ++i){
        temp = boards[i];
        for(row = 0; row < 8; ++row){
            for(col = 0; col < 8; ++col){
                for(mRow = 0; mRow < 8; ++mRow){
                    for(mCol = 0; mCol < 8; ++mCol){
                        if(temp.validateMove({row,col,mRow,mCol})){
                            tempP = temp.board[mRow][mCol];
                            temp.applyMove(row,col,mRow,mCol);
                            temp.changeTurn();
                            boards.push_back(temp);
                            temp.applyMove(mRow,mCol,row,col);
                            temp.board[mRow][mCol] = tempP;
                            temp.changeTurn();
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < fSize; ++i) boards.erase(boards.begin());
}
void ChessBoard::possibleMoves(std::vector<std::vector<int> >& moves)const{
    int row,col,mRow,mCol;
    for(row = 0; row < 8; ++row){
        for(col = 0; col < 8; ++col){
            for(mRow = 0; mRow < 8; ++mRow){
                for(mCol = 0; mCol < 8; ++mCol){
                    if(validateMove({row,col,mRow,mCol})) moves.push_back({row,col,mRow,mCol});
                }
            }
        }
    }
}

void ChessBoard::playBestMove(ChessBoard& b){
    std::vector<ChessBoard> firstBoards;
    std::vector<std::vector<int> > firstMoves;
    firstBoards.push_back(b);
    
    b.possibleMoves(firstMoves);
    ChessBoard::possibleBoards(firstBoards);
    int fBoardNum = firstBoards.size();

    int bestMoveIndex=0,currentScore,bestScore=-1;
    for(int i = 0; i < fBoardNum; ++i){
        currentScore = firstBoards[i].calcPoint(b.Turn);
        if(currentScore > bestScore){
            bestScore = currentScore;
            bestMoveIndex = i;
        }
    }

    int cRow = firstMoves[bestMoveIndex].at(0),cCol = firstMoves[bestMoveIndex].at(1);
    int dRow = firstMoves[bestMoveIndex].at(2),dCol = firstMoves[bestMoveIndex].at(3);
    b.applyMove(cRow,cCol,dRow,dCol);
    b.changeTurn();
}

void ChessBoard::printMenu(){
    std::cout << "\n(1) Play!\n";
    std::cout << "(2) Load a game!\n";
    std::cout << "(3) Help\n";
    std::cout << "(4) Exit.\n";
    std::cout << "> ";
}

void ChessBoard::errorCodes(int code){
    switch(code){
        case 0: break;
        case 1: std::cout << "Non valid input! Try again.\n";
            break;
        case 2: std::cout << "Input is out of bounds!\n";
            break;
        case 3: std::cout << "Chess rules doesn't allow that!\n";
            break;
        default:std::cout << "Invalid.\n";
    }
}

void ChessBoard::help(){
    std::cout << "Commands you can write during the game \n\n";
    std::cout << "suggest : finds the best move for the player who \n"
              <<  "has the turn at default depth (3) and plays it\n\n";
    std::cout << "save : saves the game to a file\n\n";
    std::cout << "load : loads a board from a file\n\n";
    std::cout << "exit : ends the game and returns to the main menu\n\n";
    std::cout << "help : prints out this menu of commands\n";
}
