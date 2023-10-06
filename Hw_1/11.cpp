#include "iostream"
#include "vector"
#include "algorithm"
#include "utility"
#include "math.h"
#include "climits"
#define int long long

using namespace std;


int findMinSub (int l, int r, vector<int>& sum){
    if(r - l == 1){
        int tmp = (sum[r] - sum[l]) * (sum[r] - sum[l]) + 1;
        // cout << "1( " << l << ", " << r<< ") " << tmp << "\n";
        return tmp;
    }
    else if (r - l == 2){
        int tmp = (sum[r] - sum[l+1]) * (sum[r] - sum[l+1]) + 1;
        int tmp1 = (sum[r-1] - sum[l]) * (sum[r-1] - sum[l]) + 1;
        int tmp2 = (sum[r] - sum[l]) * (sum[r] - sum[l]) + 4;
        // cout << "1( " << l << ", " << r<< ") max\n";
        tmp = min(tmp, tmp1);
        tmp = min(tmp, tmp2);
        return tmp;
    }
    else if (r - l < 1){
        cout << "fail";
        return 0;
    }

    else{
        int rmin = findMinSub((l+r)/2+1, r, sum);
        int lmin = findMinSub(l, (l+r)/2, sum);
        if(rmin < lmin) swap( rmin, lmin);
        int minVal = lmin;
        int lcur = (l+r)/2 - (int)sqrt(minVal) - 1, rcur = (l+r)/2 + (int)sqrt(minVal) + 1;
        if(lcur < l) lcur = l;
        if(rcur > r) rcur = r;
        vector<pair<int,int>> sumsort;
        for(int i = 0; i < rcur - lcur + 1; i++) sumsort.push_back( make_pair( sum[lcur + i],i));
        sort(sumsort.begin(),sumsort.end());
        // cout << "3( " << l << ", " << r<< ") bef: " << minVal << "\n";
        for(int i = 0; i < rcur - lcur + 1; i++){
            for(int j = 1; j < 8 && j+i < sumsort.size(); j++){
                int tmp = (sumsort[i+j].first - sumsort[i].first) * (sumsort[i+j].first - sumsort[i].first) + (sumsort[i+j].second - sumsort[i].second) * (sumsort[i+j].second - sumsort[i].second);
                if(tmp < minVal ) minVal = tmp;
                // cout << "3( " << l << ", " << r<< ") in :" << sumsort[i+j]<<"(" <<i+j<< "), " << sumsort[i] << "(" <<i<< ")\n";
            }
        }
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