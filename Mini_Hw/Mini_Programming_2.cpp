#include <iostream>
#include <string.h>
#define int long long int
using namespace std;

signed main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string x, y;
    cin >> x >> y;
    int table[x.size()+1][y.size()+1];
    for(int i = 0; i < x.size() + 1; i++){
        for(int j = 0; j < y.size() + 1; j++){
            if(i == 0) table[i][j] = j;
            else if(j == 0) table[i][j] = i;
            else if(x[i-1] == y[j-1]){
                table[i][j] = table[i-1][j-1];
            }
            else{
                table[i][j] = 1 + min(table[i][j-1],min(table[i-1][j],table[i-1][j-1]));
            }
        }
    }
    // for(int i = 0; i < x.size() + 1; i++){
    //     for(int j = 0; j < y.size() + 1; j++){
    //         cout << table[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    cout << table[x.size()][y.size()] << endl;
}