#include<bits/stdc++.h>
using namespace std;

const int M = 1e5+6;
int edges=0;
map<string,int> mp;
bool cx[M];
string str[M];
vector<int> dsk[M];

bool check(int i, int j) {
    string a = str[i];
    string b = str[j];
    int dem = 0;
    for(int i=0; i<=a.length()-1;i++) {
        if(a[i] != b[i]) dem ++;
        if(dem > 1) return false;
    }
    if(dem == 1) return true;
    return false;
}

void dfs(int u) {
    cx[u] = false;
    for(auto v : dsk[u]) if(cx[v]) {
        dfs(v);
    }
}

int bfs(int a,int b) {
    queue<pair<int,int>> q;
    q.push({a,1});
    cx[a] = false;
    while(!q.empty()) {
        int u = q.front().first, c = q.front().second; q.pop();
        if(u == b) return c;
        for(auto v : dsk[u]) if(cx[v]) q.push({v,c+1}), cx[v] = false;
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    freopen("input.inp","r",stdin);

    int cnt=0;
    while(true) {
        string s;
        cin >> s;
        if(s == "1") break;
        str[++cnt] = s;
        mp[s] = cnt;
    }
    for(int i=1;i<=cnt;i++) 
        for(int j=i;j<=cnt;j++) {
            if(check(i,j)) dsk[i].push_back(j), dsk[j].push_back(i), edges ++;
        }
    
    for(int i=1;i<=cnt;i++) cx[i] = true;
    int res=0;
    for(int i=1;i<=cnt;i++) if(cx[i]) res ++, dfs(i);

    cout << "So dinh : "<<cnt<<"\n";
    cout << "So canh : "<<edges<<"\n";
    cout << "So thanh phan lien thong : "<<res<<"\n";


    string a,b;
    cin >> a >> b;
    int u = mp[a], v = mp[b];
    for(int i=1;i<=cnt;i++) cx[i] = true;
    int ans = bfs(u,v);
    if(ans == -1) {
        cout <<"Khong co duong di tu "<<a<<" --> "<<b<<"\n";
    }
    else cout << "Do dai duong di ngan nhat tu "<<a<<" --> "<<b<<" la "<<ans<<"\n";
    
}