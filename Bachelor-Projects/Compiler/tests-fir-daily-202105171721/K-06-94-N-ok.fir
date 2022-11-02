float f;
int *fir() -> 0 {
  <float> p = [3];
  <float> q = [3];
  p[1] = 3;
  q[2] = 6;
  f = (q+1)[1] - p[1];
  writeln f;
}

