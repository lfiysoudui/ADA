#include <iostream>
using namespace std;

int main (){
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
// 12 9 -55 -1 47 76 20 -44  12 74