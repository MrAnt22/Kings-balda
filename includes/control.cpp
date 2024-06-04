#include "control.h"
#include "board.h"
#include "coordinates.h"
#include "dictionary.h"

#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

class Dictionary;

bool Control::canFormWord(Board& board, const string& word, int i, int j) {
    if (dfs(board, word, i, j, 0) && (board.field[i][j] == word[0])) {
        return true;
    }
    string test = word;
    reverse(test.begin(), test.end());
    if (dfs(board, test, i, j, 0) && (board.field[i][j] == test[0])) {
        return true;
    }
    return false;
}

bool Control::dfs(Board& board, const string& word, int r, int c, int index) {
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

void Control::clearBoard(Board& board) {
    for(int i=0;i<board.size;i++){
        for(int j=0;j<board.size;j++){
            board.field[i][j] = '\0';
        }
    }
}

void Control::randomizeFirstPlayer() {
    srand(time(0));
    isFirstPlayerFirst = rand()%2;
}
 
bool Control::place(Board& board, Coordinates& obj, Dictionary& dict) {
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
    if(canFormWord(board, str, x, y) && (dict.words.find(str) != dict.words.end())) {
        dict.userWords.insert(str);
        return true;
    }
    reverse(str.begin(), str.end());
    if(canFormWord(board, str, x, y) && (dict.words.find(str) != dict.words.end())) {
        dict.userWords.insert(str);
        return true;
    }
    board.field[obj.x][obj.y] = '\0';
    return false;
}
    
Coordinates Control::evaluateInput(string inp) {
    Coordinates obj;
    if((int)inp.size()<6) {
        obj.ignore = true;
        return obj;
    }
    obj.x = inp[0] - 49;
    obj.y = inp[1] - 65;
    obj.symbol = inp[3];
    for(int i = 5; i < (int)inp.size(); i++) {
        switch(inp[i]) {
            case 'U':
                obj.move[i-5] = U;
            break;
            case 'D':
                obj.move[i-5] = D;
            break;
            case 'R':
                obj.move[i-5] = R;
            break;
            case 'L':
                obj.move[i-5] = L;
            break;
            default:
                obj.move[i-5] = N;
            break;
        }
    }
    return obj;
}

bool Control::generateMove(Board& board, Dictionary& dict) {
    cout << "avalabele";
    for (int i = 0; i < board.size; ++i) {
        for (int j = 0; j < board.size; ++j) {
            if (board.field[i][j] == '\0') {
                for (char c = 'A'; c < 'Z'; c++) {
                    board.field[i][j] = c;
                    for (auto word : dict.words) {
                        if((dict.userWords.find(word) == dict.userWords.end() && dict.pcWords.find(word) == dict.pcWords.end()) && word != dict.beginningWord) {
                            if (canFormWord(board, word, i, j)) {
                                board.field[i][j] = '\0';
                                cout << word << " ";
                                return true;
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

bool Control::generateMove(Board& board, Dictionary& dict, string& res, int& misx, int& misy, char& misch) {
    for (int i = 0; i < board.size; ++i) {
        for (int j = 0; j < board.size; ++j) {
            if (board.field[i][j] == '\0') {
                for (char c = 'A'; c < 'Z'; c++) {
                    board.field[i][j] = c;
                    for (auto word : dict.words) {
                        if((dict.userWords.find(word) == dict.userWords.end() && dict.pcWords.find(word) == dict.pcWords.end()) && word != dict.beginningWord) {
                            if (canFormWord(board, word,i ,j )) {
                                board.field[i][j] = '\0';
                                //cout << "\n" << word << "\n";
                                res = word;
                                misx = i;
                                misy = j;
                                misch = c;
                                board.field[i][j] = c;
                                dict.pcWords.insert(word);
                                return true;
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

void Control::centerWord(Board& board, string word) {
    for(int i = 0; i < board.size-0; i++) {
        board.field[board.size/2][i] = word[i-0];
    }
}