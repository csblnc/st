//
// Created by huawei on 2023/3/1.
//

#ifndef MAIN_CPP_JSONHELPER_H
#define MAIN_CPP_JSONHELPER_H

#include <cstdio>
#include <vector>

struct origin_data{
    std::vector<std::string> key;
    std::vector<std::vector<std::vector<int>>> val;
    std::vector<int> num_var;
    std::vector<int> num_clauses;
};

class jsonHelper {
    origin_data od;

    void Read(std::string fileName);

    //void ReadandWriteCNF(std::string fileName);
    void ReadandWriteCNF(std::string fileName, std::string directoryPath);
public:
    void GetOriginData(std::string fileName);
    void GetOriginData(std::string fileName,std::string directoryPath);

    void ModifyLineData(std::string fileName, int lineNum, std::string lineData);
};

#endif //MAIN_CPP_JSONHELPER_H
