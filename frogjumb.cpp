#include <bits/stdc++.h>

using namespace std;

int fib(int i, vector<int> &heights, vector<int> &dp) 
{
    if (i == 0) return 0;

    if (dp[i] != -1) return dp[i];

    int ls = fib(i - 1, heights, dp) + abs(heights[i] - heights[i - 1]);

    int rs = INT_MAX;

    if (i > 1) 
    {
        rs = fib(i - 2, heights, dp) + abs(heights[i] - heights[i - 2]);
    }

    return dp[i] = min(ls, rs);
}

int frogJump(int n, vector<int> &heights) 
{
    vector<int> dp(n, -1);

    return fib(n - 1, heights, dp);
}

int main() 
{
    vector<int> heights = {30, 10, 60, 10, 60, 50};
    
    cout << frogJump(heights.size(), heights) << endl; 
}
