#include <iostream>
#include <climits>
#include <algorithm>
#include <queue>
#include <set>
#define ll long long

using namespace std;
//struct section
typedef struct Vertices {
    ll distance;
    vector<int> child;
    Vertices() : distance(LLONG_MAX) {}
} Vertices;

typedef struct Graphs {
    int s, t;
    int V, E;
    vector<Vertices> vertice;
    vector<pair<int, int> > edge;//first to second
    vector<ll> reclength;
} Graphs;

struct CompDist {
    bool operator()(const pair<int,ll> a, const pair<int,ll> b) const {
        return a.second > b.second; // Compare based on distance
    }
};

struct CompDescend {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

//public section
Graphs graph;
Graphs rev_graph;

//define function section
void input_graph();
void relax(Graphs &input_graph);

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> graph.V >> graph.E >> graph.s >> graph.t;
    rev_graph.V = graph.V;
    rev_graph.E = rev_graph.E;
    rev_graph.s = graph.t;
    rev_graph.t = graph.s;
    input_graph();
    //initialize head
    graph.vertice[graph.s].distance = 0;
    rev_graph.vertice[rev_graph.s].distance = 0;

    relax(graph);
    relax(rev_graph);
    sort(graph.reclength.begin(), graph.reclength.end());
    sort(rev_graph.reclength.begin(), rev_graph.reclength.end(), greater<ll>());
    ll ans = 0;
    int cursor = 1;
    ll shortest = graph.vertice[graph.t].distance;
    while(rev_graph.reclength[cursor] == LLONG_MAX) cursor++;
    // cout << "start ( " << shortest << "," << rev_graph.reclength[cursor]<< ")\n";
    for(int i = 0; i < graph.V; i++)
    {
        ll dist = graph.reclength[i];
        if(dist == LLONG_MAX) cursor = graph.V;
        else while(shortest <= dist + rev_graph.reclength[cursor] + 1&& cursor < graph.V) cursor++;
        // cout << "when " << i << "cursor is at " << cursor << " with ( " << dist << "," << rev_graph.reclength[cursor] << ")\n"; //! debug
        ans += cursor;
    }
    // cout << "\n"; //! debug
    // cout << ans << "\n"; //! debug
    ans -= graph.E;
    cout << ans << "\n";
    //!debug section
    // cout << "\nGraph\n";
    // // for(int i = 1; i <= graph.V; i++)
    // // {
    // //     cout << i << " : " <<  graph.vertice[i].distance << "\n";
    // // }
    // for(int j = 0; j < graph.V; j++)
    // {
    //     cout << "  " << graph.reclength[j];
    // }
    // cout << "\n";
    // cout << "\nRev_Graph\n";
    // // for(int i = 1; i <= rev_graph.V; i++)
    // // {
    // //     cout << i << " : " <<  rev_graph.vertice[i].distance << "\n";
    //     for(int j = 0; j < rev_graph.V; j++)
    //     {
    //         cout << "  " << rev_graph.reclength[j];
    //     }
    //     cout << "\n";
    // // }
}

//function section

void input_graph()
{
    int u, v;
    pair<int, int > tmppair;
    graph.vertice.resize(graph.V+1);
    rev_graph.vertice.resize(rev_graph.V+1);
    for(int i = 0; i < graph.E; i++)
    {
        cin >> u >> v;
        graph.vertice[u].child.push_back(v);
        rev_graph.vertice[v].child.push_back(u);
        tmppair = make_pair(u, v);
        graph.edge.push_back(tmppair);
        tmppair = make_pair(v, u);
        rev_graph.edge.push_back(tmppair);
    }
}

void relax(Graphs &input_graph)
{
    priority_queue <pair<int,ll>, vector<pair<int,ll> >, CompDist> pq;
    pair<int, ll> tmppair;
    tmppair.first = input_graph.s;
    tmppair.second = input_graph.vertice[input_graph.s].distance;
    pq.push(tmppair);
    while(!pq.empty())
    {
        tmppair = pq.top();
        int name = tmppair.first;
        ll dist = tmppair.second;
        pq.pop();
        if(dist != input_graph.vertice[name].distance) continue;
        ll mydist = input_graph.vertice[name].distance;
        int childname;
        for(int i = 0; i < input_graph.vertice[name].child.size(); i++)
        {
            childname = input_graph.vertice[name].child[i];
            ll chkdist = mydist + 1;
            if(input_graph.vertice[childname].distance > chkdist)
            {
                input_graph.vertice[childname].distance = chkdist;
                tmppair.first = childname;
                tmppair.second = chkdist;
                pq.push(tmppair);
            }
        }
    }
    for(int i = 1; i <= input_graph.V; i++){
        input_graph.reclength.push_back(input_graph.vertice[i].distance);}
}

