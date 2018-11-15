//
// Created by Logan Xu on 2018/11/13.
//

#include "CFGParser.h"
#include "LR_0_item.h"
#include "../util.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

vector<production> CFGParser::readCFG(const string &path, set<LR_0_item> &items) {
    ifstream in(path);
    if(in.fail()){
        cout<<"cannot open file "<<path<<". check your file path."<<endl;
        exit(0);
    }
    string line, VN, rhs,temp;
    vector<production> productions;
    getline(in,line);
    productions.push_back(production(SSYMBOL,line));
    items.insert(LR_0_item(0,0,line[0],SSYMBOL));
    while(getline(in,line)){
        stringstream ss(line);
        ss>>VN>>temp;
        rhs = "";
        while(ss>> temp){
            if(temp == "|"){
                production p(VN[0],rhs);
                productions.push_back(p);
                int pid = productions.size() - 1;
                items.insert(LR_0_item(pid,0,rhs[0],VN[0]));
                rhs = "";
            }else{
                rhs += temp;
            }
        }
        production p(VN[0],rhs);
        productions.push_back(p);
        int pid = productions.size() - 1;
        items.insert(LR_0_item(pid,0,rhs[0],VN[0]));
    }
    return productions;
}