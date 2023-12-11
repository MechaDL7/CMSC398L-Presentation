# CMSC398L Presentation
Jeffrey Jiang
## Problem: Don't Blame Me
Source: Codeforces 1829H

### Problem Statement
Given an array $a$ consiting of $n$ positive integers, count the number of **non-empty** suvsequences for which the bitwise $\mathsf{AND}$ of the elements in the subsequence has exactly $k$ set bits in its binary representation. The answer may be large, so output it modulo $10^9+7$.

Recall that the subsequence of an array $a$ is a sequence that can be obtained from $a$ by removing some (possibly, zero) elements. For example, $[1,2,3]$, $[3]$, $[1,3]$ are subsequences of $[1,2,3]$, but $[3,2]$ and $[4,5,6]$ are not.

#### Input
Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \leq t \leq 10^4$). The description of the test cases follows.

The first line of each test case consists of two integers $n$ and $k$ ($1 \leq n \leq 2 \cdot 10^5$, $0 \leq k \leq 6$) — the length of the array and the number of set bits that the bitwise $\mathsf{AND}$ the counted subsequences should have in their binary representation.

The second line of each test case consists of $n$ integers $a_i$ ($0 \leq a_i \leq 63$) — the array $a$.

It is guaranteed that the sum of $n$ over all test cases doesn't exceed $2 \cdot 10^5$.

#### Output
For each test case, output a single integer — the number of subsequences that have exactly $k$ set bits in their bitwise $\mathsf{AND}$ value's binary rerpesentation. The answer may be large, so output it modulo $10^9+7$.

### Analysis
For this problem, you are given an array $a$ and asked to find the number of subsequences of $a$ such that the bitwise $\mathsf{AND}$ of the members of the subsequences results in a number with $k$ set bits. 

Here are a couple of notable details of the problem, every member of $a$ $a_i$ is between $0$ and $63$ (inclusive) and $k$ is no more than $6$. Because we are dealing with bitwise $\mathsf{AND}$ operations, this means the associated set bits from a subsequence can't be larger than $63$ since bitwise $\mathsf{AND}$ operations can only remove bits. For this reason, given a $k$ value, we can think of the problem as summing up the number of subsequences that, after applying the bitwise $\mathsf{AND}$ operations, results in a number with $k$ set bits. For each $k$, these are:

$0$: $[0]$\
$1$: $[1, 2, 4, 8, 16, 32]$\
$2$: $[3, 5, 6, 9, 10, 12, 17, 18, 20, 24, 33, 34, 36, 40, 48]$\
$3$: $[7, 11, 13, 14, 19, 21, 22, 25, 26, 28, 35, 37, 38, 41, 42, 44, 49, 50, 52, 56]$\
$4$: $[15, 23, 27, 29, 30, 39, 43, 45, 46, 51, 53, 54, 57, 58, 60]$\
$5$: $[31, 47, 55, 59, 61, 62]$\
$6$: $[63]$

Now, the question remains, how do we count the subsequences that results in these numbers?\
For this, we can use a dp array that will count the number of subsequences for each number between $0$ and $63$ (inclusive). To explain how this will work, let's say at some point in the program, we have found $s_0, s_1, \dots, s_{62}, s_{63}$, where $s_i$ is represents the number of subsequences that would result in a value of $i$, and we are considering the outcome from introducing a new integer $a_j$ into the subsequences. If we do so to any of the subsequences $s_i$, what we will get is a new subsequence for $s_{i\&a_j}$. This is because applying bitwise $\mathsf{AND}$ operations to the elements of $s_i$ results in $i$, which means adding in $a_j$ will turn it into $i\&a_j$. Since none of these subsequences previously had element $a_j$, all of these subsequences we would create by adding in $a_j$ would be considered uncounted subsequences that we would need to add to our count. 

This means, for each subsequence count $s_i$, the new subsequence count for $s_{i\&a_j}$ would be $s'_{i\&a_j} = s_{i\&a_j} + s_i$ since we can make $s_i$ new subsequences by adding $a_j$ to them. In order to avoid adding in $a_j$ multiple times into some subsequences, we would want to update the counts in ascending order because bitwise $\mathsf{AND}$ operations can only take away bits and not add them (meaning the resulting number will less than or equal to the previous number), so going in ascending order means we wouldn't ever be using a subsequence count that already includes subsequences with $a_j$ in them.

After updating these counts, we would add $1$ to the subsequence $s_{a_j}$ to account for the subsequence with only $a_j$

Using these ideas, we can now design an algorithm to solve this problem.

#### Algorithm Outline
For each testcase $t$ 
1. Get the values for $n$ and $k$ 
2. Initialize an empty array $s$ of length 64, whose indicies will correspond to each subsequence count $s_i$
3. For each element in $a$
   1. Update $s_{i\&a_j}$ to be $s_{i\&a_j}+s_i$, for $i = 0$ to $63$.
   2. Add $1$ to $s_{a_j}$
4. Return the sum of all $s_i$ such that $i$ has $k$ set bits.

This algorithm uses: \
$\Theta(n)$ Time: Doing a set amount of operations for each element $a_i$  
$\Theta(1)$ Space: All space used is due to the max element size $63$, the max $k$ value $6$, and the number of individual variables (i.e. $n$, $k$, $t$, current $a_i$, output), which all doesn't scale with the size of $n$. 

#### C++ Implementation
```c++
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
```