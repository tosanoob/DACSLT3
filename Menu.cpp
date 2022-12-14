#ifndef MENU_CPP
#define MENU_CPP
#include "../DACSLT3/Header/Menu.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

void gotoxy(const int& column, const int& line){
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearLine() {
    gotoxy(0,0);
    cout<<"                                                                         ";
    gotoxy(0,0);
}

void clearScreen(const int& width = 100, const int& height = 20) {
    gotoxy(0,0);
    string space;
    for (int i =0;i<width;i++) {
        space+=' ';
    }
    for (int i =0;i<height;i++) {
        cout<<space<<'\n';
    }
    gotoxy(0,0);
}   

#define HOME gotoxy(0,0);
#define CLEARLINE clearLine();
#define DOWN int(1)
#define UP int(2)
#define RIGHT int(3)
#define LEFT int(4)
#define ENTER int(5)
#define ESCAPE int(8)

int move(){
    char c = getch();
    if ((int)c == -32)
        c = getch();
    switch ((int) c){
        case 80:
            return DOWN; //nhan phim xuong
        case 72:
            return UP; //nhan phim len
        case 77:
            return RIGHT; //nhan phim phai
        case 75:
            return LEFT; //nhan phim trai
        case 27:
            return ESCAPE; //nut esc
        case 13:
            return ENTER; //nut enter
        default:
            return 0; //Sai
    }
}

Menu::Menu(int strnum, string a[]): number(strnum){
    item = new string [strnum];
    for (int i = 0; i < strnum; i++)
        item[i] = a[i];
}

void Menu::printMenu(){
    for (int i = 0; i < number; i++){
        gotoxy(3, i);
        cout << item[i];
        //Sleep(1000);
    }
}

void Menu::deleteMenu(){
    for (int i = 0; i < number; i++){
        gotoxy(0, i);
        for (int j = 0; j < item[i].size() + 3; j++)
            cout << " ";
    }
}

int Menu:: ctrlMenu() {
    int x;
    int line = 0;
    printMenu();
    gotoxy(0, line);
    cout << (char) 1;
    int esc = 0;
    while (!esc){
        if (kbhit()){
            x = move();
            gotoxy(0, line);
            cout << " ";
            if (x == DOWN || x == RIGHT){
				line++;
                if (line >= number)
                        line = 0;
			}
            else if (x == UP || x == LEFT){
                line --;
                if (line < 0)
                    line = number - 1;
			}
            else if (x == ENTER){
                break;
            }
            else if (x == ESCAPE)
                exit(0);
            gotoxy(0, line);
            cout << (char) 1;
        }
    }
    return line;
}

string* Menu::getItem(){
    return item;
}

int Menu::numberOfItem(){
    return number;
}

Menu::~Menu(){
    delete[] item;
}

void showConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

// Menu declaration:

string mainMenuItem[4] = {"Thu vien sach", "Danh sach nguoi dung", "Muon tra sach", "Ket thuc"};
Menu mainMenu(4,mainMenuItem);
string sachMenuItem[5] = {"Tra cuu danh sach sach","Them sach", "Sua thong tin sach", "Xoa sach", "Quay lai"};
Menu sachMenu(5,sachMenuItem);
string userMenuItem[5] = {"Tra cuu danh sach nguoi dung", "Them nguoi dung", "Xem/Sua thong tin nguoi dung", "Xoa nguoi dung", "Quay lai"};
Menu userMenu(5,userMenuItem);
string borrowMenuItem[4] = { "Muon sach","Kiem tra thong tin muon sach", "Tra sach", "Quay lai"};
Menu borrowMenu(4,borrowMenuItem);
string borrowInfoMenuItem[3] = {"Thong tin sach","Thong tin nguoi dung", "Quay lai"};
Menu borrowInfoMenu(3,borrowInfoMenuItem);
#endif