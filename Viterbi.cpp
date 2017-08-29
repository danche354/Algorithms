#include <iostream>
#include <vector>
#include <string>

using namespace std;

// with no emission value
vector<vector<int> > viterbi(vector<vector<int> >& weights) {
    // levels denotes how many steps are there
    int levels = 7;

    // states
    int states = weights.size();

    // record previous minimum path
    vector<int> dp(states, 0);

    // record current minimum path and then assign to `dp` for next step
    vector<int> tmp(states, 0);

    // path record the previous best record in every step
    // `-1` denotes start point and end point
    // path: `(levels+2)*states`
    vector<vector<int> > path(levels+2, vector<int>(states, 0));
    for (int i=0; i<states; i++) {
        path[0][i] = -1;
        path[levels][i] = i; 
        path[levels+1][i] = -1;
    }

    for (int i=1; i<levels; i++) {

        // for (int x=0; x<states; x++) {
        //     cout<<dp[x]<<" ";
        // }
        // cout<<endl;

        for (int j=0; j<states; j++) {
            int minimum = dp[0]+weights[j][0];
            for (int k=1; k<states; k++) {
                if (dp[k]+weights[j][k]<minimum) {
                    path[i][j] = k;
                    minimum = dp[k]+weights[j][k];
                }
            }
            tmp[j] = minimum;
        }

        for (int j=0; j<states; j++) {
            dp[j] = tmp[j];
        }
    }

    // for (int i=0; i<states; i++) {
    //     cout<<dp[i]<<" ";
    // }
    // cout<<endl;

    return path;
}



int main() {

    vector<vector<int> > weights;
    int rows1[4] = {1,2,3,4};
    int rows2[4] = {2,3,1,5};
    int rows3[4] = {4,3,2,8};
    int rows4[4] = {6,9,0,1};
    weights.push_back(vector<int>(rows1, rows1+4));
    weights.push_back(vector<int>(rows2, rows2+4));
    weights.push_back(vector<int>(rows3, rows3+4));
    weights.push_back(vector<int>(rows4, rows4+4));
    vector<vector<int> > path = viterbi(weights);
    int states = path[0].size();
    int levels = path.size() - 2;

    vector<int> pathway;
    for (int i=0; i<states; i++) {
        pathway.push_back(path[levels+1][i]);
        pathway.push_back(path[levels][i]);
        int k = i;
        for (int j=levels-1; j>=0; j--) {
            pathway.push_back(path[j][k]);
            k = path[j][k];
        }
        // pathway.push_back(-1);
        for (int k=levels; k>=0; k--) {
            cout<<pathway[k]<<" ";
        }
        cout<<endl;
        pathway.clear();
    }

    return 0;
}