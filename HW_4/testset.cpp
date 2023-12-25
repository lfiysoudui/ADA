#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    for( auto i = v.rbegin(); i != v.rend(); ++i )
        std::cout << *i << '\n';
}
