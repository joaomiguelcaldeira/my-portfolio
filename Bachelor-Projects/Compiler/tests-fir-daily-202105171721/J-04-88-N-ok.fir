void f(int i) @ { int x; x = i; }
{ x = 5; return }
>> { write x; }
int *fir() -> 0 { f(3); write 'a'; }

