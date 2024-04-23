#include <iostream>

#define SIZE 5

using namespace std;

void displayField();
void writeToField(char inp[64]);

char field[SIZE][SIZE];

int main(){
    //initializaiton
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            field[i][j] = i*j+48;
        }
    }
    
    //main loop
    //cout << "dumb mafuacka" << endl ;
    char c[64];
    while(c[0] != '!') {
        displayField();
        cout << "Enter field pos and char: [3a=X]";
        cin >> c;
        cout << "\x1B[2J\x1B[H";
        writeToField(c);
    }
}

/*
    ┏ ━ ┓ ┃ ┳ ┻ ╋ ┣ ┫ ┗ ┛

*/

void writeToField(char inp[64]) {
    int x = inp[0] - 49;
    int y = inp[1] - 65;
    char val = inp[3];
    //cout << x << " " << y  << " " << val << endl;
    field[x][y] = val;
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