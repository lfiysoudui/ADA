#include <iostream>
#include <algorithm>


int findmax(int a, int b, int c){
    int tmp = a;
    if ( b > tmp ) tmp = b;
    if ( c > tmp ) tmp = c;
    return tmp;
}

int findMaxSub (int l, int r, int* head){
    // std::cout << "( " << l << " , " << r << " )\n";
    if(l >= r) return head[l];
    else{
        int tmpsum = head[(l+r)/2], maxSub = head[(l+r)/2];
        for(int i = (l+r)/2-1; i >= l ; i--){
            tmpsum += head[i];
            if( maxSub < tmpsum ) maxSub = tmpsum;
        }
        tmpsum = maxSub;
        for(int i = (l+r)/2+1; i <=r ; i++){
            tmpsum += head[i];
            if( maxSub < tmpsum ) maxSub = tmpsum;
        }
        return findmax( findMaxSub(l,(l+r)/2,head), findMaxSub((l+r)/2+1,r,head), maxSub);
    }
}

int main (){
    int len;
    std::cin >> len;
    int* arr = new int[len];
    for(int i = 0; i < len; i++){
        std::cin >> arr[i];
    }
    std::cout << findMaxSub(0,len-1,arr);

}
// 6
// 1 -2 7 -4 6 -3