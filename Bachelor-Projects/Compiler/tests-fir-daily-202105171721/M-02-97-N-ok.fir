<float> main(<float> p) { main = 1 + p; }
int *fir() -> 0 {
  <float> p = [3];
  <float> q;
  p[0] = 3.1;
  p[1] = 2.1;
  p[2] = 6.1E1;
  q = main(main(p));
  writeln q[0];
}

