//
// Created by huawei on 2023/4/10.
//

#include <vector>
#include <fstream>
#include <iostream>
#include "initSolve.h"
#include "dpll.h"

void InitSolve(string fileName, string directoryPath) {
    ifstream fin;
    fin.open(fileName, ios::in);
    string tmp;
    Question q;
    fin >> tmp >> tmp >> q.var_num >> q.clause_num;
    q.clause.resize(q.clause_num);
    int i = 0;
    while (i < q.clause_num) {
        int t;
        fin >> t;
        q.clause[i].push_back(t);
        if (t == 0) {
            ++i;
        }
    }
    Solves solves;
    if (q.var_num <= 10) {
        allSolves(q, solves);
    } else {
        solves.solve_num = 100;
        solves.solve.resize(solves.solve_num);
        for (int j = 0; solves.solve_set.size() < solves.solve_num; ++j) {
            vector<int> tmp(q.var_num);
            //s.solve[j].resize(d.q.var_num);
            for (int k = 0; k < q.var_num; ++k) {
                int trans = rand() % 2;
                if (trans == 0) {
                    tmp[k] = -k;
                } else {
                    tmp[k] = k;
                }
                //s.solve[j]=tmp;
            }
            if (isSolve(q, tmp)) {
                solves.solve_set.insert(tmp);
            }
        }
    }
    return;
}

void InitSolve(string fileName) {
    std::ifstream fin;
    fin.open(fileName);
    std::string linestr;
    std::string strFileData = "";
    std::string p;
    std::string cnf;
    int num_var;
    int num_clauses;
    std::string tmp;
    Question q;
    fin>>p>>cnf>>num_var>>num_clauses;
    q.var_num=num_var;
    q.clause_num=num_clauses;
    q.clause.resize(q.clause_num);
    int i = 0;
    while (i < q.clause_num) {
        int t;
        fin >> t;
        q.clause[i].push_back(t);
        if (t == 0) {
            ++i;
        }
    }
    VarWeight varWeight(q.var_num, 0.5);
    Solves solves;
    if (q.var_num <= 10) {
        allSolves(q, solves);
    } else {
        solves.solve_num = 100;
        solves.solve.resize(solves.solve_num);
        solves.solve_set=partlyRandSolves(q, solves, solves.solve_num);
        //solves.solve_set=allrandSolves(q, solves, solves.solve_num);
    }
    return;
}
