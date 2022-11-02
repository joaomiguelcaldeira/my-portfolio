int y;
int x;
int *fir() -> 0 {
  y = 1;
  while y <= 3 do {
    x = y;
    while x <= 50 do {
      if y == 2 then { y = y + 1; restart 2; }
      if x == 10 then leave;
      x = x + 1;
    }
    writeln x;
    y = y + 1;
  }
}

