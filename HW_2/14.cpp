#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long
#define maxlen 500000

using namespace std;

typedef struct kiwican{
    ll can;
    ll kiwi;
    ll clsteps;
}kiwican;

vector<kiwican> vec;
vector<ll> sorted;
ll inputlen;
ll goldkiwi;


bool compare(int a, int b) {
    a = vec[a].kiwi;
    b = vec[b].kiwi;
    return a < b;  // Sort in ascending order
}

void solve();

signed main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll T;
    cin >> T;
    for(int i = 0; i < T; i++){
        cin >> inputlen;
        cin >> goldkiwi;
        vec.resize(inputlen);
        sorted.resize(inputlen);
        for(int i = 0; i < inputlen; i++) cin >> vec[i].can;
        for(int i = 0; i < inputlen; i++) cin >> vec[i].kiwi;
        for(int i = 0; i < inputlen; i++) sorted[i] = i;
        sort(sorted.begin(), sorted.end(), compare);
        solve();
        // for(int i = 0; i < inputlen; i++) cerr << sorted[i] << " ";
        // cerr << "\n";
    }
}

void solve(){
    for(int i = 0; i < inputlen; i++){
        if(vec[sorted[i]].kiwi == 0){
            vec[sorted[i]].clsteps = 0;
            continue;
        }
        else{
            vec[sorted[i]].clsteps = -1;
        }
        ll j = 0;
        while(j < i){
            if(vec[sorted[j]].can < vec[sorted[i]].kiwi || vec[sorted[j]].clsteps < 0){
                j++;
                continue;
            }
            ll tmp = vec[sorted[j]].clsteps + 1;
            if(vec[sorted[i]].clsteps != -1) vec[sorted[i]].clsteps = min( vec[sorted[i]].clsteps, tmp);
            else vec[sorted[i]].clsteps = tmp;
            j++;
        }
    }
    for(int i = 0; i < inputlen; i++){
        if(vec[i].can < vec[goldkiwi-1].kiwi || vec[i].clsteps == -1) vec[i].clsteps = -1;
        else vec[i].clsteps++;
    }
    vec[goldkiwi-1].clsteps = 0;
    cout << vec[0].clsteps;
    for(int i = 1; i < inputlen; i++){
        cout << " " << vec[i].clsteps;
    }
    cout << "\n";
}