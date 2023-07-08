#include<bits/stdc++.h>
using namespace std;
#define ll int
#define pb push_back
#define F first
#define S second
#define MP make_pair

vector<string>a,b,c;
map<char,pair<ll,ll>>coor;
string tolower(string key)
{
    int i;
    for (i = 0; i < key.size(); i++) 
    {
        if (key[i] > 64 && key[i] < 91)
            key[i] += 32;
    }
    return key;
}
string removespace(string plain)
{
    string temp=plain;
    plain="";
    for (ll i=0;i<temp.size();i++)
        if (temp[i]!= ' ')
            plain+=temp[i];
    return plain;
}
string removej(string str)
{
    for(ll i=0;i<str.size();i++)
    {
        if(str[i]=='j')
        {
            str[i]='i';
        }
    }
    return str;
}
string unique_(string str)
{
    string temp=str;
    str="";
    map<char,ll>mp;
    for(ll i=0;i<temp.size();i++)
    {
        mp[temp[i]]++;
        if(mp[temp[i]]==1)
        {
            str+=temp[i];
        }
        if(mp.size()==26)
        {
            break;
        }
    }
    return str;
}
void generatetable(string key)
{
    ll n=key.size();
    ll x=0,y=0,i=0;
    map<char,ll>mp;
    while(i<n)
    {
        a[x]+=key[i];
        mp[key[i]]=1;
        y++;
        if(y==5)
        {
            y=0;
            x++;
        }
        i++;
    }
    for(ll i=0;i<26;i++)
    {
        char ch='a'+i;
        if(ch=='j')continue;
        if(mp[ch]==0)
        {
            a[x]+=ch;
            y++;
            if(y==5)
            {
                y=0;
                x++;
            }
        }
    }
}
void sep(string str,ll idx)
{
    ll n=str.size();
    if(idx==n)
    {
        return;
    }
    string temp;
    if(idx<=(n-2))
    {
        if(str[idx]!=str[idx+1])
        {
            temp.pb(str[idx]);
            temp.pb(str[idx+1]);
            b.pb(temp);
            sep(str,idx+2);
        }
        else
        {
            temp.pb(str[idx]);
            temp.pb('x');
            b.pb(temp);
            sep(str,idx+1);
        }
    }
    else
    {
        temp.pb(str[idx]);
        temp.pb('x');
        b.pb(temp);
        sep(str,idx+1);
    }
    return;
}
pair<char,char> find1(char x,char y)
{
    pair<char,char> ch;
    pair<ll,ll>x1,x2;
    x1=coor[x];
    x2=coor[y];
    if(x1.F==x2.F)
    {
        x1.S=(x1.S+1)%5;
        x2.S=(x2.S+1)%5;
    }
    else if(x1.S==x2.S)
    {
        x1.F=(x1.F+1)%5;
        x2.F=(x2.F+1)%5;
    }
    else
    {
        swap(x1.S,x2.S);
    }
    ch.F=a[x1.F][x1.S];
    ch.S=a[x2.F][x2.S];
    return ch;
}
void encrypt()
{
    c.resize(b.size());
    for(ll i=0;i<b.size();i++)
    {
        pair<char,char> p=find1(b[i][0],b[i][1]);
        string temp;
        temp.pb(p.F);
        temp.pb(p.S);
        c.pb(temp);
    }
}
pair<char,char> find2(char x,char y)
{
    pair<char,char> ch;
    pair<ll,ll>x1,x2;
    x1=coor[x];
    x2=coor[y];
    if(x1.F==x2.F)
    {
        x1.S=(x1.S-1+5)%5;
        x2.S=(x2.S-1+5)%5;
    }
    else if(x1.S==x2.S)
    {
        x1.F=(x1.F-1+5)%5;
        x2.F=(x2.F-1+5)%5;
    }
    else
    {
        swap(x1.S,x2.S);
    }
    ch.F=a[x1.F][x1.S];
    ch.S=a[x2.F][x2.S];
    return ch;
}
void decrypt()
{
    c.resize(b.size());
    for(ll i=0;i<b.size();i++)
    {
        pair<char,char> p=find2(b[i][0],b[i][1]);
        string temp;
        temp.pb(p.F);
        temp.pb(p.S);
        c.pb(temp);
    }
}
void solve()
{
    string key,str;
    cout<<"enter key and message"<<endl;
    cin>>key>>str;
    key=tolower(key);
    str=tolower(str);
    str=removespace(str);
    key=removej(key);
    key=unique_(key);
    str=removej(str);
    a.resize(5);
    generatetable(key);
    for(ll i=0;i<5;i++)
    {
        for(ll j=0;j<5;j++)
        {
            coor[a[i][j]]=MP(i,j);
        }
    }
    sep(str,0);
    ll f;
    cout<<"encrypt or decrypt"<<endl;
    cin>>f;
    // if f is 1 encrypt or decrypt
    if(f)encrypt();
    else decrypt();
    for(auto it:c)
    {
        cout<<it;
    }
}
int main() {
    ll t;
    t=1;
    // cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}