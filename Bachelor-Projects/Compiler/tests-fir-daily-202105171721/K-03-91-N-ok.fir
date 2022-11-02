<float> f;
int *fir() -> 0 {
  int n = 4;
  <float> f = [n];
  { int i = 0; while i < n do { f[i] = 2;   i = i + 1; } }
  { int j = 0; while j < n do { write f[j]; j = j + 1; } }
  write '~n';
  { int k = 0; while k < n do { f[k] = 6/f[k]; k = k + 1; } }
  { int l = 0; while l < n do { write f[l];    l = l + 1; } }
}

