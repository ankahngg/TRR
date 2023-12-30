#include<bits/stdc++.h>
using namespace std;

const int M = 1e5+6;
int edges,q,o,ans;
int pre[M],post[M],cnt[30],group[M];
map<string,int> mp;
bool cx[M];
string str[M];
vector<int> dsk[M], dsk2[M];

bool check(int i, int j, string xx, string yy) {
    string a,b;
    int error = 0;
    // cai nay de check test thoi
    // string a,b la 2 string ta se kiem tra co canh noi giua 2 string nay ko
    if(i == -1) {
        a = xx;
        b = yy;
    }
    else {
        a = str[i];
        b = str[j];
    }
    //dem so luong chu cai trong 4 chu cuoi cua string a
    for(int i=1;i<=4;i++) cnt[a[i]-'a'] ++;
    for(int i=0;i<=4;i++) {
        int nm = b[i]-'a';
        // kiem tra chu cai trong b co trong 4 chu cuoi cua string a khong 
        // neu khong error ++
        if(cnt[nm]) cnt[nm] --;
        else error ++;
        
        // neu so chu cai khong co trong 4 chu cuoi cua string a > 1 ==> khong co canh noi giua string a va b
        if(error > 1) {
            // reset mang cnt de dung cho nhung lan tiep theo
            for(int j=1;j<=4;j++) if(cnt[a[j]-'a']) cnt[a[j]-'a'] --;
            return false;
        }
    }
    // reset mang cnt de dung cho nhung lan tiep theo
    for(int j=1;j<=4;j++) if(cnt[a[j]-'a']) cnt[a[j]-'a'] --;

    return true;
}

void dfs(int u) {
    // dfs nhu bt
    // group de gan nhom thanh phan lien thong manh cho dinh u
    group[u] = ans;
    cx[u] = false;
    for(auto v : dsk[u]) if(cx[v]) {
        dfs(v);
    }
}

void dfs2(int u) {
    // dfs nhu bt
    pre[u] = ++o;
    for(auto v : dsk2[u]) if(pre[v] == -1) dfs2(v);
    post[u] = ++o;
}

int bfs(int a,int b) {
    // bfs nhu 4a
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

    /// a)
    // nhap string
    int cnt=0;
    while(true) {
        string s;
        cin >> s;
        if(s == "1") break;
        str[++cnt] = s;
        mp[s] = cnt;
    }

    // check xem co canh noi giua string i va string j khong
    // dsk --> do thi G
    // dsk2 --> do thi G' (do thi nguoc lai voi G)
    // thuat toan giong y het trong slide
    for(int i=1;i<=cnt;i++) 
        for(int j=1;j<=cnt;j++) { 
            if(i != j) if(check(i,j,"","")) dsk[i].push_back(j), dsk2[j].push_back(i), edges ++;
        }
    
    // khoi tao pre va post
    for(int i=1;i<=cnt;i++) pre[i] = post[i] = -1;
    // tim pre va post trong do thi G'
    for(int i=1;i<=cnt;i++) if(pre[i] == -1) dfs2(i);
    // sap xep post trong do thi G' 
    vector<pair<int,int>> sortPost;
    for(int i=1;i<=cnt;i++) sortPost.push_back({post[i],i});
    sort(sortPost.begin(),sortPost.end());
    // dinh co post lon nhat cua G' se la dinh thuoc thanh phan lien thong hut cua G
    for(int i=1;i<=cnt;i++) cx[i] = true;
    for(int i = sortPost.size()-1;i>=0;i--) {
        int u = sortPost[i].second;
        // dfs de tim tat ca cac dinh thuoc thanh phan lien thong hut do
        if(cx[u]) ans ++,dfs(u);
    }

    
    cout << "So dinh : "<<cnt<<"\n";
    cout << "So canh : "<<edges<<"\n";
    cout << "So thanh phan lien thong manh : "<<ans<<"\n";

    /// b)
    string a,b;
    cin >> a >> b;
    int u = mp[a], v = mp[b];
    if(group[u] == group[v]) cout <<a<<" va "<<b<<" co cung thanh phan lien thong manh"<<"\n";
    else cout <<a<<" va "<<b<<" khong cung thanh phan lien thong manh"<<"\n";


    /// c)
    cin >> a >> b;
    for(int i=1;i<=cnt;i++) cx[i] = true;
    u = mp[a], v = mp[b];
    int kq = bfs(u,v);
    if(kq == -1) cout <<"Khong co duong du tu "<<a<<" --> "<<b<<"\n";
    else cout << "Do dai duong di ngan nhat tu "<<a<<" --> "<<b<<" la "<<kq<<"\n";

}