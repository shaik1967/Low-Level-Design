#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <cstdlib>

using namespace std;

class MovementStrategy;
class GameContext;

//16 pieces black and white
// one king
// one queen
// two rooks
// two bishops
// two knights
// eight pawns

enum Color{
    WHITE,
    BLACK,
    EMPTY
};

class Player{
    string name;
    Color playerColor;
    public:
        Player(string name, Color playerColor):name(name),playerColor(playerColor) {}
        string get_playerName(){
            return name;
        }
        Color get_playerColor(){
            return playerColor;
        }
};

// Factory Pattern to create pieces
enum class PieceType {
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn
};

class Cell;

class Piece {
protected:
    PieceType type;
    Color color;
    bool killed = false;
    MovementStrategy *movementStrategy = nullptr;
public:
    Piece(Color color) : color(color) {}
    Color get_color() { return color; }
    PieceType get_type() { return type; }
    bool isKilled() { return killed; }
    void setKilled() { killed = true; }
    bool make_movement(Cell *startCell, Cell *endCell);
};

class Cell {
    int row, col;
    Piece *piece;
public:
    Cell(int row, int col) : row(row), col(col), piece(nullptr) {}
    void set_piece(Piece *piece) { this->piece = piece; }
    Piece *get_piece() { return piece; }
    int get_row() { return row; }
    int get_col() { return col; }
    bool make_movement(Cell *endCell);
};

class MovementStrategy {
    public:
         virtual bool make_movement(Cell *startCell, Cell *endCell)=0;
};

class KingMovementStrategy: public MovementStrategy{
    public:
        bool make_movement(Cell *startCell, Cell *endCell) override{
            int startRow = startCell->get_row();
            int startCol = startCell->get_col();
            int endRow = endCell->get_row();
            int endCol = endCell->get_col();
            int tot_distance = abs(startRow-endRow)+abs(startCol-endCol);
            if(tot_distance==1){
                //kill if it is not empty
                Piece *destinationPiece = endCell->get_piece();
                if(destinationPiece){
                    destinationPiece->setKilled();
                    endCell->set_piece(nullptr);
                }
                endCell->set_piece(startCell->get_piece());
                startCell->set_piece(nullptr);
                return true;
            }
            else return false;
        }
};

class QueenMovementStrategy: public MovementStrategy{
    public:
        bool make_movement(Cell *startCell, Cell *endCell) override{
            int startRow = startCell->get_row();
            int startCol = startCell->get_col();
            int endRow = endCell->get_row();
            int endCol = endCell->get_col();
            if(startRow==endRow || startCol==endCol||abs(startRow-endRow)==abs(startCol-endCol)){
                //kill if it is not empty
                Piece *destinationPiece = endCell->get_piece();
                if(destinationPiece){
                    destinationPiece->setKilled();
                    endCell->set_piece(nullptr);
                }
                endCell->set_piece(startCell->get_piece());
                startCell->set_piece(nullptr);
                return true;
            }
            else return false;
        }
};

class RookMovementStrategy: public MovementStrategy{
    public:
        bool make_movement(Cell *startCell, Cell *endCell) override{
            int startRow = startCell->get_row();
            int startCol = startCell->get_col();
            int endRow = endCell->get_row();
            int endCol = endCell->get_col();
            if(startRow==endRow || startCol==endCol){
                Piece *destinationPiece = endCell->get_piece();
                if(destinationPiece){
                    destinationPiece->setKilled();
                    endCell->set_piece(nullptr);
                }
                endCell->set_piece(startCell->get_piece());
                startCell->set_piece(nullptr);
                return true;
            }
            else return false;
        }
};


class BishopMovementStrategy: public MovementStrategy{
    public:
        bool make_movement(Cell *startCell, Cell *endCell) override{
            int startRow = startCell->get_row();
            int startCol = startCell->get_col();
            int endRow = endCell->get_row();
            int endCol = endCell->get_col();
            if(abs(startRow-endRow)==abs(startCol-endCol)){
                Piece *destinationPiece = endCell->get_piece();
                if(destinationPiece){
                    destinationPiece->setKilled();
                    endCell->set_piece(nullptr);
                }
                endCell->set_piece(startCell->get_piece());
                startCell->set_piece(nullptr);
                return true;
            }
            else return false;
        }
};


class KnightMovementStrategy: public MovementStrategy{
    public:
        bool make_movement(Cell *startCell, Cell *endCell) override{
            int startRow = startCell->get_row();
            int startCol = startCell->get_col();
            int endRow = endCell->get_row();
            int endCol = endCell->get_col();
            if((abs(startRow-endRow)==1 && abs(startCol-endCol)==2) || (abs(startRow-endRow)==2 && abs(startCol-endCol)==1)){
                Piece *destinationPiece = endCell->get_piece();
                if(destinationPiece){
                    destinationPiece->setKilled();
                    endCell->set_piece(nullptr);
                }
                // Now let's move the source piece to the destination cell
                endCell->set_piece(startCell->get_piece());
                startCell->set_piece(nullptr);
                return true;
            }
            else return false;
        }
};


class PawnMovementStrategy: public MovementStrategy{
    public:
        bool make_movement(Cell *startCell, Cell *endCell) override{
            int startRow = startCell->get_row();
            int startCol = startCell->get_col();
            int endRow = endCell->get_row();
            int endCol = endCell->get_col();
            if(abs(startRow-endRow)==1 && abs(startCol-endCol)==1){
                Piece *destinationPiece = endCell->get_piece();
                if(destinationPiece){
                    destinationPiece->setKilled();
                    endCell->set_piece(nullptr);
                }
                endCell->set_piece(startCell->get_piece());
                startCell->set_piece(nullptr);
                return true;
            }
            else if(abs(startRow-endRow)==1 && abs(startCol-endCol)==0){
                Piece *destinationPiece = endCell->get_piece();
                if(destinationPiece)return false;
                endCell->set_piece(startCell->get_piece());
                startCell->set_piece(nullptr);
                return true;
            }
            else return false;
        }
    };  

bool Piece::make_movement(Cell *startCell, Cell *endCell) {
    return movementStrategy->make_movement(startCell, endCell);
}

class King: public Piece{
    public:
    King(Color color):Piece(color) {
        type = PieceType::King;
        movementStrategy = new KingMovementStrategy();
    }

};

class Queen: public Piece{
    public:
    Queen(Color color):Piece(color) {
        type = PieceType::Queen;
        movementStrategy = new QueenMovementStrategy();
    }
};

class Rook: public Piece{
    public:
    Rook(Color color):Piece(color) {
        type = PieceType::Rook;
        movementStrategy = new RookMovementStrategy();
    }
};

class Bishop: public Piece{
    public:
    Bishop(Color color):Piece(color) {
        type = PieceType::Bishop;
        movementStrategy = new BishopMovementStrategy();
    }
};

class Knight: public Piece{
    public:
    Knight(Color color):Piece(color) {
        type = PieceType::Knight;
        movementStrategy = new KnightMovementStrategy();
    }
};

class Pawn: public Piece{
    public:
    Pawn(Color color):Piece(color) {
        type = PieceType::Pawn;
        movementStrategy = new PawnMovementStrategy();
    }
};


class PieceFactory{
    public:
        Piece* createPiece(PieceType type, Color color){
            switch(type){
                case PieceType::King:
                    return new King(color);
                case PieceType::Queen:
                    return new Queen(color);
                case PieceType::Rook: 
                    return new Rook(color);
                case PieceType::Bishop:
                    return new Bishop(color);
                case PieceType::Knight:
                    return new Knight(color);
                case PieceType::Pawn:
                    return new Pawn(color);
                default:
                    return nullptr;
            }
        }
};


bool Cell::make_movement(Cell *endCell) {
    if (piece == nullptr) return false;
    return piece->make_movement(this, endCell);
}

class Move{
    Cell *startCell;
    Cell *endCell;
    public:
        Move(Cell *startCell, Cell *endCell):startCell(startCell),endCell(endCell) {}

        bool make_movement(){
            if(startCell->get_piece()==nullptr) return false;
            Piece *dest = endCell->get_piece();
            if(dest != nullptr && startCell->get_piece()->get_color() == dest->get_color()) return false;
            return startCell->make_movement(endCell);
        }

        Cell *get_startCell(){
            return startCell;
        }
        Cell *get_endCell(){
            return endCell;
        }
};

//Singleton Pattern to create board

class Board{
    private:
        int rows, cols;
        vector<vector<Cell*>> cells;
        static mutex mtx;
        static Board *instance;
        PieceFactory pieceFactory;
        Board(int r,int c): rows(r), cols(c) {
            cells.resize(r, vector<Cell*>(c, nullptr));
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    cells[i][j] = new Cell(i, j);
                }
            }
            setPieceRow(0, Color::BLACK);
            setPawnRow(1, Color::BLACK);
            setPawnRow(6, Color::WHITE);
            setPieceRow(7, Color::WHITE);
        }
        void setPawnRow(int row, Color color){
            for(int i = 0; i < cols; i++){
                cells[row][i]->set_piece(pieceFactory.createPiece(PieceType::Pawn, color));
            }
        }
        void setPieceRow(int row, Color color){
            cells[row][0]->set_piece(pieceFactory.createPiece(PieceType::Rook, color));
            cells[row][1]->set_piece(pieceFactory.createPiece(PieceType::Knight, color));
            cells[row][2]->set_piece(pieceFactory.createPiece(PieceType::Bishop, color));
            cells[row][3]->set_piece(pieceFactory.createPiece(PieceType::Queen, color));
            cells[row][4]->set_piece(pieceFactory.createPiece(PieceType::King, color));
            cells[row][5]->set_piece(pieceFactory.createPiece(PieceType::Bishop, color));
            cells[row][6]->set_piece(pieceFactory.createPiece(PieceType::Knight, color));
            cells[row][7]->set_piece(pieceFactory.createPiece(PieceType::Rook, color));
        }
    public:
        static Board* getInstance(int r, int c){
            if(instance == nullptr){
                lock_guard<mutex> lock(mtx);
                if(instance == nullptr){
                    instance = new Board(r, c);
                }
            }
            return instance;
        }
        Cell *getCell(int row, int col){
            if (row < 0 || row >= rows || col < 0 || col >= cols) return nullptr;
            return cells[row][col];
        }
};

Board* Board::instance = nullptr;
mutex Board::mtx;


class GameState {
    public:
        virtual void next(GameContext *context)=0;
        virtual void next_win(GameContext *context)=0;
        virtual void next_draw(GameContext *context)=0;
        virtual bool isGameOver()=0;
};

class GameContext;

class WhiteTurnState: public GameState{
    public:
        bool isGameOver() override;
        void next(GameContext *context) override;
        void next_win(GameContext *context) override;
        void next_draw(GameContext *context) override;
};


class BlackTurnState: public GameState{
    public:
        bool isGameOver() override;
        void next(GameContext *context) override;
        void next_win(GameContext *context) override;
        void next_draw(GameContext *context) override;
};


class WhiteWinState: public GameState{
    public:
        bool isGameOver() override;
        void next(GameContext *context) override;
        void next_win(GameContext *context) override;
        void next_draw(GameContext *context) override;
};

class BlackWinState: public GameState{
    public:
        bool isGameOver() override;
        void next(GameContext *context) override;
        void next_win(GameContext *context) override;
        void next_draw(GameContext *context) override;
};

class DrawState: public GameState{
    public:
        bool isGameOver() override;
        void next(GameContext *context) override;
        void next_win(GameContext *context) override;
        void next_draw(GameContext *context) override;
};

class GameContext{
    GameState *currentGameState;
    public:
        GameContext(){
            currentGameState = new WhiteTurnState();
        }
        void setState(GameState *state){
            currentGameState = state;
        }
        void next_win(){
            currentGameState->next_win(this);
        }
        void next(){
            currentGameState->next(this);
        }
        void next_draw(){
            currentGameState->next_draw(this);
        }
        bool isGameOver(){
            return currentGameState->isGameOver();
        }
};

//next state logic
void WhiteTurnState::next(GameContext *context){
    context->setState(new BlackTurnState());
}
void BlackTurnState::next(GameContext *context){
    context->setState(new WhiteTurnState());
}

//next win logic
void WhiteTurnState::next_win(GameContext *context){
    context->setState(new WhiteWinState());
}
void BlackTurnState::next_win(GameContext *context){
    context->setState(new BlackWinState());
}

//next draw logic
void WhiteTurnState::next_draw(GameContext *context){
    context->setState(new DrawState());
}

void BlackTurnState::next_draw(GameContext *context){
    context->setState(new DrawState());
}

//is game over logic
bool WhiteTurnState::isGameOver(){
    return false;
}
bool BlackTurnState::isGameOver(){
    return false;
}
bool WhiteWinState::isGameOver(){
    return true;
}
bool BlackWinState::isGameOver(){
    return true;
}
bool DrawState::isGameOver(){
    return true;
}

void WhiteWinState::next(GameContext *context) {}
void WhiteWinState::next_win(GameContext *context) {}
void WhiteWinState::next_draw(GameContext *context) {}
void BlackWinState::next(GameContext *context) {}
void BlackWinState::next_win(GameContext *context) {}
void BlackWinState::next_draw(GameContext *context) {}
void DrawState::next(GameContext *context) {}
void DrawState::next_win(GameContext *context) {}
void DrawState::next_draw(GameContext *context) {}

class ChessGame{
    Board *board;
    Player *whitePlayer;
    Player *blackPlayer;
    Player *currentPlayer;
    vector<Move*> movesPlayed;
    GameContext *gameContext;
    public:
        ChessGame(Player *whitePlayer, Player *blackPlayer){
            board = Board::getInstance(8,8);
            this->whitePlayer = whitePlayer;
            this->blackPlayer = blackPlayer;
            currentPlayer = whitePlayer;
            gameContext = new GameContext();
        }
        void play(){
            int count=0;
            while(!gameContext->isGameOver()&&count<50){
                    int startRow,startCol,endRow,endCol;
                    cout<<"Enter the start row, start column, end row, end column for "<<(currentPlayer == whitePlayer ? "White" : "Black")<<": ";
                    cin>>startRow>>startCol>>endRow>>endCol;
                    Cell *startCell = board->getCell(startRow,startCol);
                    Cell *endCell = board->getCell(endRow,endCol);
                    if (startCell->get_piece() == nullptr) {
                        cout << "No piece on that square. Try again." << endl;
                        continue;
                    }
                    if (startCell->get_piece()->get_color() != currentPlayer->get_playerColor()) {
                        cout << "That is not your piece. Try again." << endl;
                        continue;
                    }
                    Piece *destPiece = endCell->get_piece();
                    PieceType destinationPieceType = destPiece ? destPiece->get_type() : PieceType::Pawn;
                    Move *move = new Move(startCell,endCell);
                    bool valid=move->make_movement();
                    if(valid){
                        count++;
                        cout<<"The move is valid"<<endl;
                        if(destinationPieceType == PieceType::King){
                            gameContext->next_win();
                        }
                        else{
                            gameContext->next();
                            currentPlayer = (currentPlayer == whitePlayer) ? blackPlayer : whitePlayer;
                        }
                        movesPlayed.push_back(move);
                        if(count>=50){
                            gameContext->next_draw();
                        }
                    }
                    else{
                        cout<<"The move is not valid, try again"<<endl;
                    }
            }
            if(gameContext->isGameOver()&&count<50){
                cout<<"Game Over and won by "<<(currentPlayer == whitePlayer ? "White" : "Black")<<endl;
            }
            else{
                cout<<"Game is a draw"<<endl;
            }
        }
};


int main(){
    Player *whitePlayer = new Player("White", Color::WHITE);
    Player *blackPlayer = new Player("Black", Color::BLACK);
    ChessGame *game = new ChessGame(whitePlayer, blackPlayer);
    game->play();
    delete game;
    return 0;
}