#include "iostream"
#include "vector"

#define int long long

using namespace std;

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int N, mod, day;//mod = m,Day = k
    cin >> N >> mod >> day;
    int** initArr = (int**) malloc((N+1)* sizeof(int*));// the array of a
    int* cArr = (int*) malloc((day)* sizeof(int));
    int** subSum = (int**) malloc((day+1)* sizeof(int*));

    initArr[0] = (int*) malloc((mod)* sizeof(int));
    for(int i = 0; i < mod; i++) initArr[0][i] = 0;
    for(int i = 1; i < N+1; i++){
        int tmp;
        initArr[i] = (int*) malloc((mod)* sizeof(int));
        for(int j = 0; j < mod; j++) initArr[i][j] = initArr[i-1][j];
        cin >> tmp;
        initArr[i][tmp]++;
    }
    for(int i = 0; i < day; i++) cin >> cArr[i];
    subSum[day] = (int*) malloc((mod)* sizeof(int));
    subSum[day][0] = 1;
    for(int i = 1; i < mod; i++) subSum[day][i] = 0;
    for(int i = day-1; i >= 0; i--){
        subSum[i] = (int*) malloc((mod)* sizeof(int));
        for(int j = 0; j < mod; j++) subSum[i][j] = subSum[i+1][j];
        for(int j = 0; j < mod; j++) {
            // printf("%lld day,%lld+%lld from %lld\n", i, j, subSum[i+1][(j-cArr[i]+mod)%mod], (j-cArr[i]+mod)%mod);
            subSum[i][j] += subSum[i+1][(j-cArr[i]+mod)%mod];
        }
    }
    for(int i = 0; i <= day; i++) {
        for(int j = 0; j < mod; j++) printf("%lld ",subSum[i][j]);
        printf("\n");
    }
}