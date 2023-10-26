#include <iostream>
#include <vector>
#define ll long long int

using namespace std;

typedef struct coor{
    ll x;
    ll y;
}coor;

vector<coor> server;
vector<vector<ll>> dp;

void solve();

signed main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll times;
    cin >> times;
    while(times){
        solve();
        times--;
    }
}

void solve(){
    int num;
    cin >> num;
    server.resize(num+1);
    dp.resize(num+1);
    server[0].x = 0;
    server[0].y = 0;
    for(int i = 1; i <= num ; i++){
        cin >> server[i].x >> server[i].y;
    }
    for(int i = 0; i <= num; i++) dp[i].resize(num+1,0);
    dp[1][0] = (server[1].x * server[1].x + server[1].y * server[1].y);
    for(int i = 2; i <= num; i++){
        for(int j = 0; j < i; j++){
            // cerr << "loop(" << i <<","<< j<< ")\n";
            if(i-j == 1){
                dp[i][j] = dp[i-1][0] + (server[i].x * server[i].x + server[i].y * server[i].y);
                ll tmp;
                for(int k = 1; k < j; k++){
                    tmp = dp[i-1][k] + ((server[i].x - server[k].x) * (server[i].x - server[k].x) + (server[i].y - server[k].y) * (server[i].y - server[k].y));
                    dp[i][j] = min(tmp,dp[i][j]);
                }
            }
            else{
                dp[i][j] = dp[i-1][j] + ((server[i].x - server[i-1].x) * (server[i].x - server[i-1].x) + (server[i].y - server[i-1].y) * (server[i].y - server[i-1].y));
            }
            // for(int i = 0; i <= num; i++){
            //     for(int j = 0; j <= num; j++){
            //         cerr << dp[i][j] << " ";
            //     }
            //     cerr << "\n";
            // }
        }
    }
    ll ans = dp[num][0] + ((server[num].x - server[0].x) * (server[num].x - server[0].x) + (server[num].y - server[0].y) * (server[num].y - server[0].y));
    ll tmp = ans;
    // cerr << "tmp0=" << tmp << "\n";
    // cerr << "ans0=" << ans << "\n";
    for(int i = 1; i < num; i++){
        tmp = 0;
        tmp += dp[num][i];
        tmp += ((server[num].x - server[0].x) * (server[num].x - server[0].x) + (server[num].y - server[0].y) * (server[num].y - server[0].y));
        tmp += ((server[i].x - server[0].x) * (server[i].x - server[0].x) + (server[i].y - server[0].y) * (server[i].y - server[0].y));
        // cerr << "tmp" << i << "=" << tmp << "\n";
        ans = min(ans,tmp);
        // cerr << "ans" << i << "=" << ans << "\n";
        
    }
    cout << ans << "\n";

}