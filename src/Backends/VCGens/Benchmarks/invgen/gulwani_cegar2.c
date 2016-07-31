
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
  int x= nondet_int(),m= nondet_int(),n= nondet_int();

  x = 0;
  m = 0;
  while( x < n ) {
    if(nondet_int())
	    m = x;
	  x++;
  }
  if( n > 0 ){
    assert( 0<=m);
    assert(m<n);
  }
}
