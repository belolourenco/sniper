
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
  int n=nondet_int(),m=nondet_int();
  int i = 1;
  m = 10;
  while( i < n ) {
    while( m > 0 ) {
      m--;
      i = 2*i;
    }
  }
  assert (i > 0 );
}
