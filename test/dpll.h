#pragma once
#include <vector>
#include <set>

using namespace std;

typedef struct qt{
    int var_num;
    int clause_num;
    vector<vector<int>> clause;
    //vector<vector<int>> solve;
    vector<int> map;
//    qt(){};
//    qt(int vn,int cn):var_num(vn),clause_num(cn),map(vn+1,0){};
}Question;

typedef struct tree{
    int node_id;
    int clause_num;
    vector<vector<int>> clause;
    vector<int> solve;
    struct tree* left;
    struct tree* right;
    struct tree* parent;
    tree(int ni, int cn):node_id(ni),clause_num(cn),left(nullptr),right(nullptr),parent(nullptr){}
}SolveTree;

typedef struct {
    int solve_num;
    vector<vector<int>> solve;
    set<vector<int>> solve_set;
}Solves;

typedef struct vw{
    int var_num;
    vector<double> weight;
    vw(int vn, int w):var_num(vn),weight(vn, w){};
}VarWeight;

//Question question;
//SolveTree solveTree;
//Solves solves;
//VarWeight varWeight;

void allSolves(Question &q, Solves &s);
bool isSolve(Question &q, vector<int> s);
vector<int> findSolve(Question &q, vector<int>s);
void randSolves(Question& q, Solves& sol); 
set<vector<int>> partlyRandSolves(Question& q, Solves& sol, int sol_num);
set<vector<int>> allrandSolves(Question& q, Solves& sol, int sol_num);


//void Loop(SolveTree* p, int deep, int& var_num, vector<vector<int>>& result);
//void Loop(SolveTree *p, int deep, int &var_num, const vector<int> &solve);
//bool isMaySatisfiable(SolveTree* s);
//void SetChildTree(SolveTree* f, SolveTree* c, int value);

class dpll{
public:


private:

};

