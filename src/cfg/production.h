//
// Created by Logan Xu on 2018/11/14.
//
#include <string>

using namespace std;
#ifndef MYYACC_PRODUCTION_H
#define MYYACC_PRODUCTION_H

struct production{
    char VN;
    string rhs;
    production(char v,string s):VN(v),rhs(s){}
};

#endif //MYYACC_PRODUCTION_H
