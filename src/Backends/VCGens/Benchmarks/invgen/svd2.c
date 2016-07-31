
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f(int n)
{
  int i=nondet_int(),j=nondet_int(),k=nondet_int(),l=nondet_int();
  

  assume(l>0);

  for (i=n;i>=1;i--) { // Accumulation of right-hand transformations. 
    if (i < n) {
      if ( nondet_int() ) {
	for (j=l;j<=n;j++) { // Double division to avoid possible underflow.   
	  //assert(1<=j);//assert(j<=n);
	  // assert(1<=i);assert(i<=n);
	  // assert(1<=i);assert(i<=m); // TODO feasible counterexample found
	  //assert(1<=l);assert(l<=n);
	}
	for (j=l;j<=n;j++) {
	  for (k=l;k<=n;k++) { 
	    //assert(1<=i);assert(i<=m); // TODO feasible counterexample found
	    //assert(1<=k);assert(k<=n);
	    //assert(1<=j);assert(j<=n);
	  }
	  for (k=l;k<=n;k++) { 
	    //assert(1<=k);assert(k<=n);
	    //assert(1<=j);assert(j<=n);
	    assert(1<=i);assert(i<=n);
	  }
	}
      }
      for (j=l;j<=n;j++) { 
        //assert(1<=j);
	//assert(j<=n);
	//assert(1<=i);
	//assert(i<=n);
      }
    }
    
    //assert(1<=i);
    //assert(i<=n);
    //assert(1<=i);
    //assert(i<=n);
    l=i;
  }
}
