#include "iostream"
#include "vector"
#define int long long

using namespace std;

int findmin(int a, int b, int c){
    int tmp = a;
    if ( b < tmp ) tmp = b;
    if ( c < tmp ) tmp = c; 
    return tmp;
}

int findMinSub (int l, int r, vector<int>& head){
    if( l >= r){
        int tmp = 1 + head[r] * head[r];
        // cout << "( " << l << " , " << r << " )[" << tmp << "]\n";
        return tmp;
    }
    else{
        int minSub = head[(l+r)/2] * head[(l+r)/2] + 1, tmpsum = head[(l+r)/2], Lreminder = (l+r)/2, Rreminder = (l+r)/2;
        int tmp;
        for(int i = (l+r)/2-1; i >= l ; i--){
            tmpsum += head[i];
            tmp = tmpsum * tmpsum + (Rreminder - i + 1)*(Rreminder - i + 1);
            if( llabs(minSub) > llabs(tmp) ) {
                minSub = tmp;
                Lreminder = i;
            }
        }
        for(int i = (l+r)/2+1; i <=r ; i++){
            tmpsum += head[i];
            tmp = tmpsum * tmpsum + (i - Lreminder + 1)*(i - Lreminder + 1);
            if( llabs(minSub) > llabs(tmp) ) {
                minSub = tmp;
                Rreminder = i;
            }
        }
        tmp = findmin( findMinSub(l,(l+r)/2,head), findMinSub((l+r)/2+1,r,head), minSub);
        // cout << "( " << l << " , " << r << " )[" << tmp << "]\n";
        return tmp;
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int length;
    vector<int> sum;

    cin >> length;
    sum.resize(length + 1);
    for(int i = 0; i < length; i++){
        cin >> sum[i];
    }
    cout << findMinSub(0,length-1,sum);
}