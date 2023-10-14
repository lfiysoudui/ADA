#include <iostream>
#include <deque>
#include <vector>
#define int long long

using namespace std;



signed main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int turns, length, target;
    deque<int>  deq;
    vector<int> sum;

    cin >> turns;
    for (int k = 0; k < turns; k++){
        cin >> length >> target;
        int ans = length + 1;
        sum.resize(length+1);
        sum[0] = 0ll;
        for( int i = 1; i <= length; i++){
            cin >> sum[i];
            sum[i] += sum[i-1];
        }
        for (int i = 0; i <= length; i++){
            while ( !deq.empty() && sum[i] - sum[deq.front()] >= target){
                ans = min( ans, i - deq.front());
                deq.pop_front();
            }
            while( !deq.empty() && sum[i] <= sum[deq.back()]){
                deq.pop_back();
            }
            deq.push_back(i);
        }
        if(ans > length) cout << -1 << "\n";
        else cout << ans << "\n";
        sum.clear();
        deq.clear();

    }
}


// ref：
// 073 蘇翊軒
// 158 黃昱凱
// 013 黃睿家
// 051 巫俋霆