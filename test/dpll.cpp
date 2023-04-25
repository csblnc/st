#include "../../DPLL/file_operator.h"
#include "dpll.h"
#include <iostream>
#include <stack>

clock_t start = clock();
long long int solve_num = 0;
int min_dp;
bool is_solve;
int count;
int count_index;
set<int> conflict;
int fixed_index, unfixed_index;

void SetChildTree(SolveTree *pSt, SolveTree *pSt1, int i);
bool isMaySatisfiable(SolveTree *pSt);
void partlyMapToNew(const Question &q, Question &q_new, vector<int> &initSolve);
void partlyMapToOrg(const Question &q_new, vector<int> &initSolve);

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

//Loop3_bak
//void Loop3_bak(SolveTree* s, int deep, int& var_num, vector<int>& solve) {
//    ++count_index;
//    if (deep >= var_num) {
//        if (isMaySatisfiable(s)) {
//            solve = s->solve;
//            is_solve = true;
//        }
//        return;
//    }
//    if(count_index>count){
//        return;
//    }
//    if (isMaySatisfiable(s)) {
//        if (!is_solve) {
//            SolveTree sl = SolveTree(s->node_id + 1, s->clause_num);
//            SolveTree* child = &sl;
//            SolveTree* p = nullptr;
//            if (solve[deep] > 0) {
//                if (!is_solve) {
//                    SetChildTree(s, child, 1);
//                    p = s->left;
//                    Loop3(p, deep + 1, var_num, solve);
//                }
//            }
//            else if (solve[deep] < 0) {
//                if (!is_solve) {
//                    SetChildTree(s, child, 0);
//                    p = s->right;
//                    Loop3(p, deep + 1, var_num, solve);
//                }
//            }
//            else {
//                int left_or_right = rand() % 2;
//                if (!is_solve) {
//                    SetChildTree(s, child, left_or_right);
//                    if (s->left == nullptr) {
//                        p = s->right;
//                    }
//                    else {
//                        p = s->left;
//                    }
//                    Loop3(p, deep + 1, var_num, solve);
//                }
//                if (!is_solve) {
//                    left_or_right = 1 - left_or_right;
//                    SetChildTree(s, child, left_or_right);
//                    if (s->left == nullptr) {
//                        p = s->right;
//                    }
//                    else {
//                        p = s->left;
//                    }
//                    Loop3(p, deep + 1, var_num, solve);
//                }
//            }
//        }
//    }
//    else{
//        for(int i=s->node_id-1;i<solve.size();++i){
//            solve[i]=0;
//        }
////        for(int i=s->node_id-1;i<solve.size();++i){
////            solve[i]=0;
////            SolveTree sl = SolveTree(s->node_id + 1, s->clause_num);
////            SolveTree* child = &sl;
////            SetChildTree(s, child, 1);
////            SolveTree* p = s->left;
////            Loop(p, deep + 1, var_num, solve);
////        }
//    }
//    return;
//}

void Loop3(SolveTree* s, int &deep, int& var_num, vector<int>& solve) {
    ++count_index;
    if (s->node_id-1 >= var_num) {
        if (isMaySatisfiable(s)) {
            solve = s->solve;
            is_solve = true;
        }
        return;
    }
    if(count_index>count){
        return;
    }
    if (isMaySatisfiable(s)) {
        if (!is_solve&&s->node_id<=deep) {
            ++deep;
            SolveTree sl = SolveTree(s->node_id + 1, s->clause_num);
            SolveTree* child = &sl;
            SolveTree* p = nullptr;
            if (solve[s->node_id-1] > 0) {
                if (!is_solve) {
                    SetChildTree(s, child, 1);
                    p = s->left;
                    Loop3(p, deep, var_num, solve);
                }
            }
            else if (solve[s->node_id-1] < 0) {
                if (!is_solve) {
                    SetChildTree(s, child, 0);
                    p = s->right;
                    Loop3(p, deep, var_num, solve);
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
                    Loop3(p, deep, var_num, solve);
                }
                if (!is_solve) {
                    s->left= nullptr;
                    s->right= nullptr;
                    left_or_right = 1 - left_or_right;
                    SetChildTree(s, child, left_or_right);
                    if (s->right == nullptr) {
                        p = s->left;
                    }
                    else {
                        p = s->right;
                    }
                    Loop3(p, deep, var_num, solve);
                }
            }
        }
        else{
            return;
        }
    }
    else{
        for(int i=s->node_id-1;i<solve.size();++i){
            solve[i]=0;
        }
        --deep;
        
//        for(int i=s->node_id-1;i<solve.size();++i){
//            solve[i]=0;
//            SolveTree sl = SolveTree(s->node_id + 1, s->clause_num);
//            SolveTree* child = &sl;
//            SetChildTree(s, child, 1);
//            SolveTree* p = s->left;
//            Loop(p, deep + 1, var_num, solve);
//        }
    }
    return;
}

void Loop5(SolveTree* s, int &deep, int& var_num, vector<int>& solve) {
    ++count_index;
    if (fixed_index>=var_num&&unfixed_index>=var_num) {
        if (isMaySatisfiable(s)) {
            solve = s->solve;
            is_solve = true;
        }
        return;
    }
    if(count_index>count){
        return;
    }
    if (isMaySatisfiable(s)) {
        if (!is_solve) {
            int nid;
            ++deep;
            if(fixed_index<var_num){
                fixed_index=s->node_id;
                while (fixed_index<var_num&&solve[fixed_index]==0){
                    ++fixed_index;
                }
                if(fixed_index<=var_num){
                    nid=fixed_index+1;
                }else{
                    nid=unfixed_index;
                }
            }else{
                unfixed_index=s->node_id;
                while (fixed_index<var_num&&solve[fixed_index]!=0){
                    ++unfixed_index;
                }
                if(unfixed_index<=var_num){
                    nid=unfixed_index+1;
                }else{
                    Loop5(s, deep, var_num, solve);
                }
            }
            SolveTree sl = SolveTree(nid, s->clause_num);
            SolveTree* child = &sl;
            SolveTree* p = nullptr;
            if (solve[s->node_id-1] > 0) {
                if (!is_solve) {
                    SetChildTree(s, child, 1);
                    p = s->left;
                    Loop5(p, deep, var_num, solve);
                }
            }
            else if (solve[s->node_id-1] < 0) {
                if (!is_solve) {
                    SetChildTree(s, child, 0);
                    p = s->right;
                    Loop5(p, deep, var_num, solve);
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
                    Loop5(p, deep, var_num, solve);
                }
                if (!is_solve) {
                    s->left= nullptr;
                    s->right= nullptr;
                    left_or_right = 1 - left_or_right;
                    SetChildTree(s, child, left_or_right);
                    if (s->right == nullptr) {
                        p = s->left;
                    }
                    else {
                        p = s->right;
                    }
                    Loop5(p, deep, var_num, solve);
                }
            }
        }
        else{
            return;
        }
    }
    else{
        if(conflict.find(s->node_id)!=conflict.end()||conflict.size()==0){
            conflict.insert(s->node_id);
            int t=solve[s->node_id-1];
            solve[s->node_id-1]=-t;
        }
        else{
            conflict.erase(s->node_id);
            conflict.insert(s->parent->node_id);
            int t=solve[s->node_id-1];
            solve[s->node_id-1]=-t;
        }
        --deep;

//        for(int i=s->node_id-1;i<solve.size();++i){
//            solve[i]=0;
//            SolveTree sl = SolveTree(s->node_id + 1, s->clause_num);
//            SolveTree* child = &sl;
//            SetChildTree(s, child, 1);
//            SolveTree* p = s->left;
//            Loop(p, deep + 1, var_num, solve);
//        }
    }
    return;
}

//void Loop4(SolveTree* s, int deep, int& var_num, vector<int>& solve, vector<double> &probability) {
//    ++count_index;
//    if (deep >= var_num) {
//        if (isMaySatisfiable(s)) {
//            solve = s->solve;
//            is_solve = true;
//        }
//        return;
//    }
//    if(count_index>count){
//        return;
//    }
//    if (isMaySatisfiable(s)) {
//        if (!is_solve) {
//            SolveTree sl = SolveTree(s->node_id + 1, s->clause_num);
//            SolveTree* child = &sl;
//            SolveTree* p = nullptr;
//            if (solve[deep] > 0) {
//                if (!is_solve) {
//                    SetChildTree(s, child, 1);
//                    p = s->left;
//                    Loop3(p, deep + 1, var_num, solve);
//                }
//            }
//            else if (solve[deep] < 0) {
//                if (!is_solve) {
//                    SetChildTree(s, child, 0);
//                    p = s->right;
//                    Loop3(p, deep + 1, var_num, solve);
//                }
//            }
//            else {
//                int left_or_right=0;
//                double k = (double)rand() / RAND_MAX;
//                if(k<probability[deep]){
//                    left_or_right=1;
//                }
//                if (!is_solve) {
//                    SetChildTree(s, child, left_or_right);
//                    if (s->left == nullptr) {
//                        p = s->right;
//                    }
//                    else {
//                        p = s->left;
//                    }
//                    Loop3(p, deep + 1, var_num, solve);
//                }
//                if (!is_solve) {
//                    left_or_right = 1 - left_or_right;
//                    SetChildTree(s, child, left_or_right);
//                    if (s->left == nullptr) {
//                        p = s->right;
//                    }
//                    else {
//                        p = s->left;
//                    }
//                    Loop3(p, deep + 1, var_num, solve);
//                }
//            }
//        }
//    }
//    else{
//        for(int i=s->node_id-1;i<solve.size();++i){
//            solve[i]=0;
//        }
//    }
//    return;
//}

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
    int deep=1;
    Loop3(root, deep, q.var_num, tmp);
    return;
}

//conflict abandon
set<vector<int>> partlyRandSolves(Question& q, Solves& sol, int sol_num) {
    SolveTree st = SolveTree(1, q.clause_num);
    SolveTree* root;
    root = &st;
    root->clause = q.clause;
    set<vector<int>> result;
    srand(time(0));
    for (int i = 0; result.size() < sol_num; ++i) {
        is_solve = false;
        count=int(q.var_num*1.2);
        count_index=0;
        vector<int> tmp(q.var_num, 0);
        for (int j = 0; j < q.var_num; ++j) {
            int a=rand()%100;
            if(a<10) tmp[j]=1;
            else if(a>=90) tmp[j]=-1;
            else continue;
        }
        //partlyMapToNew(q,q_new,tmp);
        int deep=1;
        fixed_index=1;
        while(tmp[fixed_index-1]==0&&fixed_index<=q.var_num){
            ++fixed_index;
        }
        root->node_id=fixed_index;
        unfixed_index=1;
        while(tmp[unfixed_index-1]!=0&&fixed_index<=q.var_num){
            ++unfixed_index;
        }
        conflict.clear();
        Loop5(root, deep, q.var_num, tmp);
        if (is_solve) {
            //partlyMapToOrg(q_new,tmp);
            result.insert(tmp);
        }
        cout << result.size() << endl;
    }
    return result;
}

//partlyRandSolves_bak
//set<vector<int>> partlyRandSolves(Question& q, Solves& sol, int sol_num) {
//    SolveTree st = SolveTree(1, q.clause_num);
//    SolveTree* root;
//    root = &st;
//    root->clause = q.clause;
//    set<vector<int>> result;
//    srand(time(0));
//    for (int i = 0; result.size() < sol_num; ++i) {
//        is_solve = false;
//        count=int(q.var_num*1.2);
//        count_index=0;
//        vector<int> tmp(q.var_num, 0);
////        for (int j = 0; j < q.var_num; ++j) {
////            tmp[j] = rand() % 3 - 1;
////        }
//        for (int j = 0; j < q.var_num; ++j) {
//            int a=rand()%100;
//            if(a<10) tmp[j]=1;
//            else if(a>=90) tmp[j]=-1;
//            else continue;
//        }
//        Question q_new;
//        partlyMapToNew(q,q_new,tmp);
//        int deep=1;
//        Loop3(root, deep, q_new.var_num, tmp);
//        if (is_solve) {
//            partlyMapToOrg(q_new,tmp);
//            result.insert(tmp);
//        }
//        cout << result.size() << endl;
//    }
//    return result;
//}

set<vector<int>> allrandSolves(Question& q, Solves& sol, int sol_num) {
    SolveTree st = SolveTree(1, q.clause_num);
    SolveTree* root;
    root = &st;
    root->clause = q.clause;
    set<vector<int>> result;
    srand(time(0));
    for (int i = 0; result.size() < sol_num; ++i) {
        is_solve = false;
        count=int(q.var_num*1.2);
        count_index=0;
        vector<int> tmp(q.var_num, 0);
        int deep=1;
        Loop3(root, deep, q.var_num, tmp);
        if (is_solve) {
            result.insert(tmp);
        }
        cout << result.size() << endl;
    }
    return result;
}

set<vector<int>> randSolves(Question& q, Solves& sol, int sol_num, vector<double> p) {
    SolveTree st = SolveTree(1, q.clause_num);
    SolveTree* root;
    root = &st;
    root->clause = q.clause;
    set<vector<int>> result;
    srand(time(0));
    for (int i = 0; result.size() < sol_num; ++i) {
        is_solve = false;
        count=int(q.var_num*1.2);
        count_index=0;
        vector<int> tmp(q.var_num, 0);
        for (int j = 0; j < q.var_num; ++j) {
            tmp[j] = rand() % 3 - 1;
        }
        //Loop4(root, 0, q.var_num, tmp);
        if (is_solve) {
            result.insert(tmp);
        }
        cout << result.size() << endl;
    }
    return result;
}

bool isMaySatisfiable(SolveTree *s) {
    for (int i = 0; i < s->clause_num; ++i) {
        if (s->clause[i].size() == 1 && s->clause[i][0] == 0){
            cout<<s->node_id<<": conflict!"<<endl;
            return false;
        }
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

void partlyMapToNew(const Question &q, Question &q_new, vector<int> &initSolve){
    q_new.var_num=q.var_num;
    q_new.clause_num=q.clause_num;
    q_new.clause=q.clause;
    q_new.map.resize(q_new.var_num+1,0);
    int i=q_new.var_num,j=q_new.var_num;
    while(i>0){
        while(initSolve[i-1]==0&&i==j) {
            --i;--j;
        }
        if(initSolve[i-1]!=0){
            --i;
        }
        else{
            //initSolve
            initSolve[i-1]=initSolve[j-1];
            initSolve[j-1]=0;
            //clause
            for(int k=0;k<q_new.clause_num;++k){
                for(int id=0;id<q_new.clause[k].size();++id){
                    if(q_new.clause[k][id]==i){
                        q_new.clause[k][id]=j;
                    }
                    else if(q_new.clause[k][id]==-i){
                        q_new.clause[k][id]=-j;
                    }
                    else if(q_new.clause[k][id]==j){
                        q_new.clause[k][id]=i;
                    }
                    else if(q_new.clause[k][id]==-j){
                        q_new.clause[k][id]=-i;
                    }
                }
            }
            //map
            q_new.map[i]=j;
            --i;--j;
        }
    }
    return;
}

void partlyMapToOrg(const Question &q_new, vector<int> &initSolve){
    for(int i=1;i<q_new.var_num+1;++i){
        if(q_new.map[i]!=0){
            int tmp=initSolve[i-1];
            initSolve[i-1]=initSolve[q_new.map[i]-1];
            initSolve[q_new.map[i]-1]=tmp;
        }
    }
    return;
}
