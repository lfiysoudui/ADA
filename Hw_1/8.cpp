#include <iostream>
#define int long long

using namespace std;



signed main() {
    int turns ;
    cin >> turns;
    for(int k = 0; k < turns; k++){
        int length, target;
        cin >> length >> target;
        int arr[length];
        for(int i = 0; i < length; i++){
            cin >> arr[i];
        }

        int minlen = length+1;
        int l = 0, sum = 0;
        for(int r = 0; r < length; r++){
            sum += arr[r];
            if(sum<0){
                r++;
                l = r;
                sum = arr[r];
            }
            while (sum >= target && r >= l){
                // cout << "[r = " << r << " l = " << l << "]\n";
                minlen = min( minlen, r-l+1 );
                sum -= arr[l];
                l++;
                while (l>0) l--;
                
            }
        }
        if(minlen == length+1 ) cout << "-1\n";
        else cout << minlen <<"\n";
    }
}
