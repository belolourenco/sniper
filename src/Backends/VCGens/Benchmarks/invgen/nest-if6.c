
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();


void f(){
  int lda=nondet_int(),n=nondet_int();
  int j=nondet_int(),k=nondet_int(),kp1=nondet_int(),l=nondet_int(),nm1=nondet_int();
  int i=nondet_int(), itemp=nondet_int();

  if( n < lda); else goto END; 
  if( 0 <= n ); else goto END; 
  nm1 = n - 1;
  if (nm1 >=  0) {
    for (k = 0; k < nm1; k++) {
      kp1 = k + 1;

      int dx = k;
      int incx = 1;
      
      if( n-k < 1 ) { itemp = -1; goto IDAMAXEND; }
      if(n-k ==1 )  { itemp = 0; goto IDAMAXEND; }
      if(incx != 1) {
	
	int ix = 1;

	ix = ix + incx;
	for (i = 1; i < n-k; i++) {
	  if(nondet_int()) {
	    itemp = i;
	  }
	  ix = ix + incx;
	}
      }
      else {
	
	itemp = 0;
	for (i = 1; i < n-k; i++) {
	  if(nondet_int()) {
	    itemp = i;
	  }
	}
      }

    IDAMAXEND:  l = itemp +k;

      if ( nondet_int() ) {
	
	if (l != k) {
	}
	
	for (j = kp1; j < n; j++) {

	  if (l != k) {
	  }
	} 
      }
      else { 
      }
    } 
  }
   assert(0 <= n);
   assert(n < lda);

 END: 
 return;
}