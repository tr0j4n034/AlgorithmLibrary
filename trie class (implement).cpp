#include <bits/stdc++.h>

using namespace std;

#define Long long long
#define ld long double
#define pii pair<int, int>
#define pli pair<Long, int>

const int me = 100025;
const int mod = 1.e9 + 7;

class Trie{
private:
    const static int ALPHABET = 26;
    const static char FIRST_LETTER = 'a';
    struct node{
        int link[ALPHABET];
        bool is_word;
        node(){
            for(int i = 0; i < ALPHABET; i ++)
                link[i] = -1;
            is_word = false;
        }
    };
    node make_node(){
        node c = node();
        return c;
    }
    int get(char x){
        return x - FIRST_LETTER;
    }
    void traverse(int pos, string s){
        if(trie[pos].is_word){
            cout << "word: " << s << endl;
        }
        for(int i = 0; i < ALPHABET; i ++)
            if(trie[pos].link[i] != -1)
                traverse(trie[pos].link[i], s + (char)(i + 'a'));
    }
    
public:
    vector<node> trie;
    int Size;
    Trie(){
        trie.push_back(make_node());
        Size = 1;
    }
    ~Trie() {
    };
    int size(){
        return Size;
    }
    void add(string s){
        int pos = 0;
        for(char i : s){
            int x = get(i);
            if(trie[pos].link[x] == -1){
                node c = make_node();
                trie.push_back(c);
                trie[pos].link[x] = Size;
                pos = Size ++;
            }
            else{
                pos = trie[pos].link[x];
            }
        }
        trie[pos].is_word = true;
    }
    void output(){
        traverse(0, "");
    }
};


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    Trie t = Trie();
    t.add("abcd");
    t.add("bdefd");
    t.add("aaa");
    t.add("abcc");
    t.output();
    
    return 0;
}
