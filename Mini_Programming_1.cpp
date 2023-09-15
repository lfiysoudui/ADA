#include <iostream>
#define int long long int
using namespace std;


signed main (){
    int nums;
    cin >> nums;
    int tmp;
    if(nums == 0){
        cout << 0;
        return 0;
    }
    cin >> tmp;
    int maxSum = tmp, Sum = tmp;
    for(int i = 1; i < nums; i++){
        cin >> tmp;
        Sum = max(tmp , Sum+tmp);
        maxSum = max(maxSum , Sum);
        // cout << "[" << i << "] maxSum = " << maxSum << " Sum = " << Sum << "\n";
    }
    cout << maxSum;
}