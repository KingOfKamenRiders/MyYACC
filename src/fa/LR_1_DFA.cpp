//
// Created by Logan Xu on 2018/11/13.
//

#include "LR_1_DFA.h"
#include <algorithm>
#include "../util.h"
#include <iostream>
extern map<char,vector<string>> prods;
extern vector<production> productions;

/**
 *
 * @param s the str you'd like to get FIRST set from
 * @param res the result will be added to this set
 * it is a recursive function
 */
void LR_1_DFA::first(const string& s,set<char>& res) {
    int len = s.length();
    for(int i = 0;i<len;i++){
        if(isupper(s[i])){
            for(auto it = prods[s[i]].begin();it!=prods[s[i]].end();it++){
                first(*it,res);
            }
        }else{
            res.insert(s[i]);
        }
        if(res.size()>0){
            if(!res.count(EPSILON)){
                break;
            }else{
                res.erase(EPSILON);
            }
        }
    }
}
/**
 *
 * @param items :LR(0)items, like [S -> {dot}ABc]
 * @param core :set of LR(1)items
 * @return epsilon_closure of the core
 */
set<LR_1_item> LR_1_DFA::epsilonClosure(set<LR_0_item> &items, set<LR_1_item> core) {
    set<LR_1_item> res,visited;
    queue<LR_1_item> left;
    for(auto it = core.begin();it != core.end();it++) {
        left.push(*it);
        res.insert(*it);
    }
    while(!left.empty()){
        LR_1_item cur = left.front(); left.pop();
        if(isupper(cur.item.afterDot)){
            const vector<string>& ps = prods[cur.item.afterDot];
            for(auto it = items.begin();it!=items.end();it++){
                if(it->VN == cur.item.afterDot && it->dotPos == 0){
                    set<char> First;
                    string tail = productions[cur.item.productionId].rhs.substr(cur.item.dotPos+1);
                    first(tail+cur.predictSymbol,First);
                    for(auto itt = First.begin();itt!=First.end();itt++){
                        LR_1_item next(*it,*itt);
                        if(!visited.count(next)){
                            visited.insert(next);
                            left.push(next);
                        }
                        res.insert(next);
                    }
                }
            }
        }
    }
    return res;
}
/**
 *
 * @param items :LR(0)items, like [S -> {dot}ABc]
 * @param node :node_id in the dfa(start node)
 * @param value :the value of the edge, a VN or VT
 * @return
 */
set<LR_1_item> LR_1_DFA::subSetConstruction(set<LR_0_item> &items, int node, char value) {
    set<LR_1_item> res;
    set<LR_1_item> core = nodes[node];
    for(auto it = core.begin(); it!= core.end();it++){
        if(it->item.afterDot == value){
            int pid = it->item.productionId;
            int dp = it->item.dotPos;
            LR_0_item next(pid,dp+1);
            next.VN = it->item.VN;
            if(next.dotPos < productions[pid].rhs.length()){
                next.afterDot = productions[pid].rhs[next.dotPos];
            }else{
                next.dotPos = productions[pid].rhs.length();
                next.afterDot = EPSILON;
            }
            res.insert(LR_1_item(next,it->predictSymbol));
        }
    }
    return res;
}

/**
 *
 * @param items :LR(0)items, like [S -> {dot}ABc]
 * the constructor of a LR(1)DFA
 */
LR_1_DFA::LR_1_DFA(set<LR_0_item> &items) {
    LR_1_item s = LR_1_item(*items.begin(),ESYMBOL);
    set<LR_1_item> I0 = epsilonClosure(items,set<LR_1_item>{s});
    nodes.push_back(I0);
    edges.push_back(vector<edge>());
    queue<int> q;
    q.push(id);
    node_id[I0] = id++;
    while(!q.empty()){
        int cur = q.front(); q.pop();
        set<char> eVals;
        for(auto it = nodes[cur].begin();it != nodes[cur].end();it++){
            if(it->item.afterDot != EPSILON )
                eVals.insert(it->item.afterDot);
        }
        for(auto it = eVals.begin();it != eVals.end();it++){
            set<LR_1_item> core = subSetConstruction(items,cur,*it);
            set<LR_1_item> n = epsilonClosure(items,core);
            if(!node_id.count(n)){
                nodes.push_back(n);
                q.push(id);
                node_id[n] = id++;
                edges.push_back(vector<edge>());
            }
            edges[cur].push_back(edge(*it,node_id[n]));
        }
    }
}