//
// Created by huawei on 2023/4/18.
//

#include <fstream>
#include <iostream>
#include "walksat.h"
#include "dpll.h"

using namespace std;

void InitWalkSat(std::string &Fcnf, string &Fvw, std::string &Fsolve,
                 Question &q, Solves &solves, walksat &w){
    ifstream fcnf;
    fcnf.open(Fcnf, ios::in);
    string tmp;
    //Question q;
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
    //Solves solves;
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

    //walksat w;
    w.clause_num=q.clause_num;
    w.var_num=q.var_num;
    w.clause_sat_times.resize(q.clause_num,0);
    w.var_covered_list.resize(2*w.var_num+1);
    for(int j=0;j<w.var_covered_list.size();++j){
        vector<int> tmp(0);
        w.var_covered_list[j]=tmp;
    }
}

void InitWalkSat(std::string &Fcnf, string &Fvw,
                 Question &q, Solves &solves, walksat &w){
    ifstream fcnf;
    fcnf.open(Fcnf, ios::in);
    string tmp;
    //Question q;
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

    //walksat w;
    w.clause_num=q.clause_num;
    w.var_num=q.var_num;
    w.clause_sat_times.resize(q.clause_num,0);
    w.var_covered_list.resize(2*w.var_num+1);
    for(int j=0;j<w.var_covered_list.size();++j){
        vector<int> tmp(0);
        w.var_covered_list[j]=tmp;
    }
}

void FillWithClauseSatTime(walksat &w, Question &q, vector<int>& s){
    for(int i=0;i<q.clause_num;++i){
        for (int j = 0; j < q.clause[i].size(); ++j) {
            if(q.clause[i][j]>0){
                if(q.clause[i][j]==s[q.clause[i][j]-1]) {
                    ++w.clause_sat_times[i];
                }
            }else if(q.clause[i][j]<0){
                if(q.clause[i][j]==s[-q.clause[i][j]-1]) {
                    ++w.clause_sat_times[i];
                }
            } else{
                break;
            }
        }
    }
}

void FillWithVarCoveredList(walksat &w, Question &q){
    for(int i=0;i<q.clause_num;++i){
        for (int j = 0; j < q.clause[i].size(); ++j) {
            if(q.clause[i][j]!=0){
                w.var_covered_list[q.clause[i][j]+w.var_num].push_back(i);
            }
        }
    }
}

void LocalSearch(walksat &w, Question &q, vector<int>& s, int max_count){
    int FX=0;
    vector<int> unsat_clause;
    for(int i=0;i<w.clause_num;++i){
        if(w.clause_sat_times[i]==0){
            ++FX;
            unsat_clause.push_back(i);
        }
    }
    int index=0;
    while(FX!=0&&index<max_count){
        ++index;
        int rand_unsat_clause=rand()%unsat_clause.size();
        int rand_clause=unsat_clause[rand_unsat_clause];
        int delta_max=0;
        int ind_max=0;
        int delta_now=0;
        vector<int> clause_sat_times_now=w.clause_sat_times;
        vector<int> clause_sat_times_best;
        for(int i=0;i<q.clause[rand_clause].size();++i){
            int var_open=q.clause[rand_clause][i]+w.var_num;
            int var_close = w.var_num-q.clause[rand_clause][i];
            int delta_open=0,delta_close=0;
            for(int j=0;j<w.var_covered_list[var_open].size();++j){
                if(clause_sat_times_now[w.var_covered_list[var_open][j]]==0)
                    ++delta_open;
                ++clause_sat_times_now[w.var_covered_list[var_open][j]];
            }
            for(int j=0;j<w.var_covered_list[var_close].size();++j){
                if(clause_sat_times_now[w.var_covered_list[var_close][j]]==1)
                    ++delta_close;
                --clause_sat_times_now[w.var_covered_list[var_close][j]];
            }
            delta_now=delta_open-delta_close;
            if(delta_max<delta_now) {delta_max=delta_now;ind_max=var_open;clause_sat_times_best=clause_sat_times_now;}
            clause_sat_times_now=w.clause_sat_times;
        }
        FX=FX-delta_max;
        if(FX<0){
            cerr<<"fatal error!"<<endl;
        }
        unsat_clause.clear();
        for(int i=0;i<w.clause_num;++i){
            if(w.clause_sat_times[i]==0){
                unsat_clause.push_back(i);
            }
        }
        int var_index=ind_max<w.var_num?w.var_num-ind_max:ind_max-w.var_num;
        s[var_index-1]=-s[var_index-1];
        w.clause_sat_times=clause_sat_times_best;
    }
    return;
}

void WalkSat(std::string Fcnf, std::string Fsolve){
    Question q;
    Solves s;
    walksat w;
    InitWalkSat(Fcnf, Fsolve,q,s,w);
    FillWithClauseSatTime(w,q,s.solve[0]);
    FillWithVarCoveredList(w,q);
    LocalSearch(w,q,s.solve[0],10);
    return;
}

