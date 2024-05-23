#include <iostream>
#include <set>
#include <string>
#include <fstream>

#define SIZE 5
#define GOD_WORD "THOSE"

using namespace std;

class View;
class Coordinates;
struct Control;
struct Board;
class Dictionary;

struct Coordinates{
public:
    friend View;
    friend Control;
    int x;
    int y;
    char symbol;
    int move[10];
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
    set<string> words;
    set<string> userWords;
    set<string> pcWords;
    string filename = "dictionary.txt";
    void loadDictionary(){
        string word;
        ifstream dict(filename);

        while(getline(dict, word)) {
            for (auto& x : word) {
                x = toupper(x);
            }
            words.insert(word.substr(0,word.length()));
            //cout << word.substr(0,word.length());
        }
        dict.close();
    }
};

class View {
    int score(bool isUser,Dictionary& dict){
        int sumScore = 0;
        for(auto word: (isUser?dict.userWords:dict.pcWords)) {
                sumScore += word.length();
                //cout << word.length();
            }
        return sumScore;
    }
    public:
    void displayBoard(Board& board){
        cout << "┏━A━┳━B━┳━C━┳━D━┳━E━┓" << endl;
        for(int i = 0; i < board.size; i++) {
            cout << (i+1) << " ";
            for(int j = 0; j < board.size; j++) {
                cout << board.field[i][j] << " ┃ ";
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
        cout << "Your discovered words are:";
        for(auto word: dict.userWords) {
            cout << word << " " ;
        }
        cout << "]" << endl;
        cout << "CPU's discovered words are:";
        for(auto word: dict.userWords) {
            cout << word << " " ;
        }
        cout << "]" << endl;
    }
};

class Control {
    public:
    bool isPlayerTurn = false;
    void clearBoard(Board& board) {
        for(int i=0;i<board.size;i++){
            for(int j=0;j<board.size;j++){
                board.field[i][j] = ' ';
            }
        }
    }
    bool place(Board& board, Coordinates& obj,Dictionary& dict) {
        if(obj.x < 0 || obj.x > SIZE || obj.y < 0 || obj.y > SIZE) {
            return false;
        }
        if(((board.field[obj.x-1][obj.y] == ' ' || board.field[obj.x-1][obj.y] == 0) && (board.field[obj.x+1][obj.y] == ' ' || board.field[obj.x+1][obj.y] == 0)) && ((board.field[obj.x][obj.y-1] == ' ' || board.field[obj.x][obj.y-1] == 0) && (board.field[obj.x][obj.y+1] == ' ' || board.field[obj.x][obj.y+1] == 0))) {
            return false;
        }
        board.field[obj.x][obj.y] = obj.symbol;
        string str;
        int x = obj.x;
        int y = obj.y;
        for(int i = 0;i < 10;i++) {
            if(obj.move[i]) {
                str = str + board.field[x][y];
                x+=obj.move[i]/2;
                y+=obj.move[i]%2;
            } else {
                i = 10;
            }
        }
        cout << str << ";";
        for (string wrd: dict.words) {
            bool isWord = true;
            for(int sleep = 0; sleep < 2;sleep++){
                for(int i = 0; i < (int)wrd.length();i++){
                if(str[i] == wrd[sleep? (int)wrd.length()-i-1:i] && isWord){
                    isWord = true;
                }
                else {
                    isWord = false;
                }
                if(isWord && i == (int)str.length()-1){
                    dict.userWords.insert(wrd);
                }
                }
            }
            
        }
        return true;
    }
    Coordinates evaluateInput(string inp) {
        Coordinates obj;
        obj.x = inp[0] - 49;
        obj.y = inp[1] - 65;
        obj.symbol = inp[3];
        for(int i = 0;i<10;i++){
            switch (i+3<(int)inp.length()-1?inp[i+4]:' '){
                case 'L':
                    obj.move[i] = -1;
                break;
                case 'U':
                    obj.move[i] = -2;
                break;
                case 'D':
                    obj.move[i] = +2;
                break;
                case 'R':
                    obj.move[i] = +1;
                break;
                default:
                    obj.move[i] = 0;
                break;
            }
            cout << obj.move[i];
        }
        return obj;
    }
    //this is where the hardest part probably is
    void makeMove(Board& board, Dictionary& Dictionary) {
        
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
    game.centerWord(board, GOD_WORD);

    string c;
    while(true) {
        viewport.displayBoard(board);
        cout << endl;
        viewport.displayWords(dict);
        viewport.displayScores(dict);
        cout << endl;
        cout << "Enter field pos and char [3A=X]:";
        cin >> c;
        if(c[0] == '!') {
            break;
        }
        Coordinates coord = game.evaluateInput(c);
        if( game.place(board, coord, dict)) {
            game.makeMove(board, dict);
        }
        //basically this shit is like a clear frame. clearing the console without clearing the console.
        cout << "\x1B[2J\x1B[H";
    }
}

                                                                /*Hall of Fame*/
// void checkField() {
//     bool isWord = true;

//     int length;

    //horizontal
//     for(int isVertical = 0;isVertical < 2; isVertical++){
//         for(int i = 0; i < SIZE; i++) {
//             for (string wrd: allWords) {
//                 length = wrd.length();
//                 for(int t = 0; t < (6-length); t++) {
//                     isWord = true;
//                     for(int j = 0+t; j < length+t; j++) {
//                         if(field[isVertical?j:i][isVertical?i:j] == wrd[j-t] && isWord) {
//                             isWord = true;
//                         } else {
//                             isWord = false;
//                         }
//                         if(j == SIZE-(6-length)+t && isWord) {
//                             foundWords.insert(wrd);
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }
