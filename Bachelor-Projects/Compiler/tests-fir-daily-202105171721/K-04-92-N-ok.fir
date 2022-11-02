<float> f;
float d = 4;
int *fir() -> 0 {
  int i;
  f = [7];
  { i = 0; while i < 6 do { f[i] = d; i = i + 1; } }
  f[i] = d * d;
  { int j = 0; while j < 7 do { write f[j]; j = j + 1; } }
}

