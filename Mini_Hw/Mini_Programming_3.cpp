#include <iostream>
using namespace std;

typedef struct node{
    int freq;
    int data;
    node *L,*R;
    node(int d, int f) : data(d), freq(f), L(nullptr), R(nullptr) {}
}node;

struct compmin{
    bool operator()(const node *a, const node *b) const{
        return a->freq > b->freq;
    }
};

void findHuffmanCodes(node* root, string code = "", string res[] = nullptr) {
    if (root) {
        if (!root->L && !root->R) res[root->data] = code;

        findHuffmanCodes(root->L, code + "0", res);
        findHuffmanCodes(root->R, code + "1", res);
    }
}

int main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    int freq[n];
    for(int i = 0; i < n; i++){
        cin >> freq[i];
    }
    if(n == 1){
        cout << 0 << '\n';
        return 0;
    }
    priority_queue <node*,vector<node*>, compmin> pq;
    for(int i = 0; i < n; i++){
        pq.push(new node(i, freq[i]));
    }
    while (pq.size() > 1) {
        node* left = pq.top();
        pq.pop();
        node* right = pq.top();
        pq.pop();

        node* combined = new node(-1, left->freq + right->freq);
        combined->L = left;
        combined->R = right;

        pq.push(combined);
    }
    node *root = pq.top();
    string code[n];
    findHuffmanCodes(root, "",code);
    for(string i:code){
        cout << i << "\n";
    }
}