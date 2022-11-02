int x;
int *fir() -> 0 {
  x = 1;
  while x <= 50 do {
     if x == 10 then leave;
     x = x + 1;
  }
  write x;
}

