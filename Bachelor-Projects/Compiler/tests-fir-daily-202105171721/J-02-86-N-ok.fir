void f(int i) @ { int x; x = i; }
{ x = 4; }
>> { write x; }
int *fir() -> 0 { f(3); }

