#include <iostream>
#include <algorithm>
#include <vector>
#define int long long
#define MAX 1000000

using namespace std;

int arr[MAX] = {0};



signed main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T, N;
    cin >> T;
    for(int i = 0; i < T; i++){
        cin >> N;
        vector<int> arr;
        arr.resize(N);
        for(int j = 0; j < N; j++)cin >> arr[j];
        for(int j = N-1; j > 0; j--) arr[j-1] += arr[j];
        sort(arr.begin(), arr.end());
        int res = 0;
        for(int j = 0; j < N/2; j++) {
            res += arr[j] * -1;
            res += arr[N-1-j];
        }
        cout << res << "\n";
    }
}

// ref:
// 陳思瑋