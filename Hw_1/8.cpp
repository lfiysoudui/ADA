#include <iostream>
#include <vector>
using namespace std;

int main() {
    int turns ;
    cin >> turns;
    for(int k = 0; k < turns; k++){
        int length, target;
        cin >> length >> target;
        vector<int> arr(length);
        for(int i = 0; i < length; i++){
            cin >> arr[i];
        }

        int minlen = length+1;
        int l = 0, sum = 0;
        for(int r = 0; r < length; r++){
            sum += arr[r];
            if(arr[r] > sum) l = r;
            while (sum >= target && r >= l){
                // cout << "[r = " << r << " l = " << l << "]\n";
                minlen = min( minlen, r-l+1 );
                sum -= arr[l];
                l++;
            }
        }
        if(minlen == length+1 ) cout << "-1\n";
        else cout << minlen <<"\n";
    }
}
