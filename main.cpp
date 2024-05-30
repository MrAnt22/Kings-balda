#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <algorithm> 
#include <iomanip>

#define SIZE 5
#define GOD_WORD "LIGHT"

using namespace std;

class View;
class Coordinates;
struct Control;
struct Board;
class Dictionary;
class Menu;

enum Move {
    L=-1, R=1, U=-2, D=2, N=0
};

struct Coordinates{
public:
    friend View;
    friend Control;
    int x;
    int y;
    bool ignore = false;
    char symbol;
    Move move[10] = {N,N,N,N,N,N,N,N,N,N};
};

struct Board{
    char field[SIZE][SIZE];
    int size = SIZE;
public:
    friend View;
    friend Control;
};

class Dictionary{
public:
    friend View;
    friend Control;
    string beginningWord;
    set<string> words;
    set<string> userWords;
    set<string> pcWords;
    string filename = "dictionary.txt";
    void loadDictionary(){
        
        srand(time(0)); 
  
        string word;
        ifstream dict(filename);

        while(getline(dict, word)) {
            for (auto& x : word) {
                x = toupper(x);
            }
            words.insert(word.substr(0,word.length()));

            if((word.size() == 5 && beginningWord == "") && (rand()%20) == 0 ) {
                beginningWord = word;
            }
        }
        dict.close();
    }
};

class View {
    int score(bool isUser,Dictionary& dict){
        int sumScore = 0;
        for(auto word: (isUser?dict.userWords:dict.pcWords)) {
                sumScore += word.length();
            }
        return sumScore;
    }
    public:
    void displayBoard(Board& board){
        cout << "┏━A━┳━B━┳━C━┳━D━┳━E━┓" << endl;
        for(int i = 0; i < board.size; i++) {
            cout << (i+1) << " ";
            for(int j = 0; j < board.size; j++) {
                cout << (board.field[i][j]=='\0' ? ' ' : board.field[i][j]) << " ┃ ";
            }
            cout << endl;
            if(i != board.size-1) {
                cout << "┣━━━╋━━━╋━━━╋━━━╋━━━┫" << endl;
            }
        }
        cout << "┗━━━┻━━━┻━━━┻━━━┻━━━┛" << endl;  
    }
    void displayScores(Dictionary& dict) {
        cout << "The user's score is: {" << score(true, dict) << "}\n" << "The CPU's score is: {" << score(false, dict) << "}\n";
    }
    void displayWords(Dictionary& dict) {
        cout << "Your discovered words are: {";
        for(auto word: dict.userWords) {
            cout << word << " " ;
        }
        cout << "}" << endl;
        cout << "CPU's discovered words are: {";
        for(auto word: dict.pcWords) {
            cout << word << " " ;
        }
        cout << "}" << endl;
    }
    void refreshScreen() {
        cout << "\x1B[2J\x1B[H";
    }
    void endgameScreen(Board& board, Dictionary& dict) {
        this->displayBoard(board);
        cout << endl;
        this->displayWords(dict);
        cout << endl;
        this->displayScores(dict);
        cout << endl;
        cout << "";
    }
};

class Control {
    private: 
    bool canFormWord(Board& board, const string& word) {
        for (int i = 0; i < board.size; ++i) {
            for (int j = 0; j < board.size; ++j) {
                if (board.field[i][j] == word[0] && dfs(board, word, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
    bool dfs(Board& board, const string& word, int r, int c, int index) {
        if (index == (int)word.size()) return true;
        
        if (r < 0 || c < 0 || r >= board.size || c >= board.size || board.field[r][c] == '\0' || board.field[r][c] != word[index]) {
            return false;
        }
        
        char temp = board.field[r][c];
        board.field[r][c] = '\0';
        
        bool found = dfs(board, word, r+1, c, index+1) ||
                     dfs(board, word, r-1, c, index+1) ||
                     dfs(board, word, r, c+1, index+1) ||
                     dfs(board, word, r, c-1, index+1);
        
        board.field[r][c] = temp;
        
        return found;
    }
    public:
    bool isPlayerTurn = false;
    void clearBoard(Board& board) {
        for(int i=0;i<board.size;i++){
            for(int j=0;j<board.size;j++){
                board.field[i][j] = '\0';
            }
        }
    }
    bool place(Board& board, Coordinates& obj,Dictionary& dict) {
        if(obj.ignore) {
            return false;
        }
        if(obj.x < 0 || obj.x > board.size || obj.y < 0 || obj.y > board.size) {
            return false;
        }
        if(((board.field[obj.x-1][obj.y] == '\0' || board.field[obj.x-1][obj.y] == 0) && (board.field[obj.x+1][obj.y] == '\0' || board.field[obj.x+1][obj.y] == 0)) && ((board.field[obj.x][obj.y-1] == '\0' || board.field[obj.x][obj.y-1] == 0) && (board.field[obj.x][obj.y+1] == '\0' || board.field[obj.x][obj.y+1] == 0))) {
            return false;
        }
        if(board.field[obj.x][obj.y] != '\0') {
            cout << board.field[obj.x][obj.y] << endl;
            return false;
        }
        board.field[obj.x][obj.y] = obj.symbol;
        string str;
        str += obj.symbol;
        int x = obj.x;
        int y = obj.y;

        for(int i = 0;i < 10;i++) {
            if((obj.move[i] < 5 && obj.move[i] > -5) && obj.move[i] != 0) {
                x+=obj.move[i]/2;
                y+=obj.move[i]%2;
                str += board.field[x][y];
            } else {
                str[i+1] = '\0';
                i = 10;
            }
        }
        if(canFormWord(board, str) && (dict.words.find(str) != dict.words.end())) {
            dict.userWords.insert(str);
            return true;
        }
        reverse(str.begin(), str.end());
        if(canFormWord(board, str) && (dict.words.find(str) != dict.words.end())) {
            dict.userWords.insert(str);
            return true;
        }
        board.field[obj.x][obj.y] = '\0';
        return false;
    }
    Coordinates evaluateInput(string inp) {
        Coordinates obj;
        if((int)inp.size()<5) {
            obj.ignore = true;
            return obj;
        }
        obj.x = inp[0] - 49;
        obj.y = inp[1] - 65;
        obj.symbol = inp[3];
        for(int i = 4; i < (int)inp.size(); i++) {
            switch(inp[i]) {
                case 'U':
                    obj.move[i-4] = U;
                break;
                case 'D':
                    obj.move[i-4] = D;
                break;
                case 'R':
                    obj.move[i-4] = R;
                break;
                case 'L':
                    obj.move[i-4] = L;
                break;
                default:
                    obj.move[i-4] = N;
                break;
            }
        }
        return obj;
    }
    bool checkMoves(Board& board, Dictionary& dict) {
        for (int i = 0; i < board.size; ++i) {
            for (int j = 0; j < board.size; ++j) {
                if (board.field[i][j] == '\0') {
                    for (char c = 'A'; c < 'Z'; c++) {
                        board.field[i][j] = c;
                        for (auto word : dict.words) {
                            if((dict.userWords.find(word) == dict.userWords.end() && dict.pcWords.find(word) == dict.pcWords.end()) && word != dict.beginningWord) {
                                if (canFormWord(board, word)) {
                                    board.field[i][j] = '\0';
                                    if(!canFormWord(board, word)) {
                                        return true;
                                    };
                                }
                            }
                        }
                        board.field[i][j] = '\0';
                    }
                }
            }
        }
        return false;
    }
    bool makeMove(Board& board, Dictionary& dict, string& res, int& misx, int& misy, char& misch) {
        for (int i = 0; i < board.size; ++i) {
            for (int j = 0; j < board.size; ++j) {
                if (board.field[i][j] == '\0') {
                    for (char c = 'A'; c < 'Z'; c++) {
                        board.field[i][j] = c;
                        for (auto word : dict.words) {
                            if((dict.userWords.find(word) == dict.userWords.end() && dict.pcWords.find(word) == dict.pcWords.end()) && word != dict.beginningWord) {
                                if (canFormWord(board, word)) {
                                    board.field[i][j] = '\0';
                                    if(!canFormWord(board, word)) {
                                        res = word;
                                        misx = i;
                                        misy = j;
                                        misch = c;
                                        board.field[i][j] = c;
                                        dict.pcWords.insert(word);
                                        return true;
                                    };
                                }
                            }
                        }
                        board.field[i][j] = '\0';
                    }
                }
            }
        }
        return false;
    }
    void centerWord(Board& board, string word) {
        for(int i = 0; i < board.size-0; i++) {
            board.field[board.size/2][i] = word[i-0];
        }
    }
};

int main() {
    Dictionary dict;
    dict.loadDictionary();
    
    View viewport;
    Control game;

    Board board;

    game.clearBoard(board);
    game.centerWord(board, dict.beginningWord);

    string c;
    string resword;
    int misx;
    int misy;
    char misch;
    int didBotSkipTurn;
    while(true) {
        viewport.displayBoard(board);
        cout << endl;
        viewport.displayWords(dict);
        cout << endl;
        viewport.displayScores(dict);
        cout << endl;

        if(!game.checkMoves(board, dict)) {
            viewport.refreshScreen();
            viewport.endgameScreen(board, dict);
            return 0;
        }
        
        if(didBotSkipTurn) {
            cout << "The bot skipped his turn." << endl << endl;
        }
        cout << "Format: 3A=XUL; U->Up; D->Down; R->Right; L->Left; Enter 'S' to skip turn" << endl;
        cout << "Your turn: ";
        cin >> c;
        if(c[0] == '!') {
            break;
        }
        Coordinates coord;
        if(c[0] == 'S') {
            coord.ignore = true;
        } else {
            coord = game.evaluateInput(c);
        }

        if(coord.ignore || game.place(board, coord, dict)) {    
            if (game.makeMove(board, dict, resword, misx, misy, misch)) {
                didBotSkipTurn = false;
            } else {
                didBotSkipTurn = true;
            }
        }
        
        viewport.refreshScreen();
    }

    return 0;
}