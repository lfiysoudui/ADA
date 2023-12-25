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
ll *remvec;

//functions
void insert_num(ll);
void remove_num(ll);
void merge(ll);
void check();

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    ll inbuf;
    char command[5];
    scanf("%lld", &n);
    remvec = (ll*)malloc(n+1 * sizeof(ll));
    for(ll i = 0; i < n; i++)
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
            // cerr << "wiwi ";
            cout << rightsum - leftsum + *lefttree.rbegin() * ((long long)lefttree.size() - (long long)righttree.size()) << "\n";
        }
        else if(!strcmp(command,"kiki"))
        {
            scanf("%lld", &inbuf);
            merge(inbuf);
        }
        else cerr << "wrong command\n";

        // cerr << "seq= ";
        // for (auto it = lefttree.begin(); it != lefttree.end(); it++)
        //     cerr << *it << " ";
        // cerr << "| ";
        // for (auto it = righttree.begin(); it != righttree.end(); it++)
        //     cerr << *it << " ";
        // cerr << "(" << leftsum << ", " << rightsum << ")\n";
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
        auto it = righttree.begin();
        ll tmpmv = *it;
        lefttree.insert(tmpmv);
        leftsum += tmpmv;
        rightsum -= tmpmv;
        righttree.erase(it);
    }
    while (lefttree.size() > righttree.size()+1)
    {
        auto it = lefttree.rbegin();
        ll tmpmv = *it;
        righttree.insert(tmpmv);
        rightsum += tmpmv;
        leftsum -= tmpmv;
        lefttree.erase(--it.base()); //?
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
    for(ll i = 0; i <= k; i++) remvec[i] = 0; 
    if(k >= lefttree.size()){
        ll tomodify = lefttree.size() + righttree.size() - k;
        // cerr << "tomodify = " << tomodify << "\n";
        for(ll i = 0; i < tomodify; i++)
        {
            auto it = lefttree.begin();
            remvec[i] += *it;
            leftsum -= *it;
            lefttree.erase(it);
        }
        for(ll i = tomodify; i > 0; i--)
        {
            auto itr = righttree.rbegin();
            remvec[i-1] += *itr;
            rightsum -= *itr;
            righttree.erase(--itr.base());
        }
        for(ll i = 0; i < tomodify; i++){
            rightsum += remvec[i];
            righttree.insert(remvec[i]);
        }
        check();
        return;
    }
    else
    {
        ll ct = 0;

    cerr << "ok\n";
        for(auto it = lefttree.begin(); it != lefttree.end(); it++)
        {
            // cerr << "remvec[" << ct << "]+=" << *it<< "\n";
            cerr << "ct="<< ct <<"k= "<< k <<"\n";
            remvec[ct%k] += *it;
            ct++;
            cerr << "ct="<< ct <<"k= "<< k <<"\n";
        }

        for(auto it = righttree.begin(); it != righttree.end(); it++)
        {
            // cerr << "remvec[" << ct << "]+=" << *it<< "\n";
            remvec[ct%k] += *it;
            ct++;
        }
        // for(ll i:remvec) cerr << i << " ";
        // cerr << "\n";
        lefttree.clear();
        righttree.clear();
        leftsum = 0;
        rightsum = 0;
        for(ll i = 0; i < k; i++)
        {
            lefttree.insert(remvec[i]);
            leftsum += remvec[i];
        }
        check();
    }
}