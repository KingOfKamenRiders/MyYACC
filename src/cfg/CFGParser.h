//
// Created by Logan Xu on 2018/11/13.
//

#include "LR_0_item.h"
#include  "production.h"
#include "../util.h"
#include <set>
#include <map>
#include <vector>
#include <string>
using namespace std;
#ifndef MYYACC_CFGPARSER_H
#define MYYACC_CFGPARSER_H


class CFGParser {
public:
    /**
     *
     * @param path : path of the .y file
     * @param items : the LR(0)items will be added here
     * @return
     * this function parse productions to object & create LR(0)items
     */
    static vector<production> readCFG(const string& path, set<LR_0_item>& items);

};


#endif //MYYACC_CFGPARSER_H
