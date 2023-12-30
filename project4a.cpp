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
    // dem -->  the hien so luong sai khac giua 2 string
    int dem = 0;
    for(int i=0; i<=a.length()-1;i++) {
        if(a[i] != b[i]) dem ++;
        if(dem > 1) return false;
    }
    // neu dem == 1 (sai khac duy nhat 1) thi co canh noi giua 2 string
    if(dem == 1) return true;
    return false;
}

void dfs(int u) {
    // dfs nhu binh thuong
    cx[u] = false;
    for(auto v : dsk[u]) if(cx[v]) {
        dfs(v);
    }
}

int bfs(int a,int b) {
    // mot hang doi chua 2 phan tu
    // phan tu 1 chua dinh (vertices), phan tu thu 2 chua khoang cach
    queue<pair<int,int>> q;
    q.push({a,1});
    cx[a] = false;
    while(!q.empty()) {
        int u = q.front().first, c = q.front().second; q.pop();
        // neu u == b (hay a da toi dc b thi thoat va chac chan duong di day la ngan nhat)
        if(u == b) return c;
        // duyet cac dinh ke cua u de bfs
        for(auto v : dsk[u]) if(cx[v]) q.push({v,c+1}), cx[v] = false;
    }
    // neu khong di toi dc b thi return -1
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    freopen("input.inp","r",stdin);

    // nhap string
    int cnt=0;
    while(true) {
        string s;
        cin >> s;
        if(s == "1") break;
        str[++cnt] = s;
        mp[s] = cnt;
    }

    // check xem string nao den duoc string nao
    for(int i=1;i<=cnt;i++) 
        for(int j=i;j<=cnt;j++) {
            // neu string i den duoc string i thi luu vao dsk (danh sach ke)
            if(check(i,j)) dsk[i].push_back(j), dsk[j].push_back(i), edges ++;
        }
    
    // khoi tao mang cx
    for(int i=1;i<=cnt;i++) cx[i] = true;
    int res=0;
    // dfs de tim mien lien thong
    for(int i=1;i<=cnt;i++) if(cx[i]) res ++, dfs(i);

    cout << "So dinh : "<<cnt<<"\n";
    cout << "So canh : "<<edges<<"\n";
    cout << "So thanh phan lien thong : "<<res<<"\n";


    string a,b;
    cin >> a >> b;
    // u,v --> so thu tu cua string a va string b
    int u = mp[a], v = mp[b];
    // khoi tao mang cx
    for(int i=1;i<=cnt;i++) cx[i] = true;
    // o day dung bfs thay vi dijktra do tat ca cac canh deu khong co trong so
    // (hay co the noi tat ca cac canh co trong so giong nhau)
    int ans = bfs(u,v);
    if(ans == -1) {
        cout <<"Khong co duong di tu "<<a<<" --> "<<b<<"\n";
    }
    else cout << "Do dai duong di ngan nhat tu "<<a<<" --> "<<b<<" la "<<ans<<"\n";
    
}