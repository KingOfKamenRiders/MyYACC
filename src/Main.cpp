//
// Created by Logan Xu on 2018/11/13.
//
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <sstream>
#include "cfg/LR_0_item.h"
#include "fa/LR_1_DFA.h"
#include "cfg/CFGParser.h"
#include <cstdio>
#include <fstream>
using namespace std;

map<char,vector<string>> prods;
vector<production> productions;

int main(int argc,char* args[]){
    if(argc == 1){
        cout<<"please append your .y file path after the command"<<endl;
        return 0;
    }
    string path = string(args[1]);
    set<LR_0_item> items;

    //read CFG from .y file
    productions = CFGParser::readCFG(path,items);
    for(auto it = productions.begin();it!= productions.end();it++){
        if(!prods.count(it->VN))
            prods[it->VN] = vector<string>();
        prods[it->VN].push_back(it->rhs);
    }
    //construct LR(1)DFA
    LR_1_DFA dfa(items);
    cout<<dfa.nodes.size()<<endl;

    //generate LR(1) parser (mainly the parsing table)

    ifstream in("parser.template");
    string line;
    if(in.fail()){
        cout<<"cannot find .template file. please make sure you have it under the same dir."<<endl;
        return 0;
    }
    ofstream generate("parser.cpp");
    while(getline(in,line)){
        if(line[0] == '%'){
            generate<<"map<int,map<char,string>> PT = {";
            vector<vector<edge>>& edges = dfa.edges;
            int len = edges.size();

            for(int i = 0;i<len; i++){
                generate<<"{"<<i<<", {";
                int len2 = edges[i].size();

                //generate shift & GOTO part
                for(int j = 0;j<len2;j++){
                    generate<<"{ '"<<edges[i][j].val<<"' ,"<<"\"";
                    if(!isupper(edges[i][j].val))
                        generate<<"s";
                    generate<<edges[i][j].dest<<"\"}, ";
                }

                //generate reduction part if the node is reducible
                for(auto it = dfa.nodes[i].begin();it!= dfa.nodes[i].end();it++){
                    production p = productions[it->item.productionId];
                    if(it->item.dotPos == p.rhs.length()){
                        if(it->item.productionId == 0)
                            generate<<"{'"<<it->predictSymbol<<"' ,"<<"\"accept\"}, ";
                        else
                            generate<<"{'"<<it->predictSymbol<<"' ,"<<"\"r"<<it->item.productionId<<"\"}, ";
                    }
                }
                generate<<"}},";
            }
            generate<<"};"<<endl;
        }else if(line[0] == '$'){
            generate<<"vector<production> prods = {";
            int len = productions.size();
            for(int i=0;i< len ;i++){
                generate<<"production('"<<productions[i].VN<<"',\""<<productions[i].rhs<<"\"),";
            }
            generate<<"};"<<endl;
        }else if(line[0] == '/') {
            continue;
        } else
            generate<<line<<endl;
    }

    //now you should see a file named "parser.cpp", compile it and prepare an input token_sequence to run it
    return 0;


}
