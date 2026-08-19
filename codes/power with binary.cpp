#include<iostream>
using namespace std;

double mypow(int x, int n)
{
    if(n==0) return 1.0;
    if(x==0) return 0.0;
    if(n%2==0 && x==-1) return 1.0;
    if(n%2!=0 && x==-1) return -1.0;

    double base = static_cast<double>(x);
    long long exponent = static_cast<long long>(n); // fix overflow issue
    if(n < 0)
    {
        base = 1.0 / base;
        exponent = -exponent; // safe because it's now long long
    }

    double ans = 1.0;
    while(exponent > 0)
    {
        if(exponent % 2 == 1)
        {
            ans *= base;
        }
        base *= base;
        exponent /= 2;
    }
    return ans;
}
int main() {
    cout << mypow(2, 10) << endl;    // 1024
    cout << mypow(2, -2) << endl;    // 0.25
    cout << mypow(-1, 5) << endl;    // -1
    cout << mypow(-1, 6) << endl;    // 1
    cout << mypow(0, 10) << endl;    // 0
    cout << mypow(5, 0) << endl;     // 1
    return 0;
}
