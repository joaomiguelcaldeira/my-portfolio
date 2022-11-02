int x;
int *fir() -> 0 {
  x = 1;
  while x <= 6 do {
     if x % 2 == 1 then { x = x + 1; restart; } else writeln x;
     x = x + 1;
  }
}

