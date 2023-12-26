#include <iostream>
#include <iterator>
#include <set>
#include <cstring>
#include <vector>
#include <assert.h>

#define ll long long int
using namespace std;

//variable
ll rightsum = 0;
ll leftsum = 0;
multiset<ll> lefttree;
multiset<ll> righttree;

//functions
void insert_num(ll);
void remove_num(ll);
void merge(ll);
void check();

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    ll inbuf;
    char command[5];
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%s", command);
        if(!strcmp(command,"kiwi"))
        {
            scanf("%lld", &inbuf);
            insert_num(inbuf);
        }
        else if(!strcmp(command,"wiki"))
        {
            scanf("%lld", &inbuf);
            remove_num(inbuf);
        }
        else if(!strcmp(command,"wiwi"))
        {
            cout << rightsum - leftsum + *lefttree.rbegin() * ((long)lefttree.size() - (long)righttree.size()) << "\n";
        }
        else if(!strcmp(command,"kiki"))
        {

            scanf("%lld", &inbuf);
            merge(inbuf);
        }
        else cerr << "wrong command\n";
    }
}


void insert_num(ll num){
    if(lefttree.size() == 0 || num <= *lefttree.rbegin()) 
    {
        leftsum += num;
        lefttree.insert(num);
    }
    else 
    {
        rightsum += num;
        righttree.insert(num);
    }
    check();
    return;
}

void remove_num(ll num){
    if(*lefttree.rbegin() >= num)
    {
        if(lefttree.find(num) != lefttree.end())lefttree.erase(lefttree.find(num));
        leftsum -= num;
    }
    else
    {
        if(righttree.find(num) != righttree.end())righttree.erase(righttree.find(num));
        rightsum -= num;
    }
    check();
    return;
}

void check(){
    while (righttree.size() > lefttree.size())
    {
        multiset<ll>::iterator it = righttree.begin();
        ll tmpmv = *it;
        lefttree.insert(tmpmv);
        leftsum += tmpmv;
        rightsum -= tmpmv;
        righttree.erase(righttree.find(tmpmv));
    }
    while (lefttree.size() > righttree.size()+1)
    {
        multiset<ll>::reverse_iterator it = lefttree.rbegin();
        ll tmpmv = *it;
        righttree.insert(tmpmv);
        rightsum += tmpmv;
        leftsum -= tmpmv;
        lefttree.erase(lefttree.find(tmpmv));
    }
}

void merge(ll k){
    if(lefttree.size() + righttree.size() <= k) return;
    if(k == 1)
    {
        leftsum += rightsum;
        rightsum = 0;
        lefttree.clear();
        righttree.clear();
        lefttree.insert(leftsum);
        return;
    }
    if(k >= lefttree.size()){
        ll tomodify = lefttree.size() + righttree.size() - k;
        vector<ll> remvec;
        remvec.resize(tomodify,0);
        for(ll i = 0; i < tomodify; i++)
        {
            multiset<ll>::iterator it = lefttree.begin();
            remvec[i] += *it;
            leftsum -= *it;
            lefttree.erase(it);
        }
        for(ll i = tomodify; i > 0; i--)
        {
            multiset<ll>::reverse_iterator itr = righttree.rbegin();
            remvec[i-1] += *itr;
            rightsum -= *itr;
            righttree.erase(--itr.base());
        }
        for(ll i = 0; i < tomodify; i++){
            rightsum += remvec[i];
            righttree.insert(remvec[i]);
        }
        check();
    }
    else
    {
        vector<ll> remvec;
        remvec.resize(k,0);
        ll ct = k;
        for(auto it = righttree.rbegin(); it != righttree.rend(); it++)
        {
            ct--;
            remvec[ct] += *it;
            if(ct == 0) ct = k;
        }
        for(auto it = lefttree.rbegin(); it != lefttree.rend(); it++)
        {
            ct--;
            remvec[ct] += *it;
            if(ct == 0) ct = k;
        }
        lefttree.clear();
        righttree.clear();
        leftsum = 0;
        rightsum = 0;
        for(ll i = 0; i < k/2; i++)
        {
            lefttree.insert(remvec[i]);
            leftsum += remvec[i];
        }
        for(ll i = k/2; i < k; i++)
        {
            righttree.insert(remvec[i]);
            rightsum += remvec[i];
        }
        check();
    }
}