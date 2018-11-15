#include <iostream>
#include <fstream>
#include <stack>
#include <map>
#include <string>
#include <sstream>
#include <cstdio>
#include <vector>

using namespace std;

map<int,map<char,string>> PT = {{0, {{ '(' ,"s1"}, { 'E' ,"2"}, { 'F' ,"3"}, { 'T' ,"4"}, { 'i' ,"s5"}, }},{1, {{ '(' ,"s6"}, { 'E' ,"7"}, { 'F' ,"8"}, { 'T' ,"9"}, { 'i' ,"s10"}, }},{2, {{ '+' ,"s11"}, { '-' ,"s12"}, {'$' ,"accept"}, }},{3, {{'$' ,"r6"}, {'*' ,"r6"}, {'+' ,"r6"}, {'-' ,"r6"}, {'/' ,"r6"}, }},{4, {{ '*' ,"s13"}, { '/' ,"s14"}, {'$' ,"r3"}, {'+' ,"r3"}, {'-' ,"r3"}, }},{5, {{'$' ,"r8"}, {'*' ,"r8"}, {'+' ,"r8"}, {'-' ,"r8"}, {'/' ,"r8"}, }},{6, {{ '(' ,"s6"}, { 'E' ,"15"}, { 'F' ,"8"}, { 'T' ,"9"}, { 'i' ,"s10"}, }},{7, {{ ')' ,"s16"}, { '+' ,"s17"}, { '-' ,"s18"}, }},{8, {{')' ,"r6"}, {'*' ,"r6"}, {'+' ,"r6"}, {'-' ,"r6"}, {'/' ,"r6"}, }},{9, {{ '*' ,"s19"}, { '/' ,"s20"}, {')' ,"r3"}, {'+' ,"r3"}, {'-' ,"r3"}, }},{10, {{')' ,"r8"}, {'*' ,"r8"}, {'+' ,"r8"}, {'-' ,"r8"}, {'/' ,"r8"}, }},{11, {{ '(' ,"s1"}, { 'F' ,"3"}, { 'T' ,"21"}, { 'i' ,"s5"}, }},{12, {{ '(' ,"s1"}, { 'F' ,"3"}, { 'T' ,"22"}, { 'i' ,"s5"}, }},{13, {{ '(' ,"s1"}, { 'F' ,"23"}, { 'i' ,"s5"}, }},{14, {{ '(' ,"s1"}, { 'F' ,"24"}, { 'i' ,"s5"}, }},{15, {{ ')' ,"s25"}, { '+' ,"s17"}, { '-' ,"s18"}, }},{16, {{'$' ,"r7"}, {'*' ,"r7"}, {'+' ,"r7"}, {'-' ,"r7"}, {'/' ,"r7"}, }},{17, {{ '(' ,"s6"}, { 'F' ,"8"}, { 'T' ,"26"}, { 'i' ,"s10"}, }},{18, {{ '(' ,"s6"}, { 'F' ,"8"}, { 'T' ,"27"}, { 'i' ,"s10"}, }},{19, {{ '(' ,"s6"}, { 'F' ,"28"}, { 'i' ,"s10"}, }},{20, {{ '(' ,"s6"}, { 'F' ,"29"}, { 'i' ,"s10"}, }},{21, {{ '*' ,"s13"}, { '/' ,"s14"}, {'$' ,"r1"}, {'+' ,"r1"}, {'-' ,"r1"}, }},{22, {{ '*' ,"s13"}, { '/' ,"s14"}, {'$' ,"r2"}, {'+' ,"r2"}, {'-' ,"r2"}, }},{23, {{'$' ,"r4"}, {'*' ,"r4"}, {'+' ,"r4"}, {'-' ,"r4"}, {'/' ,"r4"}, }},{24, {{'$' ,"r5"}, {'*' ,"r5"}, {'+' ,"r5"}, {'-' ,"r5"}, {'/' ,"r5"}, }},{25, {{')' ,"r7"}, {'*' ,"r7"}, {'+' ,"r7"}, {'-' ,"r7"}, {'/' ,"r7"}, }},{26, {{ '*' ,"s19"}, { '/' ,"s20"}, {')' ,"r1"}, {'+' ,"r1"}, {'-' ,"r1"}, }},{27, {{ '*' ,"s19"}, { '/' ,"s20"}, {')' ,"r2"}, {'+' ,"r2"}, {'-' ,"r2"}, }},{28, {{')' ,"r4"}, {'*' ,"r4"}, {'+' ,"r4"}, {'-' ,"r4"}, {'/' ,"r4"}, }},{29, {{')' ,"r5"}, {'*' ,"r5"}, {'+' ,"r5"}, {'-' ,"r5"}, {'/' ,"r5"}, }},};

struct state{
    int n_id;
    char c;
    state(int i,char ch):n_id(i),c(ch){}
};
struct production{
    char VN;
    string rhs;
    production(char v,string s):VN(v),rhs(s){}
};

vector<production> prods = {production('#',"E"),production('E',"E+T"),production('E',"E-T"),production('E',"T"),production('T',"T*F"),production('T',"T/F"),production('T',"F"),production('F',"(E)"),production('F',"i"),};

int my_atoi(string cmd){
    stringstream ss(cmd);
    int res;
    ss>>res;
    return res;
}


int main(int argc ,char* argv[]){
    freopen("production_sequence.txt","w",stdout);
    if(argc == 1){
        cout<<"please append your input file name after command!"<<endl;
        return 0;
    }
    ifstream in(argv[1]);
    if(in.fail()){
        cout<<"fail to open file ["<<argv[1]<<"]. check your file name."<<endl;
        return 0;
    }
    stack<state> s;
    s.push(state(0,'#'));
    char cur;
    while((cur = in.get()) != EOF){
        state top = s.top();
        string cmd = PT[top.n_id][cur];
        if(cmd[0] == 's'){
            s.push(state(my_atoi(cmd.substr(1)),cur));
        }else if(cmd[0] == 'r'){
            production p = prods[my_atoi(cmd.substr(1))];
            int len = p.rhs.length();
            char VN = p.VN;
            for(int i = 0;i <len ;i++)
                s.pop();
            int nextState = my_atoi(PT[s.top().n_id][VN]);
            s.push(state(nextState,VN));
            cout<<p.VN<<" -> "<<p.rhs<<endl;
            in.unget();
        }else if(cmd[0] == 'a'){
            cout<<"parsing finished."<<endl;
            break;
        }else{
            cout<<"you have an syntax err!"<<endl;
            break;
        }

    }


    return 0;
}

