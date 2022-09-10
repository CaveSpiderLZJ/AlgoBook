#include<cstdio>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

#define MAX 100005

int n, m, k, t, c, q;
int ts[MAX], cs[MAX];

class Node {
public:
    int left, right, cnt;
    Node *lc, *rc;

    Node(int l, int r) {
        left = l; right = r; cnt = 0;
        lc = rc = nullptr;
    }

    void split(int mid) {
        lc = new Node(left, mid);
        rc = new Node(mid, right);
    }

    void add(int l, int r) {
        if (r <= left || l >= right) return;
        if (l <= left && right <= r) { cnt++; return; }
        lc->cnt += cnt;
        rc->cnt += cnt;
        cnt = 0;
        lc->add(l, r);
        rc->add(l, r);
    }

    int search(int q) {
        if (lc == nullptr && rc == nullptr) return cnt;
        lc->cnt += cnt;
        rc->cnt += cnt;
        cnt = 0;
        if (q < lc->right) return lc->search(q);
        return rc->search(q);
    }
};

class SearchTree {
public:
    Node* root;
    vector<int> knots;

    SearchTree(const set<int>& _knots) {
        for (int knot: _knots) knots.push_back(knot);
        knots.push_back(2 * MAX);
        sort(knots.begin(), knots.end());
        root = new Node(knots[0], knots[knots.size()-1]);
        build(root, 0, knots.size() - 1);
    }

    void build(Node* node, int lIdx, int rIdx) {
        if (lIdx >= rIdx-1) return;
        int mIdx = (lIdx + rIdx) / 2;
        node->split(knots[mIdx]);
        build(node->lc, lIdx, mIdx);
        build(node->rc, mIdx, rIdx);
    }
};


int main() {
    scanf("%d %d %d", &n, &m, &k);
    set<int> knots = {0};
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &t, &c);
        knots.insert(max(0, t-k-c+1));
        knots.insert(max(0, t-k+1));
        ts[i] = t;
        cs[i] = c;
    }
    SearchTree tree = SearchTree(knots);
    for (int i = 0; i < n; i++) {
        t = ts[i]; c = cs[i];
        tree.root->add(max(0, t-k-c+1), max(0, t-k+1));
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &q);
        int res = tree.root->search(q);
        printf("%d\n", res);
    }
    return 0;
};