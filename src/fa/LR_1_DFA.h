//
// Created by Logan Xu on 2118/11/13.
// this file defines the LR(1)DFA entity class
//
#include <set>
#include <vector>
#include <map>
#include <queue>
#include "../cfg/LR_1_item.h"
#include "../util.h"
#include "../cfg/production.h"

using namespace std;

#ifndef MYYACC_LR_1_DFA_H
#define MYYACC_LR_1_DFA_H

struct edge{
    char val;
    int dest;
    edge(char v,int d):val(v),dest(d){}
};

class LR_1_DFA {
public:
    vector<set<LR_1_item>> nodes;
    map<set<LR_1_item>,int> node_id;
    vector<vector<edge>> edges;
    LR_1_DFA(set<LR_0_item>& items);

private:
    int id = 0;
    /**
     *
     * @param items :LR(0)items, like [S -> {dot}ABc]
     * @param core :set of LR(1)items
     * @return epsilon_closure of the core
     */
    set<LR_1_item> epsilonClosure(set<LR_0_item>& items,set<LR_1_item> core);
    /**
     *
     * @param items :LR(0)items, like [S -> {dot}ABc]
     * @param node :node_id in the dfa(start node)
     * @param value :the value of the edge, a VN or VT
     * @return
     */
    set<LR_1_item> subSetConstruction(set<LR_0_item>& items,int node,char value);
    void first(const string& s,set<char>& res);
};


#endif //MYYACC_LR_1_DFA_H
