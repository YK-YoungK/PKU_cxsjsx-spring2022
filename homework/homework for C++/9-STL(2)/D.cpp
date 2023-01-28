#include <iostream>
#include <vector>
#include <cstring>
#include <string>
using namespace std;
vector<string> result;
string get_copy();
string get_add();
int get_find();
int get_rfind();
string get_copy()
{
    int n, x, l;
    string s;
    cin >> s;
    if (s == "find")
        n = get_find();
    else if (s == "rfind")
        n = get_rfind();
    else
        n = stoi(s);
    cin >> s;
    if (s == "find")
        x = get_find();
    else if (s == "rfind")
        x = get_rfind();
    else
        x = stoi(s);
    cin >> s;
    if (s == "find")
        l = get_find();
    else if (s == "rfind")
        l = get_rfind();
    else
        l = stoi(s);
    // cout<<n<<" "<<x<<" "<<l<<endl;
    return result[n - 1].substr(x, l);
}
string get_add()
{
    string s1, s2;
    cin >> s1;
    if (s1 == "copy")
        s1 = get_copy();
    else if (s1 == "add")
        s1 = get_add();
    cin >> s2;
    if (s2 == "copy")
        s2 = get_copy();
    else if (s2 == "add")
        s2 = get_add();
    int t1 = 0, t2 = 0;
    int flag = 1;
    // cout<<s1<<endl;
    // cout<<s2<<endl;
    t1 = stoi(s1);
    t2 = stoi(s2);
    string s1_ = to_string(t1);
    string s2_ = to_string(t2);
    if (s1 != s1_ || s2 != s2_)
        flag = 0;
    if (flag == 0)
        return s1 + s2;
    else
    {
        if (t1 >= 0 && t1 <= 99999 && t2 >= 0 && t2 <= 99999)
        {
            string r;
            r = to_string(t1 + t2);
            return r;
        }
        else
            return s1 + s2;
    }
}
int get_find()
{
    int r;
    string s;
    cin >> s;
    if (s == "copy")
        s = get_copy();
    else if (s == "add")
        s = get_add();
    string op;
    cin >> op;
    if (op == "find")
        r = get_find();
    else if (op == "rfind")
        r = get_rfind();
    else
        r = stoi(op);
    int tmp;
    tmp = result[r - 1].find(s);
    if (result[r - 1].find(s) == string::npos)
        tmp = result[r - 1].length();
    return tmp;
}
int get_rfind()
{
    int r;
    string s;
    cin >> s;
    if (s == "copy")
        s = get_copy();
    else if (s == "add")
        s = get_add();
    string op;
    cin >> op;
    if (op == "find")
        r = get_find();
    else if (op == "rfind")
        r = get_rfind();
    else
        r = stoi(op);
    int tmp;
    tmp = result[r - 1].rfind(s);
    if (result[r - 1].rfind(s) == string::npos)
        tmp = result[r - 1].length();
    return tmp;
}
void get_insert()
{
    string s;
    int n = 0, x = 0;
    cin >> s;
    if (s == "copy")
        s = get_copy();
    else if (s == "add")
        s = get_add();
    string op;
    cin >> op;
    if (op == "find")
        n = get_find();
    else if (op == "rfind")
        n = get_rfind();
    else
        n = stoi(op);
    cin >> op;
    if (op == "find")
        x = get_find();
    else if (op == "rfind")
        x = get_rfind();
    else
        x = stoi(op);
    result[n - 1].insert(x, s);
    return;
}
void get_reset()
{
    string s;
    int n = 0;
    cin >> s;
    if (s == "copy")
        s = get_copy();
    else if (s == "add")
        s = get_add();
    string op;
    cin >> op;
    if (op == "find")
        n = get_find();
    else if (op == "rfind")
        n = get_rfind();
    else
        n = stoi(op);
    result[n - 1] = s;
    return;
}
void get_print()
{
    int n = 0;
    string op;
    cin >> op;
    if (op == "find")
        n = get_find();
    else if (op == "rfind")
        n = get_rfind();
    else
        n = stoi(op);
    cout << result[n - 1] << endl;
    return;
}
int main()
{
    int n = 0;
    cin >> n;
    string s;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        result.push_back(s);
    }
    while (1)
    {
        cin >> s;
        if (s == "copy")
            get_copy();
        else if (s == "add")
            get_add();
        else if (s == "find")
            get_find();
        else if (s == "rfind")
            get_rfind();
        else if (s == "insert")
            get_insert();
        else if (s == "reset")
            get_reset();
        else if (s == "print")
            get_print();
        else if (s == "printall")
        {
            for (int i = 0; i < n; i++)
                cout << result[i] << endl;
        }
        else if (s == "over")
            break;
    }
    return 0;
}