//
// Created by Logan Xu on 2018/11/13.
//

#ifndef MYYACC_LR_0_ITEM_H
#define MYYACC_LR_0_ITEM_H


class LR_0_item {
public:
    int productionId,dotPos;
    char afterDot,VN;
    LR_0_item(int p = -1,int pos = -1,char c = 0,char v = 0):productionId(p),dotPos(pos),afterDot(c),VN(v){}
    bool operator<(const LR_0_item& other) const{
        return productionId == other.productionId? dotPos<other.dotPos:productionId<other.productionId;
    }
    bool operator == (const LR_0_item& other) const {
        return productionId == other.productionId && dotPos == other.dotPos;
    }
};


#endif //MYYACC_LR_0_ITEM_H
