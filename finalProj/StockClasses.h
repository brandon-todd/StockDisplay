#include <iostream>
#include <string.h>
using namespace std;
class Stocks {
protected:
    string name;
    string change;
public:
    Stocks() { name = " "; change = " "; }
    Stocks(string n, string c) { name = n; change = c; }
    ~Stocks() {}
    void SetName(string n) {
        name = n;
    }
    void SetChange(string c) {
        change = c;
    }
};
class stockDisplay : public Stocks {
public:
    stockDisplay() { name = ""; change = ""; }
    void writeJson();
    void GotoLine(int num = 2);
    friend ostream& operator<<(ostream& os, const stockDisplay& sd);
};
class stockRead {
public:
    Stocks s;
    void ReadFile();
};