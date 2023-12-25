#include <iostream>
#include <iterator>
#include <set>
#include <cstring>
#include <vector>

using namespace std;



multiset<long long, greater<long long>> lower;
multiset<long long> upper;
long long lowersum;
long long uppersum;
long long median;

void kiwi(long long x){
    if(lower.size() > upper.size()){
        if(x < median){
            long long temp = *(lower.begin());
            lowersum -= temp;
            lower.erase(lower.begin());
            uppersum += temp;
            upper.insert(temp);
            lowersum += x;
            lower.insert(x);
        }
        else{
            uppersum += x;
            upper.insert(x);
        }
    }
    else{
        if(x > median){
            uppersum += x;
            upper.insert(x);
            long long temp = *(upper.begin());
            uppersum -= temp;
            upper.erase(upper.begin());
            lowersum += temp;
            lower.insert(temp);
        }
        else{
            lowersum += x;
            lower.insert(x);
        }
    }
    median = *(lower.begin());
    return;
}

void wiki(long long x){
    if(x <= median){
        lowersum -= x;
        auto i = lower.find(x);
        if(i != lower.end()) lower.erase(i);
    }
    else{
        uppersum -= x;
        auto i = upper.find(x);
        if(i != upper.end()) upper.erase(i);
    }
    if(lower.size() - upper.size() == 2){
        long long temp = *(lower.begin());
        lowersum -= temp;
        lower.erase(lower.begin());
        uppersum += temp;
        upper.insert(temp);
    }
    if(lower.size() < upper.size()){
        long long temp = *(upper.begin());
        uppersum -= temp;
        upper.erase(upper.begin());
        lowersum += temp;
        lower.insert(temp);
    }
    if(!lower.empty()){
        median = *(lower.begin());
    }
    else{
        median = LLONG_MAX;
    }
    return;
}

void wiwi(void){
    long long ans = 0;
    if(median != LLONG_MAX){
        ans += uppersum - (median * (long long)upper.size());
        ans += (median * (long long)lower.size()) - lowersum;
    }
    cout << ans << "\n";
    return;
}

void kiki(long long x){
    if(upper.empty() || lower.size() + upper.size() == x) return;
    if(x == 1){
        lowersum += uppersum;
        median = lowersum;
        lower.clear();
        upper.clear();
        uppersum = 0;
        lower.insert(lowersum);
        return;
    }
    if(x >= lower.size()){
        int skip = x - lower.size();
        int merge = upper.size() - skip;
        vector<long long> newelements(merge);
        multiset<long long>::iterator i = upper.begin();
        while(skip--) i++;
        multiset<long long>::reverse_iterator j = lower.rbegin();
        for(int k = 0; k < merge; k++){
            long long templow = *(j);
            long long temphigh = *(i);
            lowersum -= templow;
            uppersum += templow;
            auto tempi = i;
            i++;
            upper.erase(tempi);
            lower.erase(--j.base());
            newelements[k] = templow + temphigh;
        }
        while(merge--){
            upper.insert(newelements[merge]);
        }
        while(lower.size() < upper.size()){
            long long temp = *(upper.begin());
            uppersum -= temp;
            upper.erase(upper.begin());
            lowersum += temp;
            lower.insert(temp);
        }
        median = *(lower.begin());
        return;
    }
    vector<long long> newelements(x, 0);
    int counter = 0;
    for(auto i = lower.rbegin(); i != lower.rend(); i++){
        newelements[(counter++) % x] += *i;
    }
    for(auto i = upper.begin(); i != upper.end(); i++){
        newelements[(counter++) % x] += *i;
    }
    lower.clear();
    lowersum = 0;
    upper.clear();
    uppersum = 0;
    sort(newelements.begin(), newelements.end());
    int lowersize = (x % 2 == 0)? x/2 : x/2 + 1;
    for(int i = 0; i < lowersize; i++){
        lowersum += newelements[i];
        lower.insert(newelements[i]);
    }
    for(int i = x - 1; i >= lowersize; i--){
        uppersum += newelements[i];
        upper.insert(newelements[i]);
    }
    median = *(lower.begin());
    return;
}

int main(void){
    lowersum = 0;
    uppersum = 0;
    median = LLONG_MAX;
    int N;
    cin >> N;
    string cmd;
    long long x;
    for(int i = 0; i < N; i++){
        cin >> cmd;
        if(cmd == "kiwi"){
            cin >> x;
            kiwi(x);
        }
        else if(cmd == "wiki"){
            cin >> x;
            wiki(x);
        }
        else if(cmd == "wiwi"){
            wiwi();
        }
        else{
            cin >> x;
            kiki(x);
        }
    }
    return 0;
}