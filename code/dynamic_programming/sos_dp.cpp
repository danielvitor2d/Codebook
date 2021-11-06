#include <bits/stdc++.h>
using namespace std;

// version O(4^n)
void SumOverSubsetV1(vector<int> &a, int n) { // vetor de 2^n posições, n
  vector<int> sos(1 << n, 0);
  for (int mask = 0; mask < (1 << n); ++mask) {
    for (int submask = 0; submask < (1 << n); ++submask) {
      if ((mask & submask) == submask) {
        sos[mask] += a[submask];
      }
    }
  }
  for (int i = 0; i < (1 << n); ++i) {
    cout << sos[i] << ' ';
  } cout << '\n';
}

void SumOverSubsetV2(vector<int> &a, int n) { // vetor de 2^n posições, n
  vector<int> sos(1 << n, 0);
  for (int mask = 0; mask < (1 << n); ++mask) {
    sos[mask] = a[0];
    for (int submask = mask; submask > 0; submask=(submask-1)&mask) {
      sos[mask] += a[submask];
    }
  }
  for (int i = 0; i < (1 << n); ++i) {
    cout << sos[i] << ' ';
  } cout << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n; cin >> n;
  vector<int> a(1 << n);
  for (int &x : a) {
    cin >> x;
  }
  SumOverSubsetV1(a, n);
  SumOverSubsetV2(a, n);
}