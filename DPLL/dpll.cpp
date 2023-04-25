#include "../../DPLL/file_operator.h"
#include "dpll.h"
#include <iostream>

clock_t start = clock();
long long int solve_num = 0;
int min_dp;
bool is_solve;

void SetChildTree(SolveTree *pSt, SolveTree *pSt1, int i);

bool isMaySatisfiable(SolveTree *pSt);

void Loop(SolveTree *s, int deep, int &var_num, vector<int> &solve) {
    if (deep > var_num) {
        return;
    }
    if (isMaySatisfiable(s)) {
        SolveTree sl = SolveTree(s->node_id + 1, s->clause_num);
        SolveTree *p = nullptr;
        if (solve[deep] > 0) {
            SolveTree *left = &sl;
            SetChildTree(s, left, 1);
            p = s->left;
            Loop(p, deep + 1, var_num, solve);
        } else if(solve[deep] < 0) {
            SolveTree *right = &sl;
            SetChildTree(s, right, 0);
            p = s->right;
            Loop(p, deep + 1, var_num, solve);
        }
        else{
            if(!is_solve) {
                SolveTree *left = &sl;
                SetChildTree(s, left, 1);
                p = s->left;
                Loop(p, deep + 1, var_num, solve);
            }
            if(!is_solve) {
                if (deep == var_num) {
                    solve = s->solve;
                    is_solve = true;
                    return;
                }
            }
            if(!is_solve) {
                SolveTree sr = SolveTree(s->node_id + 1, s->clause_num);
                SolveTree *right = &sr;
                SetChildTree(s, right, 0);
                p = s->right;
                Loop(p, deep + 1, var_num, solve);
            }
        }
    }
    return;
}

void Loop(SolveTree *s, int deep, int &var_num, vector<vector<int>> &result) {
    if (deep > var_num) return;
    if (isMaySatisfiable(s)) {
        SolveTree sl = SolveTree(s->node_id + 1, s->clause_num);
        SolveTree *left = &sl;
        SetChildTree(s, left, 1);
        SolveTree *p = s->left;
        Loop(p, deep + 1, var_num, result);
        {
            if (deep == var_num) {
                result.push_back(s->solve);
            }
        }
        /*if (deep < min_dp) {
            double tmp_process = 1;
            double process = 0;
            for (int i = 0; i < s->solve.size(); ++i) {
                tmp_process /= 2;
                if (s->solve[i] == 0) {
                    process += tmp_process;
                }
            }
            min_dp = deep;
            long long int tmp_solve_num = solve_num + result.size();
            cout << "solve_num : " << tmp_solve_num << " time : " << (clock() - start) / CLOCKS_PER_SEC << " process : "
                 << process << " min_deep : " << min_dp << endl;
        }*/
        SolveTree sr = SolveTree(s->node_id + 1, s->clause_num);
        SolveTree *right = &sr;
        SetChildTree(s, right, 0);
        p = s->right;
        Loop(p, deep + 1, var_num, result);
    }
    return;
}


void Loop3(SolveTree* s, int deep, int& var_num, vector<int>& solve) {
    if (deep >= var_num) {
        if (isMaySatisfiable(s)) {
            solve = s->solve;
            is_solve = true;
        }
        return;
    }
    if (isMaySatisfiable(s)) {
        if (!is_solve) {
            SolveTree sl = SolveTree(s->node_id + 1, s->clause_num);
            SolveTree* child = &sl;
            SolveTree* p = nullptr;
            if (solve[deep] > 0) {
                if (!is_solve) {
                    SetChildTree(s, child, 1);
                    p = s->left;
                    Loop3(p, deep + 1, var_num, solve);
                }
            }
            else if (solve[deep] < 0) {
                if (!is_solve) {
                    SetChildTree(s, child, 0);
                    p = s->right;
                    Loop3(p, deep + 1, var_num, solve);
                }
            }
            else {
                int left_or_right = rand() % 2;
                if (!is_solve) {
                    SetChildTree(s, child, left_or_right);
                    if (s->left == nullptr) {
                        p = s->right;
                    }
                    else {
                        p = s->left;
                    }
                    Loop3(p, deep + 1, var_num, solve);
                }
                if (!is_solve) {
                    left_or_right = 1 - left_or_right;
                    SetChildTree(s, child, left_or_right);
                    if (s->left == nullptr) {
                        p = s->right;
                    }
                    else {
                        p = s->left;
                    }
                    Loop3(p, deep + 1, var_num, solve);
                }
            }
        }
    }
    return;
}

void allSolves(Question &q, Solves &s) {
    SolveTree st = SolveTree(1, q.clause_num);
    SolveTree *root;
    root = &st;
    min_dp = q.var_num;
    root->clause = q.clause;
    Loop(root, 0, q.var_num, s.solve);
    s.solve_num=s.solve.size();
    cout << "solve_num : " << solve_num + s.solve_num << endl;
}

bool isSolve(Question &q, vector<int> solve) {
    SolveTree st = SolveTree(1, q.clause_num);
    SolveTree *root;
    root = &st;
    min_dp = q.var_num;
    root->clause = q.clause;
    is_solve = false;
    Loop(root, 0, q.var_num, solve);
    return is_solve;
}

vector<int> findSolve(Question &q, vector<int> solve) {
    return vector<int>();
    SolveTree st = SolveTree(1, q.clause_num);
    SolveTree *root;
    root = &st;
    min_dp = q.var_num;
    root->clause = q.clause;
    Loop(root, 0, q.var_num, solve);
}

void randSolves(Question& q, Solves& sol) {
    SolveTree st = SolveTree(1, q.clause_num);
    SolveTree* root;
    root = &st;
    root->clause = q.clause;
    vector<int> tmp(q.var_num,0);
    tmp = { 0,0,-1,0,1,-1,1,1,-1,-1,1,-1,-1,-1,-1,-1 };
    is_solve = false;
    srand(time(0));
    Loop3(root, 0, q.var_num, tmp);
    return;
}

set<vector<int>> randSolves(Question& q, Solves& sol, int sol_num) {
    SolveTree st = SolveTree(1, q.clause_num);
    SolveTree* root;
    root = &st;
    root->clause = q.clause;
    set<vector<int>> result;
    srand(time(0));
    for (int i = 0; result.size() < sol_num; ++i) {
        is_solve = false;
        vector<int> tmp(q.var_num, 0);
        for (int j = 0; j < q.var_num; ++j) {
            tmp[j] = rand() % 3 - 1;
        }
        Loop3(root, 0, q.var_num, tmp);
        if (is_solve) {
            result.insert(tmp);
        }
        cout << result.size() << endl;
    }
    return result;
}

bool isMaySatisfiable(SolveTree *s) {
    for (int i = 0; i < s->clause_num; ++i) {
        if (s->clause[i].size() == 1 && s->clause[i][0] == 0)
            return false;
    }
    return true;
}

void SetChildTree(SolveTree *f, SolveTree *c, int value) {
    c->clause = f->clause;
    //c->clause_num = f->clause_num;
    c->parent = f;
    //c->node_id = f->node_id + 1;
    c->solve = f->solve;
    c->solve.push_back(value);
    if (value == 1) {
        for (int i = 0; i < c->clause_num; ++i) {
            for (int j = 0; i < c->clause_num && j < c->clause[i].size(); ++j) {
                if (c->clause[i][j] == f->node_id) {
                    int index = i;
                    c->clause.erase(begin(c->clause) + i);
                    --c->clause_num;
                    i = index;
                    j = -1;
                }
                if (i < c->clause_num && j >= 0 && c->clause[i][j] + f->node_id == 0) {
                    c->clause[i].erase(begin(c->clause[i]) + j);
                    --j;
                }
            }
        }
        f->left = c;
    } else {
        for (int i = 0; i < c->clause_num; ++i) {
            for (int j = 0; i < c->clause_num && j < c->clause[i].size(); ++j) {
                if (c->clause[i][j] + f->node_id == 0) {
                    int index = i;
                    c->clause.erase(begin(c->clause) + i);
                    --c->clause_num;
                    i = index;
                    j = -1;
                }
                if (i < c->clause_num && j >= 0 && c->clause[i][j] == f->node_id) {
                    c->clause[i].erase(begin(c->clause[i]) + j);
                    --j;
                }
            }
        }
        f->right = c;
    }
    return;
}