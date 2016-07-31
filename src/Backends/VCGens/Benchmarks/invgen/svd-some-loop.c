
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f(){
  int n=nondet_int();
  int m=nondet_int();
  int l=nondet_int();
  int i=nondet_int();
  int j=nondet_int();
  int k=nondet_int();

  for (i=n;i>=1;i--) { // Accumulation of right-hand transformations. 
    l = i+1;
    if (i < n) {
      if ( nondet_int() ) {
        for (j=l;j<=n;j++) { // Double division to avoid possible underflow. 
          assert(1<=j);
          assert(j<=n);
          assert(1<=i);
          assert(i<=n);
        }
        for (j=l;j<=n;j++) {
          for (k=l;k<=n;k++) { 
            assert(1<=k);
            assert(k<=n);
            assert(1<=j);
            assert(j<=n);
          }
          for (k=l;k<=n;k++) { 
            assert(1<=k);
            assert(k<=n);
            assert(1<=j);
            assert(j<=n);
            assert(1<=i);
            assert(i<=n);
          }
        }
      }
      for (j=l;j<=n;j++) { 
        assert(1<=j);
        assert(j<=n);
        assert(1<=i);
        assert(i<=n);
      }
    }

    assert(1<=i);
    assert(i<=n);
    assert(1<=i);
    assert(i<=n);
    l=i;
  }

}
