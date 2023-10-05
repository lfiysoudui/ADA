#include "iostream"
#include "vector"
#define int long long

using namespace std;


int findMinSub (int l, int r, vector<int>& sum){
    if(r - l == 1){
        int tmp = (sum[r] - sum[l]) * (sum[r] - sum[l]) + 1;
        // cout << "1( " << l << ", " << r<< ") " << tmp << "\n";
        return tmp;
    }
    else if (r - l < 1){
        int tmp = (sum.front() - sum.back()) * (sum.front() - sum.back()) + size(sum) * size(sum);
        // cout << "2( " << l << ", " << r<< ") " << tmp << "\n";
        return tmp;
    }
    else{
        int rmin = findMinSub((l+r)/2+1, r, sum);
        int lmin = findMinSub(l, (l+r)/2, sum);
        if(rmin < lmin) swap( rmin, lmin);
        int minVal = lmin;
        int lcur = (l+r)/2 - minVal, rcur = (l+r)/2 + minVal;
        if(lcur < l) lcur = l;
        if(rcur > r) rcur = r;
        for(int i = lcur; i < rcur; i++){
            for(int j = 1; j < 8 && j+i <= rcur; j++){
                int tmp = (sum[i+j] - sum[i]) * (sum[i+j] - sum[i]) + j*j;
                if(tmp < minVal ) minVal = tmp;
            }
        }
        // cout << "3( " << l << ", " << r<< ") " << minVal << "\n";
        return minVal;
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int length;
    vector<int> sum;

    cin >> length;
    sum.resize(length + 1);
    sum[0] = 0;
    for(int i = 1; i <= length; i++){
        cin >> sum[i];
        sum[i] += sum[i-1];
    }
    cout << findMinSub(0,length,sum);
}