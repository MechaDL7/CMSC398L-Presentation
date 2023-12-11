#include <bits/stdc++.h>
using namespace std;
#define MODVALUE 1000000007
#define ll long long

#define FLP(i,n) for(int i = 0; i < n; ++i)
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll answer;
    int tests, n;
    short val, k;
    cin >> tests;
    FLP(t,tests){
        cin >> n >> k;
        answer = 0;
        ll valuesSaw[64] = {0};
        FLP(i,n){
            cin >> val;
            FLP(j,64){
                valuesSaw[val & j] = (valuesSaw[val & j] + valuesSaw[j])%MODVALUE;
            }
            valuesSaw[val] = (valuesSaw[val]+1)%MODVALUE;
        }
        switch(k){
            case 0:{
                answer = valuesSaw[0];
            };break;
            case 1:{
                short vals[] = {1, 2, 4, 8, 16, 32};
                FLP(i,6){
                    answer = (answer+valuesSaw[vals[i]])%MODVALUE;
                }
            };break;
            case 2:{
                short vals[] = {3, 5, 6, 9, 10, 12, 17, 18, 20, 24, 33, 34, 36, 40, 48};
                FLP(i,15){
                    answer = (answer+valuesSaw[vals[i]])%MODVALUE;
                }
            };break;
            case 3:{
                short vals[] = {7, 11, 13, 14, 19, 21, 22, 25, 26, 28, 35, 37, 38, 41, 42, 44, 49, 50, 52, 56};
                FLP(i,20){
                    answer = (answer+valuesSaw[vals[i]])%MODVALUE;
                }
            };break;
            case 4:{
                short vals[] = {15, 23, 27, 29, 30, 39, 43, 45, 46, 51, 53, 54, 57, 58, 60};
                FLP(i,15){
                    answer = (answer+valuesSaw[vals[i]])%MODVALUE;
                }
            };break;
            case 5:{
                short vals[] = {31, 47, 55, 59, 61, 62};
                FLP(i,6){
                    answer = (answer+valuesSaw[vals[i]])%MODVALUE;
                }
            };break;
            case 6:{
                answer = valuesSaw[63];
            };break;
        }
        cout << answer << '\n';
    }
 
    return 0;
}