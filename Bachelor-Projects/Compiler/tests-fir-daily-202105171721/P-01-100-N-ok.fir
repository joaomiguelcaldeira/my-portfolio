<float> *main(<float> p) { main = 1 + p; }
int *fir() -> 0 {
  <int> p = [3];
  <float> q = [3];
  p[0] = 3;
  p[1] = 2;
  p[2] = 61;
  q[0] = p[1];
  q[1] = p[2];
  q[2] = p[0];
  writeln (q+1)[0];
}

