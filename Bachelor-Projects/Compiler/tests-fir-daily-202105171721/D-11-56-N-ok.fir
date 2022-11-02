int y;
int x;
int *fir() -> 0 {
  y = 1;
  while y <= 3 do {
    x = y;
    while x <= 50 do {
      if x == 10 then leave;
      x = x + 1;
    }
    writeln x;
    y = y + 1;
  }
}

