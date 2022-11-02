int *x = 10;
void f() { int x = 3; write x; }
int *fir() -> 0 {
  f();
  writeln x;
}

