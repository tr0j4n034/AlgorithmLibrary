#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <utility>
#include <cassert>
#include <iomanip>
#include <ctime>

using namespace std;

const int me = 100025;

typedef struct node{
    int value;
    int subtree_value;
    int priority;
    int _cnt;
    node *l, *r;
}node;
typedef node* pnode;

int get_value(pnode &t){
    return t? t->subtree_value : INT_MAX;
}
int get_size(pnode &t){
    return t? t->_cnt : 0;
}
void update_value(pnode &t){
    if(t)
        t->subtree_value = min(get_value(t->l),
                               min(t->value, get_value(t->r)));
}
void update_size(pnode &t){
    if(t)
        t->_cnt = get_size(t->l) + 1 + get_size(t->r);
}
void Split(pnode t, pnode &l, pnode &r, int key){
    if(!t)
        return void(l = r = NULL);
    if(t->value > key)
        Split(t->l, l, t->l, key), r = t;
    else Split(t->r, t->r, r, key), l = t;
    update_value(t);
    update_size(t);
}
void Merge(pnode &t, pnode l, pnode r){
    if(!l || !r)
        t = l? l : r;
    else if(l->priority > r->priority)
        Merge(l->r, l->r, r), t = l;
    else Merge(r->l, l, r->l), t = r;
    update_value(t);
    update_size(t);
}
pnode Init(int key){
    pnode p = pnode(malloc(sizeof(node)));
    p->value = p->subtree_value = key;
    p->priority = rand();
    p->_cnt = 1;
    p->l = NULL;
    p->r = NULL;
    return p;
}
void Insert(pnode &t, int key){
    pnode l, r;
    Split(t, l, r, key - 1);
    pnode p = Init(key);
    Merge(l, l, p);
    Merge(t, l, r);
}
bool Find(pnode &t, int key){
    if(!t)
        return false;
    if(t->value == key)
        return true;
    if(t->value > key)
        return Find(t->l, key);
    return Find(t->r, key);
}
void Erase(pnode &t, int key){
    if(!Find(t, key))
        return;
    pnode l1, r1;
    Split(t, l1, r1, key - 1);
    pnode l2, r2;
    Split(r1, l2, r2, key);
    Merge(t, l1, r2);
}
int Order_of_key_utility(pnode &t, int key, int add = 0){
    if(t->value == key)
        return add + get_size(t->l) + 1;
    int cur_pos = get_size(t->l) + add + 1;
    if(t->value > key)
        return Order_of_key_utility(t->l, key, add);
    return Order_of_key_utility(t->r, key, cur_pos);
}
int Order_of_key(pnode &t, int key){
    if(!Find(t, key))
        return -1;
    return Order_of_key_utility(t, key);
}
int Kth_element(pnode &t, int k){
    if(get_size(t->l) + 1 == k)
        return t->value;
    if(get_size(t->l) + 1 > k)
        return Kth_element(t->l, k);
    return Kth_element(t->r, k - get_size(t->l) - 1);
}
void Print(pnode &t){
    if(!t)
        return;
    Print(t->l);
    cout << t->value << endl;
    Print(t->r);
}

int main() {
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    
    pnode t = NULL;
    for(int i = 0; i < 10; i ++){
        string type;
        cin >> type;
        if(type == "insert"){
            int a;
            cin >> a;
            Insert(t, a);
        }
        else if(type == "erase"){
            int a;
            cin >> a;
            Erase(t, a);
        }
        else if(type == "order"){
            int a;
            cin >> a;
            cout << Order_of_key(t, a) << endl;
        }
        else if(type == "kth"){
            int a;
            cin >> a;
            cout << Kth_element(t, a) << endl;
        }
        else if(type == "print"){
            Print(t);
        }
        else break;
    }
    return 0;
}
