//
// Created by Logan Xu on 2018/11/14.
//
#include "LR_0_item.h"
#ifndef MYYACC_LR_1_ITEM_H
#define MYYACC_LR_1_ITEM_H


class LR_1_item {
public:
    LR_0_item item;
    char predictSymbol;
    LR_1_item(LR_0_item i,char s):item(i),predictSymbol(s){}
    bool operator<(const LR_1_item& other) const{
        return item == other.item ? (predictSymbol<other.predictSymbol): (item<other.item);
    }
};


#endif //MYYACC_LR_1_ITEM_H
