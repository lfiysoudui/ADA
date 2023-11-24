#include <iostream>
#include <cmath>
#include <algorithm>
#define int long long
#define maxn 10000001

using namespace std;

int dist(int i){
    int tmp = (int)sqrt(i);
    if((tmp-1)*(tmp-1) < i && i <= tmp*tmp) return tmp;
    else return tmp +1;
}

bool status[3][maxn];
int jump[3][maxn];
int  dp[3][maxn];

signed main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < n; j++){
            char tmp;
            cin >> tmp;
            status[i][j] = (tmp == '.')? true : false;
        }
    }
    int dist0 = dist(k), dist1 = dist(k-1), dist2 = dist(k-4);
    // cerr << "1 = " << dist0 << ",2 = "<< dist1 << ",3 = "<< dist2 << "\n";
    for(int j = 0; j < n; j++){
        if(!status[0][j]){
            dp[0][j] = (j > 0)? dp[0][j-1] : 0;
        }
        else{
            int d1 = (j >= dist0)? dp[0][j-dist0] + 1 : 1;
            int d2 = (j >= dist1)? dp[1][j-dist1] + 1 : 1;
            int d3 = (j >= dist2)? dp[2][j-dist2] + 1 : 1;
            int d3a = (j >= dist2-1)? dp[2][j-dist2-1] + 1 : 1;
            dp[0][j] = max( d1, d2 );
            if(k == 5) {
                dp[0][j] = max({ dp[0][j], dp[0][j-1], d3a });
                if((jump[2][j-dist2] == 0) && dp[0][j] < d3){
                    jump[0][j] = 1;
                    dp[0][j] = d3;
                }
            }
            else dp[0][j] = max( dp[0][j], d3 );
        }
        if(!status[1][j]){
            dp[1][j] = (j > 0)? dp[1][j-1] : 0;
        }
        else{
            int d1 = (j >= dist1)? dp[0][j-dist1] + 1 : 1;
            int d2 = (j >= dist0)? dp[1][j-dist0] + 1 : 1;
            int d3 = (j >= dist1)? dp[2][j-dist1] + 1 : 1;
            dp[1][j] = max({ d1, d2, d3 });
        }
        if(!status[2][j]){
            dp[2][j] = (j > 0)? dp[2][j-1] : 0;
        }
        else{
            int d1 = (j >= dist2)? dp[0][j-dist2] + 1 : 1;
            int d2 = (j >= dist1)? dp[1][j-dist1] + 1 : 1;
            int d3 = (j >= dist0)? dp[2][j-dist0] + 1 : 1;
            int d1a = (j >= dist2-1)? dp[0][j-dist2-1] + 1 : 1;
            dp[2][j] = max( d2, d3 );
            if(k == 5) {
                dp[2][j] = max({ dp[2][j], dp[2][j-1], d1a });
                if((jump[0][j-dist2] == 0) && dp[2][j] < d1){
                    jump[2][j] = 1;
                    dp[2][j] = d1;
                }
            }
            else dp[2][j] = max( dp[2][j], d1 );
        }
    }
    cout << max({dp[0][n-1],dp[1][n-1],dp[2][n-1]}) << "\n";
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < n; j++){
            cerr << dp[i][j] << " ";
        }
        cerr << "\n";
    }
    // cerr << "\n";
    // for(int i = 0; i < 3; i++){
    //     for(int j = 0; j < n; j++){
    //         cerr << jump[i][j] << " ";
    //     }
    //     cerr << "\n";
    // }
}