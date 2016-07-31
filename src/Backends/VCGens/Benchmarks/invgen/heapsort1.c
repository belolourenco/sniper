
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

int f( ){
  int n=nondet_int(),l=nondet_int(),r=nondet_int(),i=nondet_int(),j=nondet_int();
  
  assume(1 <= n);
  l = n/2 + 1;
  r = n;
  if(l>1) {
    l--;
  } else {
    r--;
  }
  while(r > 1) {
    i = l;
    j = 2*l;
    while(j <= r) {
      if( j < r) {
	if( nondet_int() )
	  j = j + 1;
      }
      if( nondet_int() ) { 
      	break;
      }
      i = j;
      j = 2*j;
    }
    if(l > 1) {
      l--;
    } else {
      assert(r <= n);
      r--;
    }
  }
  return 0;
}

