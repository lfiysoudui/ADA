#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    auto i = find(begin(v), end(v), 2);

    cout << *i << endl; // PRINTS 2

    reverse_iterator<decltype(i)> ri(i);
    cout << *ri << endl; // PRINTS 1
    cout << *ri.base() << endl; // PRINTS 1
}