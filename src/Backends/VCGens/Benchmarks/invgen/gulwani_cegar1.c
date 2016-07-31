
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
  int x = nondet_int(),y = nondet_int();

  assume(0 <= x);  assume(x <= 2);
  assume(0 <= y);  assume(y <= 2);
  while( nondet_int() ) {
	 x+=2;
	 y+=2;
  }
  if( y >= 0 ) 
    if( y <= 0 ) 
      if( 4 <= x ) 
	       assert( x < 4 );
}
