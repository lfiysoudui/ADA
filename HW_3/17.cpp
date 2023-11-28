#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <queue>
#define ll long long

using namespace std;

typedef struct mypair{
    int name;
    int dist;
}mypair;
typedef struct tripair{
    int first;
    int second;
    int dist;
}tripair;
typedef struct node{
    ll distance = LLONG_MAX;
    int roottree = 0;
    vector<mypair>child; //first is child, 
}node;
typedef struct graphs{
    int V,E;
    vector<node> vertice;//first is child number, second is distance
    vector<tripair> edge;
}graphs;

void input_graph();
void initialize_graph();
// void relax(int name);
void printgraph();

graphs graph;

struct CompareDistance {
    bool operator()(const pair<int,ll> a, const pair<int,ll> b) const {
        return a.second > b.second; // Compare based on distance
    }
};


priority_queue <pair<int,ll>, vector<pair<int,ll> >, CompareDistance> pq;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> graph.V >> graph.E;
    graph.vertice.resize(graph.V+1);
    graph.edge.resize(graph.E);
    //construct the graph(the vertice is 1-base)
    input_graph();
    initialize_graph();
    //start relax
    for(int i = 0; i < graph.vertice[1].child.size(); i++){
        pair<int, ll> tmppair;
        tmppair.first = graph.vertice[1].child[i].name;
        tmppair.second = graph.vertice[graph.vertice[1].child[i].name].distance;
        pq.push(tmppair);
    }
    while(!pq.empty()){
        pair<int, ll> getpair = pq.top();
        int name = getpair.first;
        ll dist = getpair.second;
        pq.pop();
        if(dist != graph.vertice[name].distance) continue;
        ll mydist = graph.vertice[name].distance;
        int childname, myroot = graph.vertice[name].roottree;
        for(int i = 0; i < graph.vertice[name].child.size(); i++){
            childname = graph.vertice[name].child[i].name;
            ll chkdist = mydist + graph.vertice[name].child[i].dist;
            if(graph.vertice[childname].distance > chkdist){
                graph.vertice[childname].distance = chkdist;
                graph.vertice[childname].roottree = myroot;
                pair<int, ll> tmppair;
                tmppair.first = childname;
                tmppair.second = chkdist;
                pq.push(tmppair);
            }
        }
    }
    
    ll ans = LLONG_MAX;
    for(int i = 0; i < graph.E; i++){
        int first = graph.edge[i].first;
        int second = graph.edge[i].second;
        if(graph.vertice[first].roottree != graph.vertice[second].roottree){
            if(first == 1 && second == graph.vertice[graph.edge[i].second].roottree)continue;
            else if(second == 1 && first == graph.vertice[first].roottree)continue;
            else{
                ll chkdist = graph.vertice[first].distance + graph.vertice[second].distance + graph.edge[i].dist;
                ans = (ans > chkdist)? chkdist: ans;
            }
        }
    }
    cout << ans;
}

void input_graph(){
    int u, v, dist;
    for(int i = 0; i < graph.E; i++){
        cin >> u >> v >> dist;
        mypair n;
        n.name = v;
        n.dist = dist;
        graph.vertice[u].child.push_back(n);
        n.name = u;
        graph.vertice[v].child.push_back(n);
        graph.edge[i].first = u;
        graph.edge[i].second = v;
        graph.edge[i].dist = dist;
    }
}
void initialize_graph(){
    graph.vertice[1].distance = 0;
    graph.vertice[1].roottree = 1;
    for(int i = 0; i < graph.vertice[1].child.size(); i++){
        int chiv = graph.vertice[1].child[i].name;
        graph.vertice[chiv].distance = graph.vertice[1].child[i].dist;
        graph.vertice[chiv].roottree = chiv;
    }
}


// ref:
// b11902046 李明奕
// b11902155 陳致和
// b11902011 陳愷欣
