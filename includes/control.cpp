#include "control.h"
#include "board.h"
#include "coordinates.h"
#include "dictionary.h"

#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <filesystem>

namespace fs = filesystem;

#define SIZE 5

using namespace std;

class Dictionary;

//рахунок
int Control::score(bool isUser,Dictionary& dict){
    int sumScore = 0;
    for(auto word: (isUser?dict.userWords:dict.pcWords)) {
            sumScore += word.length();
        }
    return sumScore;
}

//перевірити чи слово можливо скласти
bool Control::canFormWord(Board& board, const string& word, int i, int j) {
    if (dfs(board, word, i, j, 0) && (board.field[i][j] == word.at(0))) {
        return true;
    }
    string test = word;
    reverse(test.begin(), test.end());
    if (dfs(board, test, i, j, 0) && (board.field[i][j] == test.at(0))) {
        return true;
    }
    return false;
}

//depth first search, власне алгоритм яким все клеїться
bool Control::dfs(Board& board, const string& word, int r, int c, int index) {
    if (index == (int)word.length()) return true;
    
    if (r < 0 || c < 0 || r >= board.size || c >= board.size || board.field[r][c] == '\0' || board.field[r][c] != word.at(index)) {
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

// очистити дошку
void Control::clearBoard(Board& board) {
    for(int i=0;i<board.size;i++){
        for(int j=0;j<board.size;j++){
            board.field[i][j] = '\0';
        }
    }
}

// рандом перший гравцеь
void Control::randomizeFirstPlayer() {
    srand(time(0));
    isFirstPlayerFirst = rand()%2;
}
 
 // Поставити за координатами букву на дошку (і перевірити чи воно формує слово)
bool Control::place(Board& board, Coordinates& obj, Dictionary& dict, bool isP2) {
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
            if(x==obj.x && y==obj.y) {
                return false;
            }
        } else {
            str[i+1] = '\0';
            i = 10;
        }
    }
    if(canFormWord(board, str, x, y) && (dict.words.find(str) != dict.words.end())) {
        if(!isP2) {
            dict.userWords.insert(str);
            board.p1Move.x = obj.x;
            board.p1Move.y = obj.y;
        } else {
            dict.pcWords.insert(str);
            board.p2Move.x = obj.x;
            board.p2Move.y = obj.y;
        }
        board.isP1[obj.x][obj.y] = !isP2+1; 
        return true;
    }
    reverse(str.begin(), str.end());
    if(canFormWord(board, str, x, y) && (dict.words.find(str) != dict.words.end())) {
        if(!isP2) {
            dict.userWords.insert(str);
            board.p1Move.x = obj.x;
            board.p1Move.y = obj.y;
        } else {
            dict.pcWords.insert(str);
            board.p2Move.x = obj.x;
            board.p2Move.y = obj.y;
        }
        board.isP1[obj.x][obj.y] = !isP2+1; 
        return true;
    }
    board.field[obj.x][obj.y] = '\0';
    return false;
}

 // Конвертувати ввід користувача у координати   
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

// Перевірити чи на дошці можна скласти слова 
bool Control::generateMove(Board& board, Dictionary& dict) {
    for (int i = 0; i < board.size; ++i) {
        for (int j = 0; j < board.size; ++j) {
            if (board.field[i][j] == '\0') {
                for (char c = 'A'; c < 'Z'; c++) {
                    board.field[i][j] = c;
                    for (auto word : dict.words) {
                        if((dict.userWords.find(word) == dict.userWords.end() && dict.pcWords.find(word) == dict.pcWords.end()) && word != dict.beginningWord) {
                            if (canFormWord(board, word, i, j)) {
                                board.field[i][j] = '\0';
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

//для тяжкої складності
struct LengthComparator {
    bool operator()(const string &a, const string &b) const {
        if (a.length() != b.length())
            return a.length() > b.length();
        return a > b;
    }
};

//Знайти слово яке можна поставити на дошку і поставити його (комп'ютер)
bool Control::generateMove(Board& board, Dictionary& dict, string& res, int& misx, int& misy, char& misch) {
    srand(time(0));
    //skip turn
    if(!isDifficult && (rand()%5)==0) {
        return false;
    }

    vector<pair<int, int>> coordinates;
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 5; ++y) {
            coordinates.emplace_back(x, y);
        }
    }

    shuffle(coordinates.begin(), coordinates.end(), default_random_engine(rand()));

    string longestWord;

    for (const auto& coord : coordinates) {
        int i = coord.first;
        int j = coord.second;
        if (board.field[i][j] == '\0') {
            for (char c = 'A'; c < 'Z'; c++) {
                board.field[i][j] = c;
                for (auto word : dict.words) {
                    if((dict.userWords.find(word) == dict.userWords.end() && dict.pcWords.find(word) == dict.pcWords.end()) && word != dict.beginningWord) {
                        if (canFormWord(board, word,i ,j )) {
                            if(!isDifficult) {
                                res = word;
                                misx = i;
                                misy = j;
                                misch = c;
                                board.field[i][j] = c;
                                board.isP1[misx][misy] = 1;
                                board.p2Move.x = misx;
                                board.p2Move.y = misy;
                                dict.pcWords.insert(word);
                                return true;
                            } else {
                                if (word.length() > longestWord.length()) {
                                    longestWord = word;
                                    res = word;
                                    misx = i;
                                    misy = j;
                                    misch = c;
                                    break;
                                }
                            }
                        }
                    }
                }
                board.field[i][j] = '\0';
            }
        }
    }

    if(!longestWord.empty() && isDifficult) {
        board.field[misx][misy] = misch;
        dict.pcWords.insert(longestWord);
        return true;
    }

    return false;
}

// слово в центр
void Control::centerWord(Board& board, string word) {
    for(int i = 0; i < board.size; i++) {
        board.field[board.size/2][i] = word.at(i);
    }
}


//зберегти гру і лідерборд
void Control::saveGame(Board& board, Dictionary& dict) {
    Gamedata gd(board, name1, name2, score(true, dict), score(false, dict), isPC);
    ofstream leader;

    string filename = "leaderboards/lb_";
    filename += name1;

    Gamedata p1g = getLeaderboards(name1);
    if(p1g.p1score > gd.p1score) {
        return;
    }
    if(!gd.isPC) {
        Gamedata p2g = getLeaderboards(name2);
        if(p2g.p1score > gd.p1score) {
            return;
        }
    }

    leader.open(filename);
    //name1
    //name2
    //0/1 (isPC)
    //p1s
    //p2s
    //ABCDE  F G H (board 25 symbols)
    leader << "p1n:"<< gd.p1name << endl;
    leader << "p2n:" << gd.p2name << endl;
    leader << "isPC:" << (int)gd.isPC << endl;
    leader << "p1s:" << gd.p1score << endl;
    leader << "p2s:" << gd.p2score << endl;
    leader << "board:";
    for(int i = 0; i < gd.board.size; i++) {
        for(int j = 0; j < gd.board.size; j++) {
            if(gd.board.field[i][j] != '\0') {
                leader << gd.board.field[i][j];
            } else {
                leader << " ";
            }
        }
    }
    leader <<endl <<  "isp1:";
    for(int i = 0; i < gd.board.size; i++) {
        for(int j = 0; j < gd.board.size; j++) {
            leader << "" << gd.board.isP1[i][j];
        }
    }
    leader.close();

    if(!gd.isPC) {    
        ofstream leader;

        string filename = "leaderboards/lb_";
        filename += name2;

        leader.open(filename);
        leader << "p1n:"<< gd.p2name << endl;
        leader << "p2n:" << gd.p1name << endl;
        leader << "isPC:" << (int)gd.isPC << endl;
        leader << "p1s:" << gd.p2score << endl;
        leader << "p2s:" << gd.p1score << endl;
        leader << "board:";
        for(int i = 0; i < gd.board.size; i++) {
            for(int j = 0; j < gd.board.size; j++) {
                if(gd.board.field[i][j] != '\0') {
                    leader << gd.board.field[i][j];
                } else {
                    leader << " ";
                }
            }
        }
        leader << endl << "isp1:";
        for(int i = 0; i < gd.board.size; i++) {
            for(int j = 0; j < gd.board.size; j++) {
                leader << "" << int((!bool(gd.board.isP1[i][j]-1))+1);
            }
        }
        leader.close();
    }
}

//отримати найкращу гру гравця
Gamedata Control::getLeaderboards(string name) {
    Gamedata gd;

    try {
        ifstream file("./leaderboards/lb_" + name);
        if (file.is_open()) {
            string str;
            while (getline(file, str)) {
                if (str.rfind("p1n:", 0) == 0) {
                    gd.p1name = str.substr(4);
                } else if (str.rfind("p2n:", 0) == 0) {
                    gd.p2name = str.substr(4);
                } else if (str.rfind("isPC:", 0) == 0) {
                    gd.isPC = stoi(str.substr(5));
                } else if (str.rfind("p1s:", 0) == 0) {
                    gd.p1score = stoi(str.substr(4));
                } else if (str.rfind("p2s:", 0) == 0) {
                    gd.p2score = stoi(str.substr(4));
                } else if (str.rfind("board:", 0) == 0) {
                    string board_str = str.substr(6);
                    for (int i = 0; i < SIZE * SIZE; ++i) {
                        if (board_str[i] == ' ') {
                            gd.board.field[i / SIZE][i % SIZE] = '\0';
                        } else {
                            gd.board.field[i / SIZE][i % SIZE] = board_str[i];
                        }
                    }
                } else if (str.rfind("isp1:", 0) == 0) {
                    string board_str = str.substr(5);
                    for (int i = 0; i < SIZE * SIZE; ++i) {
                        gd.board.isP1[i / SIZE][i % SIZE] = (int)board_str[i]-'0';
                    }
                }
            }
            file.close();
        } else {
            gd.ignore = true;
            return gd;
        }
    } catch (const exception& e) {
        gd.ignore = true;
        return gd;
    }

    return gd;
}

//отримати список найкращих ігор
vector<Gamedata> Control::getLeaderboards() {
    vector<Gamedata> lbs;
    Gamedata gd;
    string path = "./leaderboards";

    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                string filename = entry.path().filename().string();
                if (filename.rfind("lb_", 0) == 0) {
                    string fn = path + "/" + filename;

                    ifstream file(fn);
                    if (file.is_open()) {
                        string str;
                        while (getline(file, str)) {
                            if (str.rfind("p1n:", 0) == 0) {
                                gd.p1name = str.substr(4);
                            } else if (str.rfind("p2n:", 0) == 0) {
                                gd.p2name = str.substr(4);
                            } else if (str.rfind("isPC:", 0) == 0) {
                                gd.isPC = stoi(str.substr(5));
                            } else if (str.rfind("p1s:", 0) == 0) {
                                gd.p1score = stoi(str.substr(4));
                            } else if (str.rfind("p2s:", 0) == 0) {
                                gd.p2score = stoi(str.substr(4));
                            } else if (str.rfind("board:", 0) == 0) {
                                string board_str = str.substr(6);
                                for (int i = 0; i < SIZE * SIZE; ++i) {
                                    if (board_str[i] == ' ') {
                                        gd.board.field[i / SIZE][i % SIZE] = '\0';
                                    } else {
                                        gd.board.field[i / SIZE][i % SIZE] = board_str[i];
                                    }
                                }
                            } else if (str.rfind("isp1:", 0) == 0) {
                                string board_str = str.substr(5);
                                for (int i = 0; i < SIZE * SIZE; ++i) {
                                    gd.board.isP1[i / SIZE][i % SIZE] = board_str[i]-'0';
                                }
                            }
                        }
                    } else {
                        cerr << "Could not open file: " << filename << endl;
                    }
                }
            }
            lbs.push_back(gd);
            gd = Gamedata();
        }
    } catch (const fs::filesystem_error& e) {
        cerr << "Filesystem error: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "General error: " << e.what() << endl;
    }

    return lbs;
}