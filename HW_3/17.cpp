#include <iostream>
#include <vector>
using namespace std;

#define ll long long
typedef struct pairs{
    ll name;
    ll dist;
}pairs;
typedef struct childs{
    vector< pairs > child;//first is child number, second is distance
}childs;

ll tmpn;

ll dfs(ll num, vector<childs> &list, vector<bool> &check, ll parent){
    // for(int j = 0; j < tmpn; j++){
    //     cerr << check[j] << " ";
    // }
    // cerr << ":"<< num << "\n";
    if(num == 0) return 0;
    check[num] = true;
    ll mindist = -1;
    for (int i = 0; i < list[num].child.size(); i++) {
        if (!check[list[num].child[i].name] && list[num].child[i].name != parent) {
            if(mindist == -1)
                mindist = dfs(list[num].child[i].name, list, check, num)+list[num].child[i].dist;
            else
                mindist = min(mindist, dfs(list[num].child[i].name, list, check, num)+list[num].child[i].dist);
            // cerr << num << ":" << i << " " << mindist << "\n";
        }
    }
    check[num] = false;
    return mindist; 
}

void push(vector< pairs > lists){
    
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    vector<bool> check;
    vector<childs> vertice;
    cin >> n >> m;
    tmpn = n;
    vertice.resize(n);
    {
        int u, v, dist;
        pairs up,vp;
        for(int i = 0; i < m; i++){
            cin >> u >> v >> dist;
            up.name = v-1;
            up.dist = dist;
            vp.name = u-1;
            vp.dist = dist;
            vertice[u-1].child.push_back(up);
            vertice[v-1].child.push_back(vp);
        }
    }
    // for(int i = 0; i < n; i++){
    //     cerr << i <<" :\n";
    //     for(int j = 0; j < vertice[i].child.size(); j++){
    //         cerr << " " << vertice[i].child[j].name << " " << vertice[i].child[j].dist << "\n";
    //     }
    // }
    // start dfs
    check.resize(n, false);
    ll ans = -1;
    for (int i = 0; i < vertice[0].child.size(); i++) {
        // cerr << "now at: " << vertice[0].child[i].name << "\n";
        ll tmp = dfs(vertice[0].child[i].name, vertice, check, 0);
        // cerr << vertice[0].child[i].name << " (" << ans << " = " << tmp << " + " << vertice[0].child[i].dist<< "\n";
        if(ans == -1)
            ans = tmp + vertice[0].child[i].dist;
        else
            ans = min(ans, tmp + vertice[0].child[i].dist);
        // cerr << vertice[0].child[i].name << " => " << ans << "\n";
    }
    cout << ans << "\n";
}

//ref: