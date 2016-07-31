
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f(){

  int n = nondet_int();
  int i = nondet_int();
  int j = nondet_int();
  int k = nondet_int();
  int l = nondet_int();
  int m=nondet_int();

  assume(n>m);

  if (m<=n) { i = m; } else { i = n; } 

  for (i=i ;i>=1;i--) { // Accumulation of left-hand transformations. 
    l=i+1;

    assert(1<=i);
    assert(i<=n); 

    for (j=l;j<=n;j++) {
      assert(1<=i);
      assert(i<=m);
      assert(1<=j);assert(j<=n);
    }

    if ( nondet_int() ) {
      for (j=l;j<=n;j++) {
	       for (k=l;k<=m;k++) {
	         assert(1<=k);assert(k<=m);
	         assert(1<=i);assert(i<=n);
	         assert(1<=j);assert(j<=n);
	       }

	       assert(1<=i);assert(i<=m);
	       assert(1<=i);assert(i<=n);
	       for (k=i;k<=m;k++) {
	          assert(1<=k);assert(k<=m);
	          assert(1<=j);assert(j<=n);
	          assert(1<=i);assert(i<=n);
	       }
      }
      for (j=i;j<=m;j++) { 
	       assert(1<=j);assert(j<=m); 
	       assert(1<=i);assert(i<=n);
      }
    } else for (j=i;j<=m;j++) { 
             assert(1<=j);assert(j<=m); 
             assert(1<=i);assert(i<=n);
           }
    
    assert(1<=i);assert(i<=m); 
    assert(1<=i);assert(i<=n);
  }
}
