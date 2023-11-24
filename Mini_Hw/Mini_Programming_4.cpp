#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define int long long

typedef struct vertice_data{
    int cursor;
    int d,f; // discovery/ finish
    vector<int> child;
}vertice_data;



int dfs(int num, vector<vertice_data> &list, vector<bool> &check, int round){
    check[num] = true;
    list[num].d = round;
    for (int i = 0; i < list[num].child.size(); i++) {
        if (!check[list[num].child[i]]) {
            round++;
            round = dfs(list[num].child[i], list, check, round);
        }
    }
    round++;
    list[num].f = round;
    return round; 
}

bool compare(pair<int,int> a, pair<int,int> b) {
    return a.first > b.first;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    vector<bool> check;
    vector<vertice_data> vertice;
    vector<vertice_data> revvertice;

    cin >> n >> m;
    check.resize(n, false);
    vertice.resize(n);
    revvertice.resize(n);
    {
        int u,v;
        for(int i = 0; i < m; i++){
            cin >> u >> v;
            vertice[u-1].child.push_back(v-1);
            revvertice[v-1].child.push_back(u-1);
        }
    }
    //first dfs
    int rd = 1;
    for (int i = 0; i < n; i++) {
        if (!check[i]) {
            rd = dfs(i, vertice,check, rd);
            rd++;
        }
    }
    //sort by.f
    pair<int,int> *seq=(pair<int,int>*)malloc(n*sizeof(pair<int,int>));
    for(int i = 0; i < n; i++){
        seq[i].first = vertice[i].f;
        seq[i].second = i;
    }
    sort(seq, seq+n, compare);

    //rev dfs
    check.resize(0);
    check.resize(n, false);
    rd = 1;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int u = seq[i].second;
        // cout << "in " << u << "\n";
        if (!check[u]) {
            int ord = rd;
            rd = dfs(u, revvertice, check, rd);
            // cout << ord  << ":" << rd << "\n";
            if(rd-ord > 1){
                sum+= ((rd-ord+1)/2) * ((rd-ord+1)/2 - 1) / 2;
            }
            rd++;
            // cout << sum << "\n";
        }
        // for(int j = 0; j < n; j++){
        //     cout << check[i] << " ";
        // }
        // cout << "\n";
    }
    cout << sum << "\n";
    // for (int i = 0; i < n; i++) {
    //     cerr << i << ".d = " << revvertice[i].d << " .f = " << revvertice[i].f << "\n";
    // }
    // for (int i = 0; i < n; i++) {
    //     cerr << i << " => " << seq[i].second << "\n";
    // }
    // check.resize(n, false);
}