#include <bits/stdc++.h>
using namespace std;

class Solution 
{
public:
    struct Node 
    {
        int cnt[3]; 
    };

    int N;
    vector<Node> tree;
    vector<int> lazy;

    Solution(int n) : N(n) 
    {
        tree.resize(4 * N);
        lazy.assign(4 * N, 0);
    }

    void build(int node, int start, int end) 
    {
        if (start == end) 
        {
            tree[node].cnt[0] = 1;
            return;
        }
        int mid = (start + end) >> 1;
        build(node << 1, start, mid);
        build(node << 1 | 1, mid + 1, end);
        pull(node);
    }

    inline void pull(int node) 
    {
        for (int i = 0; i < 3; ++i)
            tree[node].cnt[i] = tree[node << 1].cnt[i] + tree[node << 1 | 1].cnt[i];
    }

    inline void rotate(Node &n) 
    {
        int tmp = n.cnt[2];
        n.cnt[2] = n.cnt[1];
        n.cnt[1] = n.cnt[0];
        n.cnt[0] = tmp;
    }

    void push(int node, int start, int end) 
    {
        int times = lazy[node] % 3;
        while (times--) rotate(tree[node]);

        if (start != end) 
        {
            lazy[node << 1] += lazy[node];
            lazy[node << 1 | 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    void update(int node, int start, int end, int l, int r) 
    {
        push(node, start, end);
        if (r < start || end < l) return;

        if (l <= start && end <= r) 
        {
            lazy[node]++;
            push(node, start, end);
            return;
        }

        int mid = (start + end) >> 1;
        update(node << 1, start, mid, l, r);
        update(node << 1 | 1, mid + 1, end, l, r);
        pull(node);
    }

    int query(int node, int start, int end, int l, int r) 
    {
        push(node, start, end);
        if (r < start || end < l) return 0;

        if (l <= start && end <= r)
            return tree[node].cnt[0];

        int mid = (start + end) >> 1;
        return query(node << 1, start, mid, l, r) +
               query(node << 1 | 1, mid + 1, end, l, r);
    }

    void solve() 
    {
        int Q;
        cin >> N >> Q;
        build(1, 0, N - 1);

        while (Q--) 
        {
            int type, l, r;
            cin >> type >> l >> r;
            if (type == 0)
                update(1, 0, N - 1, l, r);
            else
                cout << query(1, 0, N - 1, l, r) << '\n';
        }
    }
};

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    Solution sol(N);
    sol.solve();
    return 0;
}
