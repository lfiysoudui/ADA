#include "iostream"
#include "vector"

#define int long long

using namespace std;

int powtwo[30];
int** initArr;
int* cArr;
int** subSum;
int N, mod, dayk; //mod = m,Dayk = k

int findsum(int lcur, int l, int brec, int depth){
    
    int sum = 0;
    if( depth == dayk){//sum up
        printf("(%lld, %lld, %lld, %lld,0)\n", lcur, l, depth, powtwo[depth+1]);
        for(int i = 0; i < mod; i++)
            sum += (i+brec) % mod * initArr[l%N+1][i];
    }
    else if(l-lcur+1 == powtwo[depth]){//sum upleft
        printf("(%lld, %lld, %lld, %lld,1)\n", lcur, l, depth, powtwo[depth+1]);
        for(int i = 0; i < mod; i++)
            sum += (i+brec) % mod * subSum[depth+1][i];
    }
    else if(l-lcur+1 > powtwo[depth+1]){//r
        printf("(%lld, %lld, %lld, %lld,r)\n", lcur, l, depth, powtwo[depth+1]);
        sum = findsum(0, l, brec, depth+1) + findsum(0+powtwo[depth+1], l, brec+cArr[depth], depth+1);
    }
    else if(l-lcur +1 <= powtwo[depth+1]){//l
        printf("(%lld, %lld, %lld, %lld,l)\n", lcur, l, depth, powtwo[depth+1]);
        sum = findsum(0, l, brec, depth+1);
    }
    else printf("ERROR\n");
    return sum;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> mod >> dayk;
    powtwo[dayk] = N;
    for(int i = dayk-1; i >=0; i--) powtwo[i] = powtwo[i+1]*2;
    initArr = (int**) malloc((N+1)* sizeof(int*));// the array of a
    cArr = (int*) malloc((dayk)* sizeof(int));
    subSum = (int**) malloc((dayk+1)* sizeof(int*));

    initArr[0] = (int*) malloc((mod)* sizeof(int));
    for(int i = 0; i < mod; i++) initArr[0][i] = 0;
    for(int i = 1; i < N+1; i++){
        int tmp;
        initArr[i] = (int*) malloc((mod)* sizeof(int));
        for(int j = 0; j < mod; j++) initArr[i][j] = initArr[i-1][j];
        cin >> tmp;
        initArr[i][tmp]++;
    }
    for(int i = 0; i < dayk; i++) cin >> cArr[i];
    subSum[dayk] = (int*) malloc((mod)* sizeof(int));
    for(int i = 0; i < mod; i++) 
        subSum[dayk][i] = initArr[N][i];
    for(int i = dayk-1; i >= 0; i--){
        subSum[i] = (int*) malloc((mod)* sizeof(int));
        for(int j = 0; j < mod; j++) subSum[i][j] = subSum[i+1][j];
        for(int j = 0; j < mod; j++) {
            // printf("%lld dayk,%lld+%lld from %lld\n", i, j, subSum[i+1][(j-cArr[i]+mod)%mod], (j-cArr[i]+mod)%mod);
            subSum[i][j] += subSum[i+1][(j-cArr[i]+mod)%mod];
        }
    }
    // for(int i = 0; i <= dayk; i++) {
    //     for(int j = 0; j < mod; j++) printf("%lld ",subSum[i][j]);
    //     printf("\n");
    // }
    int buyer, l, r;
    cin >> buyer;
    for(int k = 0; k < buyer; k++) {
        cin >> l >> r;
        int sum = 0;
        sum += findsum(0, r, 0, 0);
        printf("\n%lld\n",sum);
        sum -= findsum(0, l-1, 0, 0);
        printf("\n%lld\n",sum);
        cout << sum << "\n";
    }
}
