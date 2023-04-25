#include <iostream>
#include <ctime>
#include <string>

#include "jsonHelper.h"
#include "dpll.h"
#include "initSolve.h"
#include "check.h"
#include "walksat.h"

//#include "../genExample/lcExam.h"

using namespace std;

void start_cmd(int argc, char* argv[]) {
    cout<<argv[1]<<endl;
    cout<<argv[2]<<endl;
    string ctlstr=argv[1];
    if (argc <= 1)
        ;
    else if (ctlstr == "-h")
        ;
    else if (ctlstr == "--json-to-sat") {
        if (argc == 4) {
            jsonHelper jh;
            jh.GetOriginData(argv[2], argv[3]);
        } else if (argc == 3) {
            jsonHelper jh;
            jh.GetOriginData(argv[2]);
        }
    }
    else if(ctlstr=="--init-sat-solves") {
        if (argc == 4) {
            InitSolve(argv[2], argv[3]);
        } else if (argc == 3) {
            InitSolve(argv[2]);
        }
    }
    else if(ctlstr=="--find-all-solves") {

    }
    else if(ctlstr=="--check") {
        if (argc == 4) {
            InitCheckSolve(argv[2], argv[3]);
        }
    }
    else if(ctlstr=="--walksat") {
        if (argc == 4) {
            WalkSat(argv[2], argv[3]);
        }
    }
    return;
}


int main(int argc, char *argv[]) {
    clock_t start = clock();
    start_cmd(argc, argv);
    clock_t end = clock();
    cout << "time : " << ((double) end - start) / CLOCKS_PER_SEC << "s\n";
    return 0;
}