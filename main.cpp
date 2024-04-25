#include <iostream>
#include <set>

#define SIZE 5
#define GOD_WORD "GOD"

using namespace std;

void displayField();
bool writeToField(string inp);
void mainLoop(string c);
void checkField();

char field[SIZE][SIZE];
int score = 0;
bool isFirstPlayer = true;
set<string> foundWords;

int main(){
    //initializaiton
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            field[j][i] = ' ';
        }
    }

    for(int i = 0; i < SIZE-2; i++) {
        field[0][i] = GOD_WORD[i-0];
    }
    
    //main loop
    string c;
    while(c[0] != '!') {
        mainLoop(c);
    }
}

void mainLoop(string c) {
        displayField();
        cout << "Your discovered words are: [";
        for(auto word: foundWords) {
            cout << word << ", ";
        }
        cout << "]" << endl;
        cout << "<Your score: {" << foundWords.size() << "}>"<<endl;
        cout << "Enter field pos and char [3A=X]:";
        cin >> c;
        cout << "\x1B[2J\x1B[H";
       if(!writeToField(c)) {
            mainLoop(c);
       }
       checkField();
}

/*
    ┏ ━ ┓ ┃ ┳ ┻ ╋ ┣ ┫ ┗ ┛

*/

bool writeToField(string inp) {
    int x = inp[0] - 49;
    int y = inp[1] - 65;
    char val = inp[3];

    if(x < 0 || x > SIZE || y < 0 || y > SIZE) {
        return false;
    }

    if(((field[x-1][y] == ' ' || field[x-1][y] == 0) && (field[x+1][y] == ' ' || field[x+1][y] == 0)) && ((field[x][y-1] == ' ' || field[x][y-1] == 0) && (field[x][y+1] == ' ' || field[x][y+1] == 0))) {
        return false;
    }

    //cout << x << " " << y  << " " << val << endl;
    field[x][y] = val;
    return true;
}

void displayField() {
    cout << "┏━A━┳━B━┳━C━┳━D━┳━E━┓" << endl;
    for(int i = 0; i < SIZE; i++) {
        cout << (i+1) << " ";
        for(int j = 0; j < SIZE; j++) {
            cout << field[i][j] << " ┃ ";
        }
        cout << endl;
        if(i != SIZE-1) {
            cout << "┣━━━╋━━━╋━━━╋━━━╋━━━┫" << endl;
        }
    }
    cout << "┗━━━┻━━━┻━━━┻━━━┻━━━┛" << endl;
}

void checkField() {
    bool isWord = true;

    int length = 3;

    for(int t = 0; t < 3; t++) {
        isWord = true;
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0+t; j < SIZE; j++) {
                if(field[i][j] == GOD_WORD[j-t] && isWord) {
                    isWord = true;
                } else {
                    isWord = false;
                }
                if(j == SIZE-3+t && isWord) {
                    foundWords.insert(GOD_WORD);
                }
            }
        }
    }
    
}