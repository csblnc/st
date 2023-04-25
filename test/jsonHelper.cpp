//
// Created by huawei on 2023/3/1.
//

#include <vector>
#include <fstream>
#include <iostream>

#include "jsonHelper.h"
#include "shlwapi.h"

using namespace std;

string getfilename(const string filename)//从完整路径名中解析出文件名称，例如：/home/test/abc.txt,解析完成后为abc.txt
{
    int len = filename.size();
    int i;
    for (i = (len - 1); i >= 0; i--)
    {
        if ((filename[i] == '\\') || (filename[i] == '/'))
        {
            break;
        }
    }
    string result=filename.substr(i+1,len-6-i);
    return result;
}

void jsonHelper::GetOriginData(string fileName){
    string fn_no_ex = getfilename(fileName);
    string directoryPath = "E:/LAB/IS/cd/satTest/specification_data/"+fn_no_ex;
    CreateDirectory(directoryPath.c_str(), NULL);
    ReadandWriteCNF(fileName, directoryPath);
    return;
}

void jsonHelper::GetOriginData(string fileName, string directoryPath){
    ReadandWriteCNF(fileName, directoryPath);
    return;
}

void jsonHelper::ReadandWriteCNF(string fileName, string directoryPath) {
    ifstream fin(fileName, std::ios::binary);
    vector<char> buf(static_cast<unsigned int>(fin.seekg(0, std::ios::end).tellg()));
    fin.seekg(0, std::ios::beg).read(&buf[0], static_cast<std::streamsize>(buf.size()));
    fin.close();
    bool bool_key = true, bool_val_outer = false, bool_val_inner = false;
    string fn;
    for (int i = 0; i < buf.size(); ++i) {
        string file_name;
        if (buf[i] == '\"') {
            int p = ++i;
            string tmp_key = "";
            while (buf[p] != '\"') {
                tmp_key += buf[p++];
            }
            file_name=tmp_key;
            i = p;
            bool_key = true;
            fn=directoryPath + "/" + file_name + ".cnf";
//            ofstream outfile(fn, ios::app);
//            if(outfile.good()) {
//                outfile << "c writetest" << endl;
//                outfile.close();
//            }
        }
        else if (buf[i] == ':') {
            int num_var = 0;
            int p = ++i;
            int cnf_count=0;
            vector<int> tmp_lst(1,0);
            vector<vector<int>> tmp_cnf;
            while (buf[p] == ' ')
                ++p;
            if (buf[p++] == '[') {
                bool_val_outer = true;
            }
            while (bool_val_outer) {
                if (buf[p] == '[') {
                    ++p;
                    bool_val_inner = true;
                    vector<int> tmp_val;
                    int tmp_int = 0;
                    int sig = 1;
                    while (bool_val_inner) {
                        if (buf[p] == ']') {
                            if(num_var<tmp_int) num_var=tmp_int;
                            tmp_val.push_back(sig * tmp_int);
                            bool_val_inner = false;
                            tmp_val.push_back(0);
                            if(tmp_val==tmp_lst) { ++p;continue;}
                            tmp_lst=tmp_val;
                            tmp_cnf.push_back(tmp_val);
                            ++cnf_count;
                        } else if (buf[p] == ',') {
                            if(num_var<tmp_int) num_var=tmp_int;
                            tmp_val.push_back(sig * tmp_int);
                            sig = 1;
                            tmp_int = 0;
                        } else if (buf[p] == '-') {
                            sig = -1;
                        } else if (buf[p] >= '0' && buf[p] <= '9') {
                            tmp_int = tmp_int * 10 + buf[p] - '0';
                        }
                        ++p;
                    }
                }
                else if(buf[p]==','||buf[p]=='}') {
                    bool_val_outer = false;
                    int num_clauses=cnf_count;
                    string head = "p cnf " + to_string(num_var) + " " + to_string(num_clauses);
                    ofstream outfile(fn, ios::app);
                    outfile << head << endl;
                    for(int ii=0;ii<tmp_cnf.size();++ii){
                        for(int jj=0;jj<tmp_cnf[ii].size();++jj){
                            outfile << tmp_cnf[ii][jj] << " ";
                        }
                        outfile << endl;
                    }
                    outfile.close();
                }
                ++p;
            }
            i = p;
        }
    }
}

void jsonHelper::ModifyLineData(string fileName, int lineNum, string lineData)
{
    ifstream in;
    in.open(fileName);

    string strFileData = "";
    int line = 1;
    char tmpLineData[1024] = { 0 };
    while (in.getline(tmpLineData, sizeof(tmpLineData)))
    {
        if (line == lineNum)
        {
            strFileData += lineData;
            strFileData += "\n";
        }
        else
        {
            strFileData += tmpLineData;
            strFileData += "\n";
        }
        line++;
    }
    in.close();

    ofstream out;
    out.open(fileName);
    out.flush();
    out << strFileData;
    out.close();
}