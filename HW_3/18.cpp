#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;
#define int long long

typedef struct vertice_data {
    int cursor;
    int d, f; // discovery/ finish
    int weight;
    int weight_sum;
    vector<int> child;
    set<int> schild;
} vertice_data;


int dfs(int num, vector<vertice_data> &list, vector<bool> &check, int round, vector<int> &current_scc, vector<int> &reclist) {
    check[num] = true;
    current_scc.push_back(num);
    list[num].d = round;
    for (int i = 0; i < list[num].child.size(); i++) {
        if (!check[list[num].child[i]]) {
            round++;
            round = dfs(list[num].child[i], list, check, round, current_scc, reclist);
        }
    }
    round++;
    list[num].f = round;
    reclist.push_back(num);
    return round;
}
void topple(int num, vector<vertice_data> &list, vector<bool> &check, vector<int> &reclist){
    check[num] = true;
    auto lt = list[num].schild.begin();
    for (int i = 0; i < list[num].schild.size(); i++) {
        if (!check[*lt]) {
            topple(*lt, list, check, reclist);
        }
        lt++;
    }
    reclist.push_back(num);
}
void topplesp(int num, vector<vertice_data> &list, vector<bool> &check, vector<int> &reclist){
    check[num] = true;
    for (int i = 0; i < list[num].child.size(); i++) {
        if (!check[list[num].child[i]]) {
            topple(list[num].child[i], list, check, reclist);
        }
    }
    reclist.push_back(num);
}

bool compare(pair<int, int> a, pair<int, int> b) {return a.first > b.first;}

vector<bool> check(1000100);
vector<vertice_data> vertice;
vector<vertice_data> revvertice;
vector<vector<int> > scc_components;
vector<int> SCCgrp(1000100);
vector<vector<bool> > doublecheck;
struct CompareDistance {
    bool operator()(const pair<int,int> a, const pair<int,int> b) const {
        return a.second > b.second; // Compare based on distance
    }
};

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    check.resize(0);
    check.resize(n, false);
    vertice.resize(n);
    revvertice.resize(n);
    {
        int u, v;
        for (int i = 0; i < m; i++) {
            cin >> u >> v;
            vertice[u - 1].child.push_back(v - 1);
            revvertice[v - 1].child.push_back(u - 1);
        }
    }
    //first dfs
    int rd = 1;
    for (int i = 0; i < n; i++) {
        if (!check[i]) {
            vector<int> tmp;
            vector<int> tmp2;
            rd = dfs(i, vertice, check, rd, tmp, tmp2);
            rd++;
        }
    }

    //sort by.f
    vector<pair<int, int> > seq(n);
    for (int i = 0; i < n; i++) {
        seq[i].first = vertice[i].f;
        seq[i].second = i;
    }
    sort(seq.begin(), seq.end(), compare);

    //rev dfs
    check.resize(0);
    check.resize(n, false);
    vector<int> reclist;
    for (int i = 0; i < n; i++) {
        int u = seq[i].second;
        if (!check[u]) {
            vector<int> current_scc;
            int ord = rd;
            rd = dfs(u, revvertice, check, rd, current_scc, reclist);
            scc_components.push_back(current_scc);
            rd++;
        }
    }
    int new_n = scc_components.size();
    vector<vertice_data> new_graph(new_n);
    

    if(scc_components.size()!= 0){
    SCCgrp.resize(n);
    for(int i = 0; i < new_n; i++){
        for(int j = 0; j < scc_components[i].size(); j++){
            SCCgrp[scc_components[i][j]] = i;
        }
    }
    for(int i = 0; i < new_n; i++){
        new_graph[i].weight = scc_components[i].size();
        new_graph[i].weight_sum = scc_components[i].size();
    }
    for(int j = 0; j < n; j++){
        for(int k = 0; k < vertice[j].child.size(); k++){
            // cout << "("<<j <<","<<k<<")\n";
            int tmp = SCCgrp[vertice[j].child[k]];
            if(SCCgrp[j] == tmp) continue;
            else if(new_graph[SCCgrp[j]].schild.find(tmp) == new_graph[SCCgrp[j]].schild.end()){
                new_graph[SCCgrp[j]].schild.insert(tmp);
            }
        }
    }

    // start calculate weight
    // check.resize(0);
    // check.resize(new_n, false);
    // reclist.resize(0);
    // for (int i = 0; i < new_n; i++){
    //     if (!check[i]) {
    //         topple(i, new_graph, check, reclist);
    //     }
    // }
    int ans = 0;
    int cursor = -1;
    for(int i = 0; i <reclist.size(); i++){
        if(cursor == SCCgrp[reclist[i]]) continue;
        cursor = SCCgrp[reclist[i]];
        ans = (ans > new_graph[cursor].weight_sum)? ans: new_graph[cursor].weight_sum;
        auto lt = new_graph[cursor].schild.begin();
        for(int j = 0; j < new_graph[cursor].schild.size(); j++){
            int tmp = *lt;
            if(new_graph[tmp].weight_sum < new_graph[cursor].weight_sum + new_graph[tmp].weight)
                new_graph[tmp].weight_sum = new_graph[cursor].weight_sum + new_graph[tmp].weight;
            lt++;
        }
    }
    cout << ans << "\n";
    }
    else{
        for(int i = 0; i < new_n; i++){
            vertice[i].weight = 1;
            vertice[i].weight_sum = 1;
        }
        
        int ans = 0;
        for(int i = reclist.size()-1; i >= 0; i--){
            int cursor = reclist[i];
            ans = (ans > vertice[cursor].weight_sum)? ans: vertice[cursor].weight_sum;
            for(int j = 0; j < vertice[cursor].child.size(); j++){
                int tmp = vertice[cursor].child[j];
                if(new_graph[tmp].weight_sum < new_graph[cursor].weight_sum + new_graph[tmp].weight)
                    new_graph[tmp].weight_sum = new_graph[cursor].weight_sum + new_graph[tmp].weight;
            }
        }
        cout << ans << "\n";
    }
}
// ref:
// b11902084 張閔堯
// b11902132 官毓韋
// b11902158 黃昱凱