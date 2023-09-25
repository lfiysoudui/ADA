#include <iostream>
#include <vector>
using namespace std;

int main() {
    int arrlength, K;
    cin >> arrlength >> K;

    vector<int> arr(arrlength);
    for (int i = 0; i < arrlength; i++) {
        cin >> arr[i];
    }

    int minLength = arrlength + 1; // Initialize to a value greater than the maximum possible length
    int sum = 0;
    int left = 0;

    for (int right = 0; right < arrlength; right++) {
        sum += arr[right];

        while (sum > K && left <= right) {
            minLength = min(minLength, right - left + 1);
            sum -= arr[left];
            left++;
        }
    }

    if (minLength == arrlength + 1) {
        cout << "No subarray found with sum greater than " << K << endl;
    } else {
        cout << "Shortest subarray length with sum greater than " << K << ": " << minLength << endl;
    }

    return 0;
}
