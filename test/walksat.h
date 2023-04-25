//
// Created by huawei on 2023/4/18.
//

#ifndef MAIN_CPP_WALKSAT_H
#define MAIN_CPP_WALKSAT_H

#include <vector>
#include <string>

typedef struct cs{
    int clause_num;
    int var_num;
    std::vector<int> clause_sat_times;
    std::vector<std::vector<int>> var_covered_list;
}walksat;

typedef struct ws{
    std::vector<int> solve;

}walksat_solve;

void WalkSat(std::string Fcnf, std::string Fsolve);

#endif //MAIN_CPP_WALKSAT_H
