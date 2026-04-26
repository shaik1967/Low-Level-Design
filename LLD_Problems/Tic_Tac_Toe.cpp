#include <iostream>
#include <vector>
#include <string>
#include <exception>
using namespace std;
enum Symbol{
    X,
    O,
    EMPTY
};

class Position{
    public:
        int row,col;
        Position(int row, int col){
            this->row = row;
            this->col = col;
        }
};
class GameContext;
class Board{
    int rows,cols;
    vector<vector<Symbol>> board;
    public:
        Board(int r, int c){
            this->rows = r;
            this->cols = c;
            board.resize(r,vector<Symbol>(c,Symbol::EMPTY));
        }
        void makeMove(int r, int c,Symbol symbol){
            board[r][c] =symbol;
        }
        bool isValidMove(int r, int c){
            if(r<0 || r>=rows || c<0 || c>=cols){
                return false;
            }
            if(board[r][c] != Symbol::EMPTY){
                return false;
            }
            return true;
        }
        void checkCurrentGameState(GameContext* context);
};

class PlayerStrategy{
    public:
        virtual Position *makeMove(Board* board)=0;
};


class HumanPlayerStrategy: public PlayerStrategy{
    public:
        Position *makeMove(Board *board) override{
            while(true){
                try{
                    cout<<"Enter the row and column for your move: ";
                    int r,c;cin>>r>>c;
                    if(board->isValidMove(r,c)){
                        return new Position(r,c);
                    }
                    cout<<"Invalid move, try again"<<endl;
                }
                catch(exception& e){
                    cout<<"Invalid input, try again"<<endl;
                }
            }
            return nullptr;
        }
};

// class AiPlayerStrategy: public PlayerStrategy{
//         public:
//         Position *makeMove(Board *board) override{
//             while(true){
//                 Posistion *move =getBestMove(board);
//                 if(move != nullptr){
//                     return move;
//                 }
//                 cout<<"No best move found, try again"<<endl;
//             }
//             return nullptr;
//         }
//         Position *getBestMove(Board *board){
//             return nullptr;
//         }
// };



class Player{
    Symbol symbol;
    string name;
    PlayerStrategy *strategy;
    public:
        Player(Symbol symbol,string name,PlayerStrategy *strategy){
            this->symbol = symbol;
            this->name = name;
            this->strategy = strategy;
        }
        void makeMoveMethod(Board* board){
            Position* move= strategy->makeMove(board);
            board->makeMove(move->row,move->col,symbol);
            delete move;
        }
};

class GameContext;

class GameState{
    public:
        Symbol symbol;
        virtual void next(GameContext* context)=0;
        virtual void next_win(GameContext* context)=0;
        virtual bool isGameOver()=0;
};

class XTurnState: public GameState{
    public:
        XTurnState(){
            symbol = Symbol::X;
        }
        void next(GameContext* context) override;
        void next_win(GameContext* context) override;
        bool isGameOver() override{
            return false;
        }
};

class OTurnState: public GameState{
    public:
        OTurnState(){
            symbol = Symbol::O;
        }
        void next(GameContext* context) override;
        void next_win(GameContext* context) override;
        bool isGameOver() override{
            return false;
        }
};

class XWinState: public GameState{
    Symbol symbol;
    public:
        XWinState(){
            symbol = Symbol::X;
        }
        bool isGameOver() override{
            return true;
        }
        void next(GameContext* context) override;
        void next_win(GameContext* context) override;
};

class OWinState: public GameState{
    public:
        OWinState(){
            symbol = Symbol::O;
        }
        void next(GameContext* context) override;
        void next_win(GameContext* context) override;
        bool isGameOver() override{
            return true;
        }
};

class DrawState: public GameState{
    public:
        DrawState(){
            symbol = Symbol::EMPTY;
        }
        void next(GameContext* context) override;
        void next_win(GameContext* context) override;
        bool isGameOver() override{
            return true;
        }
};

class GameContext{
    GameState* currentGameState;
    public:
        GameContext(){
            currentGameState = new XTurnState();
        }
        void next_win(){
            currentGameState->next_win(this);
        }
        void next(){
            currentGameState->next(this);
        }
        void setState(GameState* state){
            currentGameState = state;
        }
        bool isGameOver(){
            return currentGameState->isGameOver();
        }
};

void XTurnState::next(GameContext* context) {
    context->setState(new OTurnState());
}
void OTurnState::next(GameContext* context) {
    context->setState(new XTurnState());
}

void XTurnState::next_win(GameContext* context) {
    context->setState(new XWinState());
}
void OTurnState::next_win(GameContext* context) {
    context->setState(new OWinState());
}

void XWinState::next(GameContext* context) {
    (void)context;
}
void XWinState::next_win(GameContext* context) {
    (void)context;
}
void OWinState::next(GameContext* context) {
    (void)context;
}
void OWinState::next_win(GameContext* context) {
    (void)context;
}
void DrawState::next(GameContext* context) {
    (void)context;
}
void DrawState::next_win(GameContext* context) {
    (void)context;
}

void Board::checkCurrentGameState(GameContext* context){
        //CHECK FOR WINNING CONDITIONS
        for(int i=0;i<rows;i++){
            if(board[i][0] == board[i][1] && board[i][1] == board[i][2]&&board[i][0] != Symbol::EMPTY){
                context->next_win();
                return;
            }
        }
        for(int i=0;i<cols;i++){
            if(board[0][i] == board[1][i] && board[1][i] == board[2][i]&&board[0][i] != Symbol::EMPTY){
                context->next_win();
                return;
            }
        }
        if(board[0][0] == board[1][1] && board[1][1] == board[2][2]&&board[0][0] != Symbol::EMPTY){
                context->next_win();
                return ;
        }
        if(board[0][2] == board[1][1] && board[1][1] == board[2][0]&&board[0][2] != Symbol::EMPTY){
            context->next_win();
            return ;
        }
        int cnt=0;
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(board[i][j] == Symbol::EMPTY){
                    cnt++;
                }
            }
        }
        if(cnt == 0){
            context->setState(new DrawState());
            return;
        }
        context->next();
};

class TicTacToeGame{
    Board *board;
    Player* playerx;
    Player* playero;
    Player* currentPlayer;
    GameContext *context;
    public:
        TicTacToeGame(int rows, int cols,PlayerStrategy* strategyx,PlayerStrategy* strategyo){
            board = new Board(rows,cols);
            playerx = new Player(Symbol::X,"Player X",strategyx);
            playero = new Player(Symbol::O,"Player O",strategyo);
            currentPlayer = playerx;
            context = new GameContext();
        }
        void play(){
            while(true){
                currentPlayer->makeMoveMethod(board);
                board->checkCurrentGameState(context);
                if(context->isGameOver()){
                    cout<<"Game Over and won by "<<(currentPlayer == playerx ? "Player X" : "Player O")<<endl;
                    break;
                }
                currentPlayer = currentPlayer == playerx ? playero : playerx;
            }
        }
        ~TicTacToeGame(){
            delete board;
            delete playerx;
            delete playero;
            delete context;
        }
};

int main(){
    TicTacToeGame *game= new TicTacToeGame(3,3,new HumanPlayerStrategy(),new HumanPlayerStrategy());
    game->play();
    delete game;
    return 0;
}