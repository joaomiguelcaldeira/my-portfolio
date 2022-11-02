int x;
int y;
int *fir() -> 0 {
  y = 1;
  while y <= 3 do {
    x = 1;
    while x <= 6 do {
      if x % 2 == 1 then { x = x + 1; restart; } else writeln x;
      x = x + 1;
    }
    y = y + 1;
  }
}

