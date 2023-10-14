#include "iostream"

#define int long long

using namespace std;

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int y,x;
    scanf("%lld%lld", &y, &x);
    int* price[x+1];
    for(int i = 0; i < x+1; i++)
        price[i] = (int*) malloc((y+1)* sizeof(int));
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            scanf("%lld", &price[j][i]);
        }
    }
    for(int j = 0; j < x+1; j++){
        price[j][y] = 0;
    }
    for(int j = 0; j < y+1; j++){
        price[x][j] = 0;
    }
    int houses, ycoor, xcoor, safedist, hprice;
    scanf("%lld",&houses);
    for(int i = 0; i < houses; i++){
        scanf("%lld%lld%lld%lld", &ycoor, &xcoor, &safedist, &hprice);
        price[xcoor - safedist - 1][ycoor - safedist - 1] -= hprice;
    }

    for(int i = 0; i < x ; i++){
        for(int j = y-2; j >= 0; j--){
            price[i][j] += price[i][j+1];
        }
    }
    for(int j = y-1; j >= 0; j--){
        if(price[0][j] > price[0][j+1])
            price[0][j] = price[0][j+1];
    }
    for(int i = 1; i < x ; i++){
        for(int j = y-1; j >= 0; j--){
            if(price[i][j] + price[i-1][j] > price[i][j+1])
                price[i][j] = price[i][j+1];
            else
                price[i][j] += price[i-1][j];
        }
    }
    printf("%lld", -price[x-1][0]);
}

// ref:
// 138 柯柏任
// 155 陳致和