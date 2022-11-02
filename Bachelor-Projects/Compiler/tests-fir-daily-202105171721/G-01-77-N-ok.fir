int f(int i) {
  if i == 0 then f = 0; else { f = f(i-1) + i; return }
  f = 9;
}
int *fir() -> 0 { writeln f(3); }

