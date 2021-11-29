#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sys/types.h>
#include "StockClasses.h"
//#include <unistd.h>

using namespace std;

int main() {
    int os;
    string pyE,web,chrome,folder,pyE2;
    //get operating system used code only works for windows
    std::cout << "What operating system are you using? (0 for Windows, 1 for linux or Mac)" << endl;
    cin >> os;
    while (!cin||(os!=1&&os!=0)) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        std::cout << "Error. Renter os (Windows:0     linux or mac:1) " << endl;
        cin >> os;
    }
    //get path to the python executable
    std::cout << "What is the path to your python executable?" << endl;
    cin >> pyE;
    while (!cin) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
       std::cout << "Error. Renter path to python executable." << endl;
       cin >> pyE;
    }
    if (os == 0) {
        //convert from string to WCHAR variable
        pyE += "\"\ .\\webscrapping_prax.py\0";
        pyE2 = '\"';
        pyE2 += pyE;
        char* py = new char[pyE2.length()+1];
        strcpy(py, pyE2.c_str());
        int i = 0;
        int nChars = MultiByteToWideChar(CP_ACP, 0, py, -1, NULL, 0);
        WCHAR* szCmdLine = new WCHAR[nChars+1];
        MultiByteToWideChar(CP_ACP, 0, py, -1, (LPWSTR)szCmdLine, nChars);
        szCmdLine[-1] = '\0';
        //setup process information
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        GetStartupInfo(&si);
        si.cb = sizeof(STARTUPINFO);
        si.wShowWindow = SW_SHOW;
        si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
        //example what the WCHAR variable should end up looking like
        //WCHAR szCmdLine2[] = L"\"C:\\Users\\brand\\AppData\\Local\\Programs\\Python\\Python38\\python.exe\" .\\webscrapping_prax.py";
        //create a new process to run python script
        CreateProcess(NULL, szCmdLine, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
        //wait for process to finish
        WaitForSingleObject(pi.hProcess, INFINITE);
        //close the process
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    /* psuedo code for linux os process code
    else { 
        pid_t pid;
        pid = fork();
        execv(python script and executable);
    }*/

    //create object of class Stocks
    Stocks today;
    //create object of class stockRead
    stockRead readData;
    //use Stock class in the stockRead class to call its functions
    readData.s = today;
    //read the data file, parse and set up your javascript object
    readData.ReadFile();
    //get path to web browser of choice (have used chrome most often)
    cout << "What is the path to your web browser?" << endl;
    getchar();
    //use get line because the Program Files folder has a space in it
    getline(cin,chrome,'\n');
    while (!cin) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Error. Renter path to web browser." << endl;
        getline(cin,chrome);
    }
    //get current directory from user
    cout << "What is the path to the folder containing this project?" << endl;
    cin >> folder;
    while (!cin) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Error. Renter path to the folder containing this project." << endl;
        cin >> folder;
    }
    //convert from string input to WCHAR to create process
    string chrome2;
    chrome += "\"";
    chrome += folder;
    chrome += "\\StockPage.html";
    chrome2 = '\"';
    chrome2 += chrome;
    char* cWeb = new char[chrome2.length() + 1];
    strcpy(cWeb, chrome2.c_str());
    int i = 0;
    int nChars1 = MultiByteToWideChar(CP_ACP, 0, cWeb, -1, NULL, 0);
    WCHAR* szCmdLine1 = new WCHAR[nChars1 + 1];
    MultiByteToWideChar(CP_ACP, 0, cWeb, -1, (LPWSTR)szCmdLine1, nChars1);
    szCmdLine1[-1] = '\0';
    if (os == 0) {
        //set up process information
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        GetStartupInfo(&si);
        si.cb = sizeof(STARTUPINFO);
        si.wShowWindow = SW_SHOW;
        si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
        //example for what the WCHAR variable should look like
        //WCHAR szCmdLine1[] = L"\"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe\" C:\\Users\\brand\\Documents\\cs225\\finalProj\\finalProj\\StockPage.html";
        //call web browser process
        CreateProcess(NULL, szCmdLine1, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
        WaitForSingleObject(pi.hProcess, INFINITE);
        //close the process
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    /* psuedo code for linux os system processes
    else {
        pid_t pid;
        pid = fork();
        execv(python script and executabled);
    }*/
    return 0;
}