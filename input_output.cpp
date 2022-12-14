#ifndef INPUT_OUTPUT_CPP
#define INPUT_OUTPUT_CPP

#include "../DACSLT3/Header/user.h"
#include "../DACSLT3/Header/sach.h"
#include "../DACSLT3/Header/friendfunction.h"
#include <iomanip>
#include <fstream>
#include <iostream>

string increment(string & input) {
    int len = input.length()-1;
    for (int i = len; i>=0;i--) {
        if (input[i]=='9') {
            input[i]='0';
            continue;
        }
        input[i]+=1;
        break;
    }
    return input;
}

bool checkCmd(string & inp) {
    int len = inp.length()-1;
    for (int i=0;i<=len;i++) {
        if (inp[i]<'0' || inp[i]>'9') return 0;
    }
    return 1;
}

//-------------Operator << >> for User------------


istream &operator>>(istream &inp, User &a)
{
    cout << "Nhap ten nguoi dung: ";
    inp.sync();
    getline(inp, a.ten, '\n');
    cout << "Nhap so CMND: ";
    bool flag;
    do 
    {
        inp >> a.cmd;    
        flag = checkCmd(a.cmd);
        if (!flag) {
            cout<<"So CMND gom 9 ki tu so, vui long nhap lai: "; 
        }
    } while (!flag);
    return inp;
}

ostream &operator<<(ostream &out, const User &a)
{
    out << a.uid << setw(40) << a.ten << setw(16) << a.cmd;
    return out;
}

ifstream &operator>>(ifstream &inp, User &a)
{
    getline(inp, a.uid, '|');
    getline(inp, a.ten, '|');
    getline(inp, a.cmd, '\n');
    return inp;
}

ofstream &operator<<(ofstream &out, User &user)
{
    out << user.uid << '|' << user.ten << '|' << user.cmd << '\n';
}


//------------Operator << >> for Sach------------

istream &operator>>(istream &inp, Sach &a)
{
    cout << "Nhap ten sach: ";
    inp.sync();
    getline(inp, a.tenSach, '\n');
    cout << "Nhap ten tac gia: ";
    getline(inp, a.tenTacGia, '\n');
    cout << "Nhap so ban: ";
    inp >> a.soBan;
    return inp;
}

ostream &operator<<(ostream &out, const Sach &a)
{
    out << a.ma << setw(40) << a.tenSach << setw(40) << a.tenTacGia << setw(6) << a.soBan;
    return out;
}

ofstream &operator<<(ofstream &out, Sach &a)
{
    out << a.ma << '|' << a.tenSach << '|' << a.tenTacGia << '|' << a.soBan << '\n';
    return out;
}

ifstream &operator>>(ifstream &inp, Sach &a)
{
    getline(inp, a.ma, '|');
    getline(inp, a.tenSach, '|');
    getline(inp, a.tenTacGia, '|');
    string cp;
    getline(inp, cp, '\n');
    try {a.soBan = stoi(cp);}
    catch (invalid_argument) {
        throw;
    }
    return inp;
}

#endif