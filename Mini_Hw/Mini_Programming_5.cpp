#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#define ll long long int

using namespace std;

typedef struct Edge 
{
    int weight;
    int u;
    int v;
} Edge;

inline bool operator<(const Edge& lhs, const Edge& rhs)
{
  return lhs.weight <= rhs.weight;
}

typedef struct Graph 
{
    int v, e;
    vector<bool> vertice;
    set<Edge> edge;
} Graph;

int main ()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    Graph graph;
    cin >> graph.v >> graph.e;
    graph.vertice.resize(graph.v, false);
    {
        Edge tmpedge;
        for(int i = 0; i < graph.e; i++)
        {
            cin >> tmpedge.u >> tmpedge.v >> tmpedge.weight;
            graph.edge.insert(tmpedge);
        }
    }
    int ct = 0;
    auto lt = graph.edge.begin();
    while(ct < graph.v)
    {
        if(lt == graph.edge.end()) 
        {
            cerr << "didn't found" << "\n";
            break;
        }
        if(!(graph.vertice[lt->u] == true && graph.vertice[lt->v] == true))
        {
            ct += lt->weight;
            cerr << lt->u << " " << lt->v << " " << lt->weight << endl;
        }
        lt++;
    }
    cout << ct << "\n";
    // {
    //     for(auto const& bi : graph.edge){
    //         cerr << bi.u << " " << bi.v << " " << bi.weight << endl;
    //     }
    // }
}

