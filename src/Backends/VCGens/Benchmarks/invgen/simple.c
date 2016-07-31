
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
  int x=0;
  int n=nondet_int();
  
  assume(n > 0 );
  while( x < n ){
    x++;
  }
  assert( x<=n );
}
