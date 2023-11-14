#include<bits/stdc++.h>
#define fo(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

int n;
bool fl = false;
string s;
vector<string> v,a;
vector<string> kq;
map<string,float> m;
map<string,int> op;

// bien string thanh number
void convert(string x) {
    vector<int> num;
    int pos=x.length()-1;
    fo(i,0,x.length()-1) {
        if(x[i] == '.') {pos = i; continue;}
        int o = x[i]-'0';
        num.push_back(o);
    }
    int lt = pow(10,x.length()-1-pos);
    
    reverse(num.begin(),num.end());
    float number = 0;
    fo(i,0,num.size()-1) {
        number += 1.0*pow(10,i)*num[i];
    }

    m[x] = 1.0*number/lt;
    // giá trị số của string x là m[x]
}

void precal() {
    op["+"] = 1;
    op["-"] = 1;
    op["*"] = 2;
    op["/"] = 2;
    op[")"] = 3;
    op["("] = 3;
    // độ ưu tiên của dấu
}

int main()
{
    precal();

    cin >> s; 
    fo(i,0,s.length()-1) {
        if(s[i] == '.') fl = true;
        string str = "";
        str += s[i];
        a.push_back(str);
    }

    fo(i,0,a.size()-1) {
        int j = i;
        // a[i] khong la toan tu
        if(!op.count(a[i])) {
            string str = "";
            while(j+1<=a.size()-1 && !op.count(a[j+1])) j ++;
            fo(k,i,j) str += a[k];
            convert(str);
            v.push_back(str);
            i = j;
        }
        // a[i] la toan tu
        else {
            v.push_back(a[i]);
        }
    }

    // for(auto x : v) {
    //     cout << x<<" ";
    //     if(m.count(x)) cout << m[x]<<"\n";
    //     else cout <<"op"<<"\n";
    // }

    stack<string> st;
    for(auto x : v) {
        if(m.count(x)) kq.push_back(x);
        else {
            if(x == "(") st.push(x);
            else if(x == ")") {
                while(!st.empty() && st.top() != "(") {
                    kq.push_back(st.top());
                    st.pop();
                }
                st.pop();
            }
            else {
                while(!st.empty() && op[st.top()] >= op[x]) kq.push_back(st.top()), st.pop();
                st.push(x);
            }
        }
    }

    while(!st.empty()) kq.push_back(st.top()), st.pop();

    // for(auto x : kq) 
    //     if(m.count(x)) cout << m[x]<<" ";
    //     else cout << x<<" ";
    // cout <<"\n";

    stack<float> num_st;
    for(auto x : kq) {
        if(m.count(x)) num_st.push(m[x]);
        else {
            float num1 = num_st.top(); num_st.pop();
            float num2 = num_st.top(); num_st.pop();
            float ans;
            if(x == "+") ans = num2 + num1;
            if(x == "-") ans = num2 - num1;
            if(x == "*") ans = num2 * num1;
            if(x == "/") ans = num2 / num1;
           // cout << num1<<" "<<num2<<" "<<ans<<"\n";
            num_st.push(ans);
        }
    }
    
    if(fl) cout << fixed << setprecision(1) << num_st.top();
    else {
        if(floor(num_st.top()) != num_st.top()) cout << fixed << setprecision(1) << num_st.top();
        else cout << fixed << setprecision(0) << num_st.top(); 
    }
}