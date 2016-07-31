
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
  int x = nondet_int(),y = nondet_int();

  x = -50;
  while( x < 0 ) {
	 x = x+y;
	 y++;
  }
  assert(y>0);
}
