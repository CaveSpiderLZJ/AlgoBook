#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

#define MAX 100010
#define W_MIN 16 // min width of a leaf node
#define N_MAX 16 // max line in a leaf node
#define LL long long

class Line {
public:
    LL x1, x2, y1, y2;
    double a;
    bool dir;

    Line(LL _x1, LL _y1, LL _x2, LL _y2, double _a) {
        if (_x1 < _x2) { x1 = _x1; x2 = _x2; }
        else { x1 = _x2; x2 = _x1; }
        if (_y1 < _y2) { y1 = _y1; y2 = _y2; }
        else { y1 = _y2; y2 = _y1; }
        a = _a;
        dir = (_x1<_x2 && _y1<_y2) || (_x2<_x1 && _y2<_y1);
    }

    int intersect(LL x, LL y, int d) {
        // test intersect with a light
        // if intersect, return the distance;
        // if not, return 0;
        int res = 0;
        LL ix, iy; // intersect x, y;
        if ((d&1) == 0) { // d == 0 || d == 2
            if (y <= y1 || y >= y2) return res;
            if (dir) ix = x1 + y - y1;
            else ix = x1 + y2 - y;
            if ((d==0 && x>=ix) || (d==2 && x<=ix)) return res;
            res = abs(x - ix);
        } else { // d == 1 || d == 3
            if (x <= x1 || x >= x2) return res;
            if (dir) iy = y1 + x - x1;
            else iy = y1 + x2 - x;
            if ((d==1 && y>=iy) || (d==3 && y<=iy)) return res;
            res = abs(y - iy);
        }
        return res;
    }

    bool intersect(LL& x, LL& y, LL& d, double& I, LL& t) {
        // modify the light when intersected
        // if intersact, store the next start point in x,y,d,I,t,
        // return true; if not, do not change x,y,d,I,t, return false;
        LL ix, iy; // intersect x, y;
        if ((d&1) == 0) { // d == 0 || d == 2
            if (y <= y1 || y >= y2) return false;
            if (dir) ix = x1 + y - y1;
            else ix = x1 + y2 - y;
            if ((d==0 && x>=ix) || (d==2 && x<=ix)) return false;
            if (d == 0) {
                if (t < ix - x) return false;
                t -= (ix - x); x = ix;
                d = dir ? 1 : 3; I *= a;
            } else {    // d == 2
                if (t < x - ix) return false;
                t -= (x - ix); x = ix;
                d = dir ? 3 : 1; I *= a;
            }
        } else { // d == 1 || d == 3
            if (x <= x1 || x >= x2) return false;
            if (dir) iy = y1 + x - x1;
            else iy = y1 + x2 - x;
            if ((d==1 && y>=iy) || (d==3 && y<=iy)) return false;
            if (d == 1) {
                if (t < iy - y) return false;
                t -= (iy - y); y = iy;
                d = dir ? 0 : 2; I *= a;
            } else {    // d == 3
                if (t < y - iy) return false;
                t -= (y - iy); y = iy;
                d = dir ? 2 : 0; I *= a;
            }
        }
        return true;
    }
};

Line* lines[MAX];

class Node {
public:
    Node* parent;
    Node* children[4];
    LL x1, y1, x2, y2;
    vector<int> lineIdxs;

    Node(LL _x1, LL _y1, LL _x2, LL _y2, Node* _parent = nullptr) {
        x1 = _x1; y1 = _y1;
        x2 = _x2; y2 = _y2;
        parent = _parent;
        for (int i = 0; i < 4; i++)
            children[i] = nullptr;
    }

    bool isLeaf() {
        bool res = true;
        for (int i = 0; i < 4; i++) {
            if (children[i] != nullptr) {
                res = false;
                break;
            }
        }
        return res;
    }

    bool intersect(LL x, LL y, int d) {
        // test intersect with light
        if ((d&1) == 0) { // d == 0 || d == 2
            if (y <= y1 || y >= y2) return false;
            if (d == 0 && x >= x2) return false;
            if (d == 2 && x <= x1) return false;
        } else {
            if (x <= x1 || x >= x2) return false;
            if (d == 1 && y >= y2) return false;
            if (d == 3 && y <= y1) return false;
        }
        return true;
    }

    int intersect(int idx) {
        // return 0~15, (1<<x) means intersect with x quandrant (0<=x<4)
        Line* line = lines[idx];
        if (line == nullptr) return 0;
        int res = 0;
        LL xs[4] = { (x1+x2)/2, x1, x1, (x1+x2)/2 };
        LL ys[4] = { (y1+y2)/2, (y1+y2)/2, y1, y1 };
        LL w = (x2-x1) / 2;
        for (int i = 0; i < 4; i++) {
            LL x = xs[i], y = ys[i], d;
            if (line->dir) d = abs(x - y + line->y1 - line->x1);
            else d = abs(x + y + w - line->x1 - line->y2);
            if (d>=w || line->x2<=x || line->x1>=x+w || line->y2<=y || line->y1>=y+w)
                continue;
            res += (1 << i);
        }
        return res;
    }

    void insert(int idx) {
        // cout << "### Node::insert() " << idx << endl;
        if (intersect(idx) == 0) return;
        if (!isLeaf()) { // has children
            for (int i = 0; i < 4; i++) {
                if (children[i] != nullptr && children[i]->intersect(idx) > 0)
                    children[i]->insert(idx);
            }
            return;
        }
        // is the minimum leaf node, directly puch back
        if (x2-x1 <= W_MIN) {
            lineIdxs.push_back(idx);
            return;
        }
        // may split into four children
        lineIdxs.push_back(idx);
        if (lineIdxs.size() > N_MAX) {
            // split to four children
            LL cw = (x1+x2)/2 - x1; // child width
            LL xs[4] = { x1+cw, x1, x1, x1+cw };
            LL ys[4] = { y1+cw, y1+cw, y1, y1 };
            for (int i = 0; i < 4; i++)
                children[i] = new Node(xs[i], ys[i], xs[i]+cw, ys[i]+cw, this);
            for (int j: lineIdxs) {
                int res = intersect(j);
                for (int i = 0; i < 4; i++) {
                    if ((res&(1<<i)) != 0)
                        children[i]->insert(j);
                }
            }
            lineIdxs.clear();
        }
        return;
    }
};

class QuadTree {
public:
    Node* root;

    QuadTree() {
        root = new Node(-((LL)1<<32), -((LL)1<<32), ((LL)1<<32), ((LL)1<<32));
    }

    void insert(int idx) {
        root->insert(idx);
    }

    void intersect(LL& x, LL& y, LL& d, double& I, LL& t) {
        while (I >= 1.0 && t > 0) {
            // printf("### xydIt: %d %d %d %lf %d\n", x, y, d, I, t);
            set<int> lineIdxs;
            vector<Node*> nodes = {root};
            int head = 0;
            while (head < nodes.size()) {
                Node* current = nodes[head++];
                if (!current->intersect(x, y, d)) continue;
                if (current->isLeaf()) {
                    for (int idx: current->lineIdxs)
                        lineIdxs.insert(idx);
                } else {
                    for (int i = 0; i < 4; i++) {
                        Node* node = current->children[i];
                        if (node != nullptr) nodes.push_back(node);
                    }
                }
            }
            // for (int i = 0; i < 10010; i++) {
            //     if (lines[i] != nullptr) lineIdxs.insert(i);
            // }
            LL minDis = ((LL)1 << 32);
            LL minIdx = MAX;
            for (int idx: lineIdxs) {
                Line* line = lines[idx];
                if (line == nullptr) continue;
                LL dis = line->intersect(x, y, d);
                if (dis > 0 && dis <= t && dis < minDis) {
                    minDis = dis;
                    minIdx = idx;
                }
            }
            if (minIdx == MAX) { // not intersected
                if (d == 0) x += t;
                else if (d == 1) y += t;
                else if (d == 2) x -= t;
                else if (d == 3) y -= t;
                t = 0;
            } else {
                Line* line = lines[minIdx];
                line->intersect(x, y, d, I, t);
            }
        }
        // printf("### xydIt: %d %d %d %lf %d", x, y, d, I, t);
    }
};


int main() {
    // init
    for (int i = 0; i < MAX; i++)
        lines[i] = nullptr;
    QuadTree tree = QuadTree();
    LL m, op, x1, y1, x2, y2;
    LL k, x, y, d, t;
    double a, I;
    scanf("%lld", &m);
    for (LL i = 0; i < m; i++) {
        scanf("%lld", &op);
        if (op == 1) {
            scanf("%lld %lld %lld %lld %lf", &x1, &y1, &x2, &y2, &a);
            lines[i] = new Line(x1, y1, x2, y2, a);
            tree.insert(i);
        } else if (op == 2) {
            scanf("%lld", &k);
            if (lines[k-1] != nullptr) {
                // delete lines[k-1];
                lines[k-1] = nullptr;
            }
        } else if (op == 3) {
            scanf("%lld %lld %lld %lf %lld", &x, &y, &d, &I, &t);
            tree.intersect(x, y, d, I, t);
            if (I >= 1.0) {
                printf("%lld %lld %lld\n", x, y, (LL)I);
            } else printf("0 0 0\n");
        }
    }
    return 0;
}