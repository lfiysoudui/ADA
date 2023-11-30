#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define int long long

typedef struct vertice_data {
    int cursor;
    int d, f; // discovery/ finish
    vector<int> child;
} vertice_data;

int dfs(int num, vector<vertice_data> &list, vector<bool> &check, int round, vector<int> &current_scc) {
    check[num] = true;
    current_scc.push_back(num);
    list[num].d = round;
    for (int i = 0; i < list[num].child.size(); i++) {
        if (!check[list[num].child[i]]) {
            round++;
            round = dfs(list[num].child[i], list, check, round, current_scc);
        }
    }
    round++;
    list[num].f = round;
    return round;
}

bool compare(pair<int, int> a, pair<int, int> b) {
    return a.first > b.first;
}

signed main() {
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
            rd = dfs(i, vertice, check, rd, tmp);
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
    vector<vector<int> > scc_components;

    for (int i = 0; i < n; i++) {
        int u = seq[i].second;
        if (!check[u]) {
            vector<int> current_scc;
            int ord = rd;
            rd = dfs(u, revvertice, check, rd, current_scc);
            if (rd - ord > 1) {
                scc_components.push_back(current_scc);
            }
            rd++;
        }
    }

    // Print SCCs
    for (int i = 0; i < scc_components.size(); i++) {
        for (int j = 0; j < scc_components[i].size(); j++) {
            cout << scc_components[i][j]+1 << " ";
        }
        cout << "\n";
    }
}
