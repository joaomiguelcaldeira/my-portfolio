<float> f(<float> p) { f = p; f[2] = 1; }
int *fir() -> 0 {
  <float> p = [3];
  p[0] = 100;
  p[1] = 40;
  p[2] = 0;
  f(p);
  writeln p[2];
}

