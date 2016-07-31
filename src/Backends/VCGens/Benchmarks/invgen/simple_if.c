
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
  int n=nondet_int(),m=nondet_int();
  int i = 1;

  while( i < n ) {
    if( m > 0 ) {
      i = 2*i;
    } else {
      i = 3*i;
    }
    
  }
  assert (i > 0 );
}
