extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
  int x0, y0, x1, y1;
  int dy;
  int dx;
  int stepx, stepy;
  int fraction;
  int AUXVAR;

  x0=nondet_int();
  y0=nondet_int();
  x1=x0+30;
  y1=y0+30;
  dy = y1 - y0;
  dx = x1 - x0;
  if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
  
  if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }
  
  dy = dy*2;
  dx = dx*2;

  if (dx > dy) {
    fraction = 2*dy - dx;
   AUXVAR = x0 < x1 || x0 > x1;
    while (AUXVAR) {
      
      if (fraction >= 0) {
	y0 = y0 + stepy;
	fraction = fraction - 2*dx;
      } else {}
      
      x0 = x0 + stepx;
      fraction = fraction + 2*dy;
      AUXVAR = x0 < x1 || x0 > x1;
    }
    
  } else {
    fraction = 2*dx - dy;
    AUXVAR = y0 < y1 || y0 > y1;
    while (AUXVAR) {
      
      if (fraction >= 0) {
	x0 = x0 + stepx;
	fraction = fraction - 2*dy;
      } else {}
      
      y0 = y0 + stepy;
      fraction = fraction + 2*dx;
      AUXVAR = y0 < y1 || y0 > y1;
    }
    
  }
  
  assert(y1==y0);
  
}
