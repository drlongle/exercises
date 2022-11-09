
#include <algorithm>
#include <iterator>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Merge two files at a time.
// Cost of each merge is the size of the two merges files.
// Find the minimum cost for merging a list of files.
int minimumTime(int numOfSubFiles, int* files)
{
    vector<int> f;
    for (int i = 0; i < numOfSubFiles; ++i) {
        f.emplace_back(files[i]);
    }
    int cost = 0;
    while (f.size() > 1) {
        sort(begin(f), end(f), greater<int>());
        int n = f.size();
        f[n-2] += f[n-1];
        f.pop_back();
        cost += f.back();
    }

    return cost;
}

int minimumTime2(int numOfSubFiles, int* files)
{
    priority_queue<int, vector<int>, greater<int>> f;
    for (int i = 0; i < numOfSubFiles; ++i) {
        f.emplace(files[i]);
    }
    int cost = 0;
    while (f.size() > 1) {
        int a = f.top();
        f.pop();
        int b = f.top();
        f.pop();
        int c = a + b;
        cost += c;
        f.emplace(c);
    }

    return cost;
}


int main()
{
    int files[] =  {8, 4, 6, 12};
    int n = 4;

    cout << "Result: " << minimumTime2(n, files) << endl;
    return 0;
}
