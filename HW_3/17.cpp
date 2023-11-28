#include <iostream>
#include <vector>
#include <climits>
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
    ll distance;
    int roottree;
    vector<mypair>child; //first is child, 
}node;
typedef struct graphs{
    int V,E;
    vector<node> vertice;//first is child number, second is distance
    vector<tripair> edge;
}graphs;

void relax(int name, graphs& graph);

void printgraph(graphs& graph);

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> graph.V >> graph.E;
    graph.vertice.resize(graph.V+1);
    graph.edge.resize(graph.E);
    //construct the graph(the vertice is 1-base)
    {
        int u, v, dist;
        for(int i = 0; i < graph.E; i++){
            cin >> u >> v >> dist;
            mypair n;
            tripair tmpedge;
            n.name = v;
            n.dist = dist;
            graph.vertice[u].child.push_back(n);
            n.name = u;
            graph.vertice[v].child.push_back(n);
            tmpedge.first = u;
            tmpedge.second = v;
            tmpedge.dist = dist;
            graph.edge.push_back(tmpedge);
        }
    }
    //initialize the graph
    graph.vertice[1].distance = 0;
    graph.vertice[1].roottree = 1;
    for(int i = 2; i < graph.vertice.size(); i++){
        graph.vertice[1].distance = LLONG_MAX;
    }
    for(int i = 0; i < graph.vertice[1].child.size(); i++){
        int chiv = graph.vertice[1].child[i].name;
        graph.vertice[chiv].distance = graph.vertice[1].child[i].dist;
        graph.vertice[chiv].roottree = chiv;
    }
    //start relax
    for(int i = 0; i < graph.vertice[1].child.size(); i++){
        relax(graph.vertice[1].child[i].name, graph);
    }
    ll ans = LLONG_MAX;
    for(int i = 0; i < graph.E; i++){
        int first = graph.edge[i].first;
        int second = graph.edge[i].second;
        if(graph.vertice[first].roottree != graph.vertice[second].roottree){
            if(first == 1 && second == graph.vertice[graph.edge[i].second].roottree)continue;
            else if(second == 1 && first == graph.vertice[first].roottree)continue;
            else{
                ll chkdist = graph.vertice[graph.edge[i].first].distance + graph.vertice[graph.edge[i].second].distance + graph.edge[i].dist;
                ans = (ans > chkdist)? chkdist: ans;
            }
        }
    }
    printgraph(graph);
    cout << ans;
}
void relax(int name, graphs& graph){
    ll mydist = graph.vertice[name].distance;
    int childname, myroot = graph.vertice[name].roottree;
    for(int i = 0; i < graph.vertice[name].child.size(); i++){
        childname = graph.vertice[name].child[i].name;
        ll chkdist = mydist + graph.vertice[name].child[i].dist;
        if(graph.vertice[childname].distance > mydist + graph.vertice[name].child[i].dist){
            graph.vertice[childname].distance = mydist + graph.vertice[name].child[i].dist;
            graph.vertice[childname].roottree = myroot;
            relax(childname, graph);
        }
    }
}

void printgraph(graphs& graph){
    printf("vertices:\n");
    for(int i = 1; i < graph.V; i++){
        printf(" %d:\n", i);
        printf("    distance: %d \n", graph.vertice[i].distance);

    }
}


// ref:
// 李明奕
// 陳致和
