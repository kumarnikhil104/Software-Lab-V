#include<bits/stdc++.h>
#define Cost dp[{a, {v, c}}]
using namespace std;

map<pair<int ,pair<vector<int >, int > >, int > dp;

int path[10];

void print(int n){
    
    map<pair<int ,pair<vector<int >, int > >, int > :: iterator it;

    cout << "\n" ;

    for(int j = 0; j < n; j++){
        for (it = dp.begin(); it !=dp.end() ; it++)
        {   
            if(it -> first.second.first.size() != j)
                continue;
            cout << "Cost( " << it -> first.first << " ,{";
            for(int i = 0; i < it -> first.second.first.size(); i++){
                if(i == 0)
                    cout << it -> first.second.first[i] ;
                else
                    cout << ", " << it -> first.second.first[i] ;
            }
            cout << "}, 1) = " << dp[{it -> first.first , {it -> first.second.first, 1}}] << "\n";
                        
        }
        cout << "\n";
    }
}

void set_path(int a, vector<int >v, int c, int index, int** dist){
    int i;
    for(i = 0; i < v.size(); i++)
    {
        vector<int > v2 = v;
        v2.erase(v2.begin() + i);
        if(Cost == dist[a][v[i]] + dp[{v[i], {v2, c}}])
        {
            path[index] = v[i];
            set_path(v[i], v2, c, index+1, dist);
        }
    }    
}

int TSP(int a, vector<int >v, int c, int ** dist)
{
    if(Cost)
        return Cost;
    
    Cost = 10000;
    int min_vertex;

    if(v.size() == 0)
        Cost = dist[a][c];
    
    else{
        for(int i = 0; i < v.size(); i++){

            if(dist[a][v[i]]){
                
                vector<int > v2 = v;
                v2.erase(v2.begin() + i);
                Cost =  min(Cost, dist[a][v[i]] + TSP(v[i], v2, c, dist));
            }
        }
    }
    return Cost;
}

int main()
{
    int n, i, j, ans;
    vector<int > v;
    cin>>n;
    int *dist = (int *) malloc(sizeof(int) * (n + 1));
    for(i=1;i<=n;i++)
        dist[i] = (int *) malloc(sizeof(int) * n);

    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            cin >> dist[i][j];
        
    for(i=2;i<=n;i++)
        v.push_back(i);

    ans = TSP(1, v, 1, dist);
    print(n);    
    cout << "The shortest distance is " << ans << "\n";
    set_path(1, v, 1, 0, dist);

    cout<<endl<<"The Path is 1-->";
    for(i=0;i<n-1;i++)
        cout << path[i] << "-->";
    cout<<"1\n";
}

/*
4 
0 10 15 20 
5 0 4 10 
6 13 0 12 
8 0 9 0

5
0 24 11 10 9
8 0 2 5 11 
26 12 0 8 7
11 23 24 0 6
5 4 8 10 0

3
0 1 10
1 0 3
2 3 0

4 
0 4 1 3
4 0 2 1
1 2 0 5
3 1 5 0
*/
