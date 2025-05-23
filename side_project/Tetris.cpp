﻿#include <iostream>
#include <windows.h>
#include <vector>
#include <cstdlib>  
#include <ctime>  
#include "block.h"
#include <chrono>
#include <conio.h>
#include <string>
using namespace std;
using namespace std::chrono;
//(0,2)->(int x = 34; int y = 6;)
int const leftx = 80, topy = 14;
#pragma region Function Declaration

    void frame(void);
    int turnright(vector<vector<string>>& v, vector<vector<string>>& tmp, int x, int y);
    bool down(vector<vector<string>>&v, vector<vector<string>>&tmp, int x, int y, bool& tr);
    bool right(vector<vector<string>>& v, vector<vector<string>>& tmp, int x, int y);
    bool left(vector<vector<string>>& v, vector<vector<string>>& tmp, int x, int y,int &outside);
    bool check(vector<vector<string>>&v, int x, int y);
    void print(string text, int color);
    void printnextblock(vector<vector<string>>& v, vector<vector<string>>& tmp, int saveblock);
    bool tostop(vector<vector<string>>& v, vector<vector<string>>& tmp, int x, int y);
    int  clear(vector<vector<string>>& v);
    int setcolor(vector<vector<string>>&v, vector<vector<string>>&tmp, int i, int j);
    void gotoxy(int x, int y);
    void startscreen();
    void clearstartscreen();
    void endscreen(int score);


#define  random(x) (rand()%x)+1
#pragma endregion

    
int main() { 
    auto lastTime = steady_clock::now(), lastpushW=steady_clock::now(), lastpushA = steady_clock::now();
    auto lastpushS = steady_clock::now(),lastpushD = steady_clock::now(),lastpushSP=steady_clock::now();
    bool pressA = 0, pressW = 0, pressS = 0, pressD = 0, pressSP = 0;
    srand(time(0));
    startscreen();
    int headline = 10 , saveblock = random(7);
    while (1) {
        auto now = steady_clock::now();            //間閣下落
        auto elapsed = duration_cast<milliseconds>(now - lastTime).count();
        //閃爍標題
        if (elapsed >= 100) {
            gotoxy(60 + 11, 12 + 4);   print("       TETRIS CONSOLE         ", headline);
            headline++;
            if (headline > 15)headline = 10;
            lastTime = now;
        }
        if (_kbhit()) {
            char ccc = _getch();
            if (ccc == ' ') {
                clearstartscreen();
                break;
            }
        }
    }
    bool endgane = 0;
    while (endgane == 0) {
        frame();
        
        Sleep(1000);
        vector<vector<string>>v(14, vector<string>(10, " "));
        vector<vector<string>>tmp(14, vector<string>(10, " "));
        int score = 0;
        //
        gotoxy(leftx + 18, topy + 11); print("D", 7);
        gotoxy(leftx + 16, topy + 10); print("W", 7);
        gotoxy(leftx + 16, topy + 11); print("S", 7);
        gotoxy(leftx + 14, topy + 11); print("A", 7);
        gotoxy(leftx + 14, topy + 12); print("SPACE", 112);
        while (1) {
            int x = 3, y = 0, cc = clear(v), sec = 0, outside = 0;
            bool b = 1, ctu = 1, display = 0;
            score += cc;
            gotoxy(leftx + 14, topy + 2+6); print("Score：", 14);
            gotoxy(leftx +14, topy +3 + 6); print(to_string(score), 7);
            if (cc != 0) {
                print("+", 12);
                print(to_string(cc), 12);
                display = 1;
            }
            int newblock = saveblock;
            saveblock = random(7);
            printnextblock(v, tmp, saveblock);

            switch (newblock) {
            case 1:
                ctu = I(tmp, v);
                break;
            case 2:
                ctu = L(tmp, v);
                break;
            case 3:
                ctu = J(tmp, v);
                break;
            case 4:
                ctu = O(tmp, v);
                break;
            case 5:
                ctu = T(tmp, v);
                break;
            case 6:
                ctu = S(tmp, v);
                break;
            case 7:
                ctu = Z(tmp, v);
                break;
            }
            if (ctu == 0)break;
            
            bool tr = 1;
            while (1) {
                auto now = steady_clock::now();            //間閣下落█■
                auto elapsed = duration_cast<milliseconds>(now - lastTime).count();
                for (int i = 0; i < v.size(); i++) {
                    for (int j = 0; j < v[0].size(); j++) {
                        gotoxy(leftx + j + 1, topy + i);
                        if (tmp[i][j] != " " || v[i][j] != " ")print("#", setcolor(v, tmp, i, j));
                        else cout << " ";
                    }
                }
                if (elapsed >= 1000 - sec) {
                    //
                    if (display == 0) {
                        int k = 0;
                        if (score >= 100)k = 3;
                        else if (score >= 10)k = 2;
                        else k = 1;
                        gotoxy(leftx + 14 + k, topy + 3 + 6);
                        cout << "          ";
                    }
                    else {
                        display = 0;
                    }
                    sec = 0;
                    //
                    if (b == 0) {
                        for (int i = 0; i < v.size(); i++) {
                            for (int j = 0; j < v[0].size(); j++) {
                                if (tmp[i][j] != " ") {
                                    v[i][j] = tmp[i][j];
                                    tmp[i][j] = " ";
                                }
                            }
                        }
                        break;
                    }
                    down(v, tmp, x, y, tr);

                    if (y < 9)y++;
                    lastTime = now;
                }
                if (_kbhit()) {//鍵盤輸入
                    char c = _getch();
                    if (c == 'd' || c == 'D') {
                        if (right(v, tmp, x, y) && x <= 5) {
                            x++;
                        }
                        pressD = 1;
                        lastpushD = steady_clock::now();
                        gotoxy(leftx + 14+4, topy + 11); print("D", 207);
                    }
                    else if ((c == 'a' || c == 'A')) {
                        if (left(v, tmp, x, y, outside) && x >= -1) {
                            x--;
                        }
                        pressA = 1;
                        lastpushA = steady_clock::now();
                        gotoxy(leftx + 14, topy + 11); print("A", 207);
                    }
                    else if (tr && (c == 'w' || c == 'W')) {
                        x += turnright(v, tmp, x, y);
                        gotoxy(leftx + 16, topy + 10); print("W", 207);
                        pressW = 1;
                        lastpushW = steady_clock::now();
                    }
                    else if (c == ' ') {
                        while (!tostop(v, tmp, x, y)) {
                            down(v, tmp, x, y, tr);
                            if (y < 9)y++;
                        }
                        pressSP = 1;
                        lastpushSP = steady_clock::now();
                        gotoxy(leftx + 14, topy + 12); print("SPACE", 207);
                    }
                    else if (c == 's') {
                        sec = 900;
                        pressS = 1;
                        lastpushS = steady_clock::now();
                        gotoxy(leftx + 14+2, topy + 11); print("S", 207);
                    }

                }
                    if (pressD && duration_cast<milliseconds>(now - lastpushD).count() > 300) {
                        gotoxy(leftx + 18, topy + 11); print("D", 7);
                        pressD = 0;
                    }
                    if (pressW && duration_cast<milliseconds>(now - lastpushW).count() > 300) {
                        gotoxy(leftx + 16, topy + 10); print("W", 7);
                        pressW = 0;
                    }
                    if (pressS && duration_cast<milliseconds>(now - lastpushS).count() > 300) {
                        gotoxy(leftx + 16, topy + 11); print("S", 7);
                        pressS = 0;
                    }
                    if (pressA && duration_cast<milliseconds>(now - lastpushA).count() > 300) {
                        gotoxy(leftx + 14, topy + 11); print("A", 7);
                        pressA = 0;
                    }
                    if (pressSP && duration_cast<milliseconds>(now - lastpushSP).count() > 300) {
                        gotoxy(leftx + 14, topy + 12); print("SPACE", 112);
                        pressSP = 0;
                    }

                
                b = !tostop(v, tmp, x, y);
            }
        }
        clearstartscreen();
        endscreen(score);
        int k = 10;
        while (1) {
            auto now = steady_clock::now();            //間閣下落
            auto elapsed = duration_cast<milliseconds>(now - lastTime).count();
            if (elapsed >= 100 ) {
                gotoxy(60 + 11, 12 + 6);   print("          GAME OVER           ", k);
                lastTime = now;
                k++;
                if (k > 15)k = 10;
            }
            if (_kbhit()) {
                char ccc = _getch();
                if (ccc == ' ') {
                    clearstartscreen();
                    break;
                }
                else {
                    gotoxy(30, 20);
                    return 0;
                }
            }
        }
        
    }
    return 0;
}

void printkeybroad(vector<vector<string>>& v, vector<vector<string>>& tmp, int a) {

}


void printnextblock(vector<vector<string>>& v, vector<vector<string>>& tmp, int saveblock) {
    switch (saveblock) {
    case 1:
        I(tmp, v);
        break;
    case 2:
        L(tmp, v);
        break;
    case 3:
        J(tmp, v);
        break;
    case 4:
        O(tmp, v);
        break;
    case 5:
        T(tmp, v);
        break;
    case 6:
        S(tmp, v);
        break;
    case 7:
        Z(tmp, v);
        break;
    }
    gotoxy(leftx + 10+3 , topy + 2); print("Upcoming", 11);
    for (int j = 3; j < 11; j++) {//15
        gotoxy(leftx + 10 + j, topy +3 ); print("■", 7);
        /*if (j == 3 || j == 10)print("▓", 7);
        else *print("■：", 7);*/
        gotoxy(leftx + 10 + j, topy + 2+5);
        /*if (j == 3 || j == 10)print("▓", 7);
        else */print("■", 7);
    }
    for (int j = 2; j < 5; j++) {//15
        gotoxy(leftx + 10+3 , topy + 2 + j); print("▓", 7);
        gotoxy(leftx + 10+10 , topy + 2  +j); print("▓", 7);
    }


    int a = saveblock==1?1: 0;

    for (int i = 1; i < 3 ; i++) {
        for (int j = 3; j < 7; j++) {
            gotoxy(leftx + 12 + j, topy + 3 + i);
            if (tmp[i-a][j] != " ") {
                
                print("#", setcolor(v, tmp, i-a, j));
            }
            else cout << " ";
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j < 7; j++) {
            tmp[i][j]=" ";
        }
    }
    return;
}

#pragma region Function
void endscreen( int score) {
    int x = 60 + 10;
    int y = 12 + 5;
    int w = 30;
    gotoxy(x, y);       print("╔══════════════════════════════╗", 13);
    gotoxy(x, y + 1);   print("║                              ║", 13);
    gotoxy(x+1, y + 1);   print("          GAME OVER           ", 12);
    gotoxy(x, y + 2);   print("╠══════════════════════════════╣", 13);
    for (int i = 3; i <= 10; i++) {
        gotoxy(x, y + i); print("║                              ║", 13);
    }
    string s1 = "Your Score: " + to_string(score);
    int offset1 = (w - s1.size()) / 2;
    gotoxy(x + 1 + offset1, y + 4); print(s1, 14);
    string s2 = "Thanks for playing Tetris";
    int offset2 = (w - s2.size()) / 2;
    gotoxy(x + 1 + offset2, y + 6); print(s2, 11);
    string s3 = "Press Space to restart...";
    int offset3 = (w - s3.size()) / 2;
    gotoxy(x + 1 + offset3, y + 8); print(s3, 9);
    string s4 = "Press any other key to exit...";
    int offset4 = (w - s4.size()) / 2;
    gotoxy(x + 1 + offset4, y + 9); print(s4,4);
    string s5 = "2025/5/7";
    int offset5 = (w - s5.size()) / 2;
    gotoxy(x  + offset5, y + 10); print(s5, 8);
    gotoxy(x, y + 11); print("╚══════════════════════════════╝", 13);
}


void clearstartscreen() {
    for (int row = 1; row <= 20; row++) {
        gotoxy(60 + 0, 12 + row);
        cout << string(60, ' ');
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void startscreen() {
    int x = 34+26 +10;
    int y = 12 + 3;

    gotoxy(x, y);       print("╔══════════════════════════════╗", 13);
    gotoxy(x, y + 1);   print("║       TETRIS CONSOLE         ║", 13);
    gotoxy(x, y + 2);   print("╠══════════════════════════════╣", 13);
    for (int i = 3; i <= 13; i++) {
        gotoxy(x, y + i); print("║                              ║", 13);
    }
    gotoxy(x + 3, y + 4);  print("[W] - Rotate Block", 14);
    gotoxy(x + 3, y + 5);  print("[A] - Move Left",2);
    gotoxy(x + 3, y + 6);  print("[D] - Move Right", 5);
    gotoxy(x + 3, y + 7);  print("[S] - Soft Drop", 9);
    gotoxy(x + 3, y + 8);  print("[SPACE] - Hard Drop", 12);

    gotoxy(x + 3, y + 10); print("Press [SPACE] to Start Game", 11);

    gotoxy(x + 11, y + 12); print("2025/5/7", 8);

    gotoxy(x, y + 13);     print("╚══════════════════════════════╝", 13);
}
int clear(vector<vector<string>>& v) {
    vector<vector<string>>tmp(14, vector<string>(10, " "));
    int a = v.size() - 1;
    int score = 0;
    for (int i = v.size() - 1; i >= 0; i--) {
        bool b = 0;
        for (int j = 0; j < v[0].size(); j++) {
            if (v[i][j] == " ") {
                b = 1;
                break;
            }
        }
        if (b) {
            v[a] = v[i];
            a--;
        }
        else {
            score++;
        }
    }
    for (int i = a; i >= 0; i--) {
        v[i] = vector<string>(10, " ");
    }
    return score;
}
bool tostop(vector<vector<string>>& v, vector<vector<string>>& tmp, int x, int y) {
    bool b = 0;
    if (x < 0) {
        x = 0;
    }
    if (x >= 6) {
        x = 6;
    }
    for (int i = y + 4; i >= y; i--) {
        if (i >= tmp.size())continue;
        for (int j = x; j < x + 4; j++) {
            if (tmp[i][j] != " ") {
                if (i + 1 >= v.size() || (v[i + 1][j] != " ")) {
                    b = 1;
                    break;
                }
            }
        }
        if (b) break;
    }
    return b;
}
bool right(vector<vector<string>>& v, vector<vector<string>>& tmp, int x, int y) {
    if (x < 0) {
        x = 0;
    }
    if (x >= 6) {
        x = 6;
    }
    if (y + 5 > v.size())y = v.size() - 5;
    for (int i = y; i < y + 5; i++) {
        for (int j = x + 3; j >= x; j--) {
            if (j + 1 >= tmp[0].size() && tmp[i][j] != " ") return 0;
            if (tmp[i][j] != " ") {
                if (j + 1 >= tmp[0].size())return 0;
                if (tmp[i][j] != " " && v[i][j + 1] != " ") return 0;
            }
        }
    }
    for (int i = y; i < y + 5; i++) {
        for (int j = x + 3; j >= x; j--) {
            if (j + 1 < tmp[0].size()) {
                tmp[i][j + 1] = tmp[i][j];
            }
        }
    }
    for (int i = y; i < y + 5; i++) {
        tmp[i][x] = " ";
    }
    return 1;
}
bool left(vector<vector<string>>& v, vector<vector<string>>& tmp, int x, int y,int& outside) {
    if (x < 0) {
        x = 0;
        outside = x;
    }
    /*if (x >= tmp[0].size()) {
        x--;
    }*/
        if (x >= 6) {
            x = 6;
        }
    if (y + 5 > v.size())y = v.size() - 5;
    for (int i = y; i < y + 5; i++) {
        
        for (int j = x; j < x + 4; j++) {
            if (tmp[i][j] != " ") {
                if (j <= 0)return 0;
                if (tmp[i][j] != " " && v[i][j - 1] != " ") return 0;
            }
        }
    }
    for (int i = y; i < y +5; i++) {
       
        for (int j = x; j < x + 4; j++) {
            if (j > 0) {
                tmp[i][j - 1] = tmp[i][j];
            }
        }
    }
    for (int i = y; i < y + 5; i++) {
        if (i >= v.size())break;
        tmp[i][x + 3] = " ";
    }
    if (outside != 0)outside--;
    return 1;
}
bool down(vector<vector<string>>& v, vector<vector<string>>& tmp, int x, int y,bool & tr) {
    if (x < 0) {
        x = 0;
    }
    if (x >= 6) {
        x=6;
    }
    bool b = 1;
    for (int i = y + 4; i >= y; i--) {
        if (i >= tmp.size())continue;
        for (int j = x; j < x + 4; j++) {
            if (tmp[i][j] != " ") {
                if (i + 1 >= v.size() || (v[i + 1][j] != " ")) {
                    b = 0;
                    break;
                }
                else if (i + 1 == v.size() - 1|| v[i + 2][j] != " ")tr = 0;
            }
        }
        if (!b) break;
    }
    if (b) {
        for (int i = y + 4; i > y; i--) {
            for (int j = x; j < x + 4; j++) {
                tmp[i][j] = tmp[i - 1][j];
            }
        }
        for (int j = x; j < x + 4; j++) {
            tmp[y][j] = " ";
        }
    }
    return b;
}
int setcolor(vector<vector<string>>& v, vector<vector<string>>& tmp, int i, int j) {
    string s = "";
    if (tmp[i][j] != " ") {
        if (tmp[i][j] == "I") return(11);
        else if (tmp[i][j] == "L") return(6);
        else if (tmp[i][j] == "J") return(9);
        else if (tmp[i][j] == "O") return(14);
        else if (tmp[i][j] == "T") return(13);
        else if (tmp[i][j] == "S") return(10);
        else if (tmp[i][j] == "Z") return(12);
        
    }
    else if (v[i][j] != " ") {
        if (v[i][j] == "I") return(11);
        else if (v[i][j] == "L") return(6);
        else if (v[i][j] == "J") return(9);
        else if (v[i][j] == "O") return(14);
        else if (v[i][j] == "T") return(13);
        else if (v[i][j] == "S") return(10);
        else if (v[i][j] == "Z") return(12);
    }
    return -1;
}
void frame(void) {
    for (int i = 0; i < 12; i++) {
        gotoxy(leftx, i+ topy+2);
        cout << "▓";
        gotoxy(leftx+11, i+ topy + 2);
        cout << "▓";
        gotoxy(i+ leftx, 12+ topy + 2);
        if(i==0||i==11)cout << "▓";
        else cout << "■";
    }
    
}
bool check(vector<vector<string>>& v, int x, int y) {
    int c = 0;
    for (int i = y; i < y + 4; i++) {
        for (int j = x; j < x+4; j++) {
            if (v[i][j] != " ")c++;
        }
    }
    return c == 4;
}
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void print(string text, int color) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color);
    cout << text;
    SetConsoleTextAttribute(h, 7);
}
int turnright(vector<vector<string>>& v, vector<vector<string>>& tmp, int x, int y) {

    int a = 0,ox=0;
    /*if (x < 0) {
        a = x;
        x = 0;
    }*/
    if (x >= 6) {
        x = 6;
    }
    if (y + 4 > v.size())y = v.size() - 4;
    for (int i = y; i < y + 4; i++) {
        for (int j = x; j < x + 4; j++) {
            if (j < 0)continue;
            if (tmp[i][j] == "O")return 0;
        }
    }
    vector<vector<string>> tmp1=tmp;
    vector<vector<string>> tmp2(14, vector<string>(10, " "));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (x + j < 0)continue;
            if (tmp[y + i][x + j] != " ") {
                int ny = y + j, nx = x + a + 3 - i;
                while (nx < 0) {
                    if (!right(v, tmp1, x, y))return 0;
                    ox++;
                    nx++;
                    x++;
                    if (nx >= 0) {
                        j--; continue;
                    }
                    
                }
                if ((ny < 0 || nx < 0 || ny >= tmp2.size() || nx >= tmp2[0].size()))return 0;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (x + j < 0)continue;
            if(tmp1[y + i][x + j]!=" ")
            tmp2[y + j][x + 3 - i] = tmp1[y + i][x + j];
        }
    }
    for (int i = y; i < y + 4; i++) {
        for (int j = x; j < x + 4; j++) {
            if ( j < 0)continue;
            if (tmp2[i][j] != " " && v[i][j] != " ") {
                return 0;
            }
        }
    }

    tmp = tmp2;
    /*for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            tmp[y + i][x + j] = tmp2[y + i][x + j];
        }

    }*/

    return ox ;
}

#pragma endregion