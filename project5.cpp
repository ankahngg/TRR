#include<bits/stdc++.h>
using namespace std;

const int M = 1e3+6;
int n,m,a,b,c,d,r;
int f[M][M];
pair<int,int> pre[M][M];
vector<pair<int,int>> dsk[M];

void djiktra(int st) {
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({f[st][st],st});
    // priority_queue se luong sap xep theo phan tu first cua pair<int,int>
    // do do f[i][j] se la o vi tri first
    while(!pq.empty()) {
        int u = pq.top().second, c = pq.top().first;
        pq.pop();
        for(auto v : dsk[u]) {
            // dieu kien dijktra
            if(f[st][v.first] > c + v.second) 
                f[st][v.first] = c + v.second,
                pq.push({f[st][v.first],v.first});
        }
    }
}

void solv() {
    // pre[i][j] --> vi tri truoc do cua 2 robot
    for(int i=0;i<=n-1;i++) 
        for(int j=0;j<=n-1;j++) pre[i][j] = {-1,-1};

    queue<pair<int,int>> q;
    // ban dau 2 robot lan luot o vi tri a va b
    q.push({a,b});

    while(!q.empty()) {
        // lay vi tri hien tai cua 2 robot
        int x = q.front().first, y = q.front().second;
        q.pop();
        // th1 : di chuyen robot x, giu nguyen robot y
        // xet tat ca cac dinh ke voi robot x
        for(auto o : dsk[x]) {
            int v = o.first;
            // neu vi tri {v,y} chua duoc toi
            // va khoang cach ngan nhat giua {v,y} > r thi ta push vo q
            if(pre[v][y].first == -1 && f[v][y] > r) q.push({v,y}), pre[v][y] = {x,y};
        }
        // th2 : di chuyen robot y, giu nguyen robot x
        // xet tat ca cac dinh ke voi robot y
        for(auto o : dsk[y]) {
            int v = o.first;
            // neu vi tri {x,v} chua duoc toi
            // va khoang cach ngan nhat giua {x,v} > r thi ta push vo q
            if(pre[x][v].first == -1 && f[x][v] > r) q.push({x,v}), pre[x][v] = {x,y};
        }
    }
    // neu vi tri {c,d} khong co vi truoc do thi chung to khong co cach nao co the den dc {c,d}
    if(pre[c][d].first == -1) cout <<"Khong the !";
    else {
        // truy vet tu {c,d} den {a,b}
        // vi khi truy vet thu tu se bi nguoc lai 
        // nen ta su dung stack
        stack<pair<int,int>> st;
        int ii = c, jj = d;
        st.push({ii,jj});
        while(ii != a || jj != b) {
            pair<int,int> xx = pre[ii][jj];
            st.push(xx);
            ii = xx.first;
            jj = xx.second;    
        }

        // in ra ket qua
        while(!st.empty()) {
            int u = st.top().first;
            int v = st.top().second;
            cout << u<<" "<<v<<" "<<f[u][v]<<"\n";
            st.pop();
        }
    }

}

int main()
{
    freopen("project5_inp.inp","r",stdin);
    cin >> n >> m;
    // nhap du lieu
    for(int i=1;i<=m;i++) {
        int u,v;
        cin >> u >> v >> c;
        dsk[u].push_back({v,c});
        dsk[v].push_back({u,c});
    }
    cin >> a >> b >> c >> d >> r;

    // f[i][j] --> do dai duong di ngan nhat tu dinh i den dinh j
    // Khoi tao mang f[i][j]
    for(int i=0;i<=n-1;i++)
        for(int j=0;j<=n-1;j++) 
            if(i != j) f[i][j] = INT_MAX;
            else f[i][j] = 0;
        
    // djiktra cho moi dinh    
    for(int i=0;i<=n-1;i++) {
        djiktra(i);
    }

    solv();
}