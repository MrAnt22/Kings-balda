#include <iostream>
#include <set>
#include <string>
#include <fstream>

#define SIZE 5
#define GOD_WORD "LIGHT"

using namespace std;

class Coordinates{
public:
    int x;
    int y;
    char symbol;
    int move[10];
};

class Board{
    char field[SIZE][SIZE];
    int size = SIZE;
public:
    void display(){
        cout << "┏━A━┳━B━┳━C━┳━D━┳━E━┓" << endl;
        for(int i = 0; i < size; i++) {
            cout << (i+1) << " ";
            for(int j = 0; j < size; j++) {
                cout << field[i][j] << " ┃ ";
            }
            cout << endl;
            if(i != size-1) {
                cout << "┣━━━╋━━━╋━━━╋━━━╋━━━┫" << endl;
            }
        }
        cout << "┗━━━┻━━━┻━━━┻━━━┻━━━┛" << endl;  
    }
    bool place(Coordinates obj){
        if(obj.x < 0 || obj.x > SIZE || obj.y < 0 || obj.y > SIZE) {
            return false;
        }
        if(((field[obj.x-1][obj.y] == ' ' || field[obj.x-1][obj.y] == 0) && (field[obj.x+1][obj.y] == ' ' || field[obj.x+1][obj.y] == 0)) && ((field[obj.x][obj.y-1] == ' ' || field[obj.x][obj.y-1] == 0) && (field[obj.x][obj.y+1] == ' ' || field[obj.x][obj.y+1] == 0))) {
            return false;
        }
        field[obj.x][obj.y] = obj.symbol;
        return true;
    }
    void clearBoard(){
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                field[i][j] = ' ';
            }
        }
    }
    void centerWord(string word){
        for(int i = 0; i < size-0; i++) {
        field[size/2][i] = word[i-0];
        }
    }
};

class Dictionary{
public:
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
            words.insert(word);
        }
        dict.close();
    }
    void introduceWord(string word){
        words.insert(word);
        ofstream MyFile(filename,ios::out | ios::app);
        MyFile << word;
        MyFile.close();
    }
};

class Game{
public:
    bool isPlayerTurn;
    void makeMove(){
        //
    }
    Coordinates evaluateInput(string inp){
        Coordinates obj;
        obj.x = inp[0] - 49;
        obj.y = inp[1] - 65;
        obj.symbol = inp[3];
        return obj;
    }
    int score(bool isUser,Dictionary dict){
        int sumScore = 0;
        for(auto word: (isUser?dict.userWords:dict.pcWords)) {                                                                                                                              //cout << word << ", ";
                sumScore += word.length();
            }
        return sumScore;
    }
};

int main() {
    Dictionary dict;
    dict.loadDictionary();
    
    Board board;
    board.clearBoard();
    board.centerWord(GOD_WORD);

    Game game;
    

    string c;
    dict.introduceWord("skibidi toilet");
    while(c[0] != '!') {
        board.display();
        cout << "Your discovered words are: [";
        for(auto word: dict.userWords) {
            cout << word << " " ;
        }
        cout << "]" << endl;
        cout << "<Your score: {" << game.score(true, dict) << "}>"<<endl;
        cout << "Enter field pos and char [3A=X]:";
        cin >> c;
        cout << "\x1B[2J\x1B[H";
    }
}
// int yoScore(){
//     int sumScore = 0;
//     for(auto word: foundWords) {
//             //cout << word << ", ";
//             sumScore += word.length();
//         }
//     return sumScore;
// }

//void mainLoop(string c, Board board, Dictionary dict, Game game){
    //     board.display();
    //     cout << "Your discovered words are: [";
    //     for(auto word: dict.userWords) {
    //         cout << word << " " ;
    //     }
    //     cout << "]" << endl;
    //     cout << "<Your score: {" << yoScore() << "}>"<<endl;
    //     cout << "Enter field pos and char [3A=X]:";
    //     cin >> c;
    //     cout << "\x1B[2J\x1B[H";
    //    if(!writeToField(c)) {
    //         mainLoop(c);
    //    }
    //    checkField();
//}


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
