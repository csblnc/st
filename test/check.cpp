//
// Created by huawei on 2023/4/17.
//

#include <fstream>
#include <iostream>
#include "check.h"
#include "dpll.h"

using namespace std;

bool checkSolve(Question& q, vector<int>& s);

void InitCheckSolve(std::string Fcnf, std::string Fsolve){
    ifstream fcnf;
    fcnf.open(Fcnf, ios::in);
    string tmp;
    Question q;
    fcnf >> tmp >> tmp >> q.var_num >> q.clause_num;
    q.clause.resize(q.clause_num);
    int i = 0;
    while (i < q.clause_num) {
        int t;
        fcnf >> t;
        q.clause[i].push_back(t);
        if (t == 0) {
            ++i;
        }
    }

    ifstream fsolve;
    fsolve.open(Fsolve, ios::in);
    Solves solves;
    solves.solve_num=1;
    solves.solve.resize(solves.solve_num);
    i = 0;
    int ts;
    fsolve>>ts;
    while (ts!=0) {
        solves.solve[0].push_back(ts);
        ++i;
        fsolve>>ts;
    }
    if(checkSolve(q,solves.solve[0])){
        cout<<"solve is right! "<<endl;
    }else{
        cout<<"solve is wrong! "<<endl;
    }
}

bool checkSolve(Question& q, vector<int>& s){
    for(int i=0;i<q.clause_num;++i){
        for(int j=0;j<q.clause[i].size();++j){
            if(q.clause[i][j]>0){
                if(q.clause[i][j]==s[q.clause[i][j]-1]) break;
            }else if(q.clause[i][j]<0){
                if(q.clause[i][j]==s[-q.clause[i][j]-1]) break;
            } else{
                return false;
            }
        }
    }
    return true;
}