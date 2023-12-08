#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#define ll long long int

using namespace std;

class DisjointSet {
public:
    DisjointSet(int size) : parent(size), rank(size, 0) {
        // Initialize each element as a separate set
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    // Find the representative (root) of the set to which the element belongs
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }

    // Union two sets based on their ranks (to keep the tree balanced)
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootX] = rootY;
                rank[rootY]++;
            }
        }
        // for(int i = 0; i < parent.size(); i++)
        //     cerr << parent[i] << " ";
        // cerr << "\n";
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
};


typedef struct Edge 
{
    ll weight;
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
    set<Edge> edge;
} Graph;

int main ()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    Graph graph;
    cin >> graph.v >> graph.e;
    DisjointSet vertice_set(graph.v);
    {
        Edge tmpedge;
        for(int i = 0; i < graph.e; i++)
        {
            cin >> tmpedge.u >> tmpedge.v >> tmpedge.weight;
            graph.edge.insert(tmpedge);
        }
    }
    ll ct = 0, unions = graph.v;
    set<Edge> :: iterator lt = graph.edge.begin();
    while(unions > 1 )
    {
        if(lt == graph.edge.end()) 
        {
            // cerr << lt->u << " " << lt->v << " " << lt->weight << endl;
            cerr << "didn't found" << "\n";
            break;
        }
        if(vertice_set.find(lt->u) != vertice_set.find(lt->v))
        {
            vertice_set.unionSets(lt->u, lt->v);
            ct += lt->weight;
            // cerr << lt->u << " " << lt->v << " " << lt->weight << endl;
            unions--;
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

