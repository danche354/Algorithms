#include <iostream>
#include <vector>

using namespace std;

vector<int> get_next_ii(string p) {
    int p_length = p.size();
    vector<int> next(p_length);

    // i: first point
    // j: last point
    int i = -1;
    int j = 0;

    next[j] = -1;

    while (j<p_length) {
        if (i==-1||p[i]==p[j]) {
            i++;
            j++;
            // next.size() is same as p.size() 
            if (j==p_length) break;
            if (p[i]!=p[j]) next[j] = i;
            else next[j] = next[i];
        }
        else i = next[i];
    }

    return next;
}


vector<int> get_next_i(string p) {
    int p_length = p.size();
    vector<int> next(p_length);

    // i: first point
    // j: last point
    int i = -1;
    int j = 0;

    next[j] = -1;

    while (j<p_length) {
        if (i==-1||p[i]==p[j]) {
            i++;
            j++;
            // next.size() is same as p.size() 
            if (j==p_length) break;
            next[j] = i;
        }
        else i = next[i];
    }

    return next;
}


vector<string> KMP_match(string s, string p) {
    int s_length = s.size();
    int p_length = p.size();

    vector<int> next = get_next_ii(p);

    int i = 0;
    int j = 0;
    // record the substring start position
    int start = 0;
    vector<string> res;

    while (i<s_length) {
        if (j==-1||s[i]==p[j]) {
            i++;
            j++;
        }
        else {
            j = next[j];
        }
        if (j==p_length) {
            // substring length is `i-start-j`
            if (i-start-j!=0) res.push_back(s.substr(start, i-start-j));
            start = i;
            j = 0;
        }
    }
    // last segment need to be cosidered
    if (start!=s_length) res.push_back(s.substr(start, s_length-start));

    return res;
}

vector<string> violence_match(string s, string p) {
    int s_length = s.size();
    int p_length = p.size();

    int i = 0;
    int j = 0;
    // record the substring start position
    int start = 0;
    vector<string> res;

    while (i<s_length) {
        if (s[i]==p[j]) {
            i++;
            j++;
        }
        else {
            i = i-j+1;
            j = 0;
        }
        if (j==p_length) {
            // substring length is `i-start-j`
            if (i-start-j!=0) res.push_back(s.substr(start, i-start-j));
            start = i;
            j = 0;
        }
    }
    // last segment need to be cosidered
    if (start!=s_length) res.push_back(s.substr(start, s_length-start));

    return res;
}


int main() {
    string s = "ABCDEECDdddddCDFCDGGDCCDCCCDCCDCDCDCDC";
    string p = "CD";
    vector<string> res = KMP_match(s, p);
    for (int i=0; i<res.size(); i++) {
        cout<<res[i]<<" ";
    }
    cout<<endl;
    return 0;
}
