
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();


void f(){
  int x=0;
  int y=0;
  int z=0;
  int w=0;

  while ( nondet_int() ){
    if ( nondet_int() ) {
      x++; y = y+100;
    } else if  ( nondet_int() ) {
      if( x >= 4)
	{ x=x+1; y=y+1;}
    } else if  ( y >10*w)
      if (z>=100*x )
      y = -y;
    w=w+1; 
    z=z+10;
  }
  if ( x >=4 )
    assert(y>2);
}
