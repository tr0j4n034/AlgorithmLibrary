//
//  main.cpp
//  practice
//
//  Created by Mahmud on 01/31/19.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>


using namespace std;

void read(string& text) {
    freopen("input.txt", "r", stdin);
    text = "";
    string s;
    while (cin >> s) {
        if (cin.eof())
            break;
        for (char &ch: s)
            ch = tolower(ch);
        text += s;
    }
}

int main(int argc, const char * argv[]) {
    string text = "this is an example for huffman encoding";
    
    read(text);
    
    map<char, int> counters;
    for_each(begin(text), end(text), [&](char ch) {
        counters[ch] ++;
    });
    for (auto i: counters) {
        cout << "weight of " << i.first << " is " << i.second << endl;
    }
    
    
    //priority_queue<data, vector< data >, greater<data> > Q;
    priority_queue<pair<int, vector<char> >, vector<pair<int, vector<char> >>,
    greater<pair<int, vector<char> >>> Q;
    // I know it is ugly ^.
    
    for (auto i: counters) {
        Q.push(make_pair(i.second, vector<char>(1, i.first)));
    }
    map<char, string> identifiers;
    while (int(Q.size()) > 1) {
        auto itemSet1 = Q.top();
        Q.pop();
        auto itemSet2 = Q.top();
        Q.pop();
        for_each(begin(itemSet1.second), end(itemSet1.second), [&](char ch) {
            identifiers[ch] = '0' + identifiers[ch];
        });
        for_each(begin(itemSet2.second), end(itemSet2.second), [&](char ch) {
            identifiers[ch] = '1' + identifiers[ch];
        });
        int weight = itemSet1.first + itemSet2.first;
        vector<char> merged = itemSet1.second;
        for (auto ch: itemSet2.second)
            merged.push_back(ch);
        Q.push(make_pair(weight, merged));
    }
    
    cout << endl;
    
    vector<pair<char, string>> result;
    for (auto item: identifiers)
        result.push_back(make_pair(item.first, item.second));
    sort(result.begin(), result.end(), [](pair<char, string> a, pair<char, string> b) {
        string s1 = a.second;
        string s2 = b.second;
        if (s1.length() != s2.length())
            return s1.length() < s2.length();
        for (int i = 0; i < s1.length(); i ++) {
            if (s1[i] != s2[i])
                return s1[i] < s2[i];
        }
        return false;
    });
    for_each(begin(result), end(result), [&](pair<char, string> item) {
        cout << item.second << " " << item.first << endl;
    });
    
    cout << endl;
    cout << endl;
    
    int huffmanTotal = 0;
    for (auto item: counters)
        huffmanTotal += item.second * identifiers[item.first].length();
    double v = text.length() * log2(int(counters.size()));
    
    cout << "length of the initial text in bits: " << text.length() * log2(int(counters.size())) << endl;
    cout << "length via Huffman encoding in bits: " << huffmanTotal << endl;
    cout << "the number of the saved bits: " << text.length() * 8 - huffmanTotal << endl;
    cout << "the gain in the size in percentages is: " << 100. * (v - huffmanTotal) / v << endl;
    cout << endl;
    
    
    double entropySource = 0.;
    for (auto item: counters) {
        entropySource += -1. * item.second / text.length() * log2(1. * item.second / text.length());
    }
    cout << "entropy of the source is: " << entropySource * int(text.length()) << endl;
    cout << "average length for huffman encoding is: " << 1. * huffmanTotal / text.length() << endl;
    cout << endl;
    
    return 0;
}

