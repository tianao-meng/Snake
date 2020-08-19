#include <iostream>
#include <ncurses.h>
#include <cstdlib>

using namespace std;
bool gameover;
const int width = 20;
const int height = 20;
int x, y, FruitX, FruitY, score;
enum eDirection {Stop = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
int TailX[100], TailY[100];
int nTail = 0;
void setup(){

    initscr();// initscr()函数将终端屏幕初始化为curses 模式
    clear();
    noecho(); //禁止字符出现在终端上
    cbreak();//可以禁止行缓冲
    curs_set(0);//这个函数用来设制光标是否可见

    gameover = false;
    x = width / 2;
    y = height / 2;

    FruitX = rand() % width;

    FruitY = rand() % height;
    score = 0;

}

void draw(){
    //mvwprintw 指定窗口，指定坐标输出

 
    clear();



    for (int i = 0; i < height + 2; i++){
        for(int j = 0; j < width + 2; j++){
            if (i == 0 || i == 21){
                mvprintw(i, j,"#");
            } else if (j == 0 || j == 21){
                mvprintw(i, j,"#");
            } else if (i == y && j == x){
                mvprintw(i, j ,"O");
            } else if (i == FruitY && j == FruitX){
                mvprintw(i, j ,"F");
            } else {
                for (int k = 0; k < nTail; k++){
                    if ((TailX[k] == j) && (TailY[k] == i)){
                        mvprintw(i, j ,"o");
                    }
                }
            }
        }
    }

    mvprintw(22, 0, "Score %d", score);

    refresh();

}

void input(){

    keypad(stdscr, TRUE);
    halfdelay(3);
    int c = getch();
    switch(c){
        case KEY_LEFT:
            dir = LEFT;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        case KEY_UP:
            dir = UP;
            break;
        case KEY_DOWN:
            dir = DOWN;
            break;
        case 113:
            gameover = true;
            break;
        default:
            break;

    }
}

void logic(){
    
    int prevX = TailX[0];
    int prevY = TailY[0];
    int prev2X, prev2Y;
    TailX[0] = x;
    TailY[0] = y;
    
    for (int i = 1; i < nTail; i++){
        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
        
    }
    switch(dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;

    }
    if (x >= width|| x <= 0 || y <= 0 || y >= height){
        gameover = true;
    }
    if(x == FruitX && y == FruitY){
        score ++;
        FruitX = (rand() % width) + 1;
        FruitY = (rand() % height) + 1;
        nTail++;

    }
    for(int i = 0; i< nTail; i++){
        if (TailX[i] == x && TailY[i] == y){
            gameover = true;
        }
    }

}

int main() {
    setup();


    while(!gameover){
        draw();
        input();
        logic();

    }

    getch();
    endwin();


    return 0;
}
