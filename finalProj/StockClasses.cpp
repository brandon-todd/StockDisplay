#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "StockClasses.h"
using namespace std;
//operator overload for the << operator with a stockDisplay class
ostream& operator<<(ostream& os, const stockDisplay& sd) {
    time_t now = time(0);
    char* dt = ctime(&now);
    char date[25];
    strncpy(date, dt, 24);
    date[24] = '\0';
    os << endl;
    os << " }," << endl;
    os << " {" << endl;
    os << "    name: \"" << sd.name << "\"," << endl;
    os << "    change: \"" << sd.change << "\"," << endl;
    os << "    date: \"" << date << "\"" << endl;
    os << " }" << endl;
    os << "]" << endl;
    return os;
}
/*this function is used to read from the data.txt file created by the python script
it parses the data in there to be able to write it correctly to the javascript variable
in the javascript file*/
void stockRead::ReadFile() {
    string n;
    string ch;
    FILE* fp1;
    char c;
    float change;
    int loop_count = 0;
    fp1 = fopen("data.txt", "r");
    c = fgetc(fp1);
    stockDisplay sD;
    while (c != EOF) {
        c = fgetc(fp1);
        if (c == '"') {
            loop_count++;
            c = fgetc(fp1);
            while (c != '"') {
                if (c != '+' && c != '-' && c > 64 && c < 123 && c != '\\' || c == ' ' || c == '&') {
                    n += c;
                    c = fgetc(fp1);
                }
                else if (c == '+' || c == '-' || c == '.' || c < 48 || c > 39 && c != ',') {
                    ch += c;
                    c = fgetc(fp1);
                }
            }
            if (loop_count % 2 != 0) {
                cout << n << endl;
                sD.SetName(n);
            }
            else {
                cout << ch << endl;
                sD.SetChange(ch);
                sD.writeJson();
            }
            n = "";
            ch = "";
        }
    }
    if (fp1 != NULL) {
        ::fclose(fp1);
    }
}
/*this function is used to go to a specific line in the javascript file to write the data*/
void stockDisplay::GotoLine(int num) {
    string s;
    int lineCount = 0;
    string n = "StockData.js";
    fstream fout;
    fout.open(n, ios::in | ios::out);
    if (!fout.good()) {
        throw "The file StockData.js did not open.";
    }
    while (getline(fout, s)) {
        lineCount++;
    }
    fout.clear();
    fout.seekg(ios::beg);
    for (int i = 1; i <= (lineCount - num); i++) {
        getline(fout, s);
    }
    long pos = fout.tellp();
    fout.seekp(pos);
    //operator overloaded function
    fout << *this;
    fout.close();
}
/*
this function is used to write the Json style data to a variable in a javascript file*/
void stockDisplay::writeJson() {
    string n = "StockData.js";
    ifstream fin(n);
    time_t now = time(0);
    char* dt = ctime(&now);
    char date[25];
    strncpy(date, dt, 24);
    date[24] = '\0';
    if (fin.is_open()) {
        fin.close();
        try {
            GotoLine();
        }
        catch (char* c) {
            cout << c << endl;
        }
    }
    else {
        try {
            ofstream foutNew(n, ios::out);
            if (!foutNew.good()) {
                throw "The file StockData.js did not open.";
            }
            foutNew << "const data = " << endl;
            foutNew << "[" << endl;
            foutNew << " {" << endl;
            foutNew << "    name: \"" << this->name << "\"," << endl;
            foutNew << "    change: \"" << this->change << "\"," << endl;
            foutNew << "    date: \"" << date << "\"" << endl;
            foutNew << " }" << endl;
            foutNew << "]" << endl;
            foutNew.close();
        }
        catch (char* c) {
            cout << c << endl;
        }
    }

}