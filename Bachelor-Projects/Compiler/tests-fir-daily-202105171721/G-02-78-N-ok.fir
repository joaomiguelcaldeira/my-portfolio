int ?g(int i)
int *f(int i) -> 9 { if i==0 then f = 0; else f = g(i-1) + i; }
int *g(int i) -> 9 { if i==0 then g = 0; else g = f(i-1) + i; }
int *fir() -> 0 { writeln f(3); }

