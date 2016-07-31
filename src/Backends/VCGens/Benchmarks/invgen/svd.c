
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();


void f(int m, int n){
  int flag=nondet_int(),i=nondet_int(),its=nondet_int()
      ,j=nondet_int(),jj=nondet_int(),k=nondet_int(),l=nondet_int(),nm=nondet_int();



  for (i=1;i<=n;i++) {
    l=i+1;
    
    assert(1<=i);assert(i<=n);
    
    if (i <= m) {

      for (k=i;k<=m;k++) { 
  assert(1<=k);assert(k<=m);
  assert(1<=i);assert(i<=n);
  
      }

      if ( nondet_int() ) {

  for (k=i;k<=m;k++) {
    
    assert(1<=k);assert(k<=m);
    assert(1<=i);assert(i<=n);
    

    
  }

  assert(1<=i);assert(i<=m);
  assert(1<=i);assert(i<=n);
  

  
  


  assert(1<=i);assert(i<=m);
  assert(1<=i);assert(i<=n);
  

  for (j=l;j<=n;j++) {
    
    for (k=i;k<=m;k++) {

      assert(1<=k);assert(k<=m);
      assert(1<=i);assert(i<=n);
      assert(1<=j);assert(j<=n);
      
    }
    
    for (k=i;k<=m;k++) {

      assert(1<=k);assert(k<=m);
      assert(1<=i);assert(i<=n);
      assert(1<=j);assert(j<=n);
      
    }
  }
  for (k=i;k<=m;k++) { 

    assert(1<=k);assert(k<=m);
    assert(1<=i);assert(i<=n);
    
  }

      }

      }


    
    
    if (i <= m && i != n) {
      for (k=l;k<=n;k++) {
  assert(1<=i);assert(i<=m);
  assert(1<=k);assert(k<=n);
  
      }
      if ( nondet_int() ) {
  for (k=l;k<=n;k++) {

   assert(1<=i);assert(i<=m);
   assert(1<=k);assert(k<=n);
    


   assert(1<=i);assert(i<=m);
   assert(1<=k);assert(k<=n);
    
  }
  
  assert(1<=i);assert(i<=m);
  assert(1<=l);assert(l<=n);
  

  
  

  assert(1<=i);assert(i<=m);
  assert(1<=l);assert(l<=n);
  
  for (k=l;k<=n;k++) { 

   assert(1<=i);assert(i<=m);
   assert(1<=k);assert(k<=n);
    
  }
  for (j=l;j<=m;j++) {
    
    for (k=l;k<=n;k++) { 

      assert(1<=j);assert(j<=m);
      assert(1<=i);assert(i<=m);
      assert(1<=k);assert(k<=n);
      
    }
    for (k=l;k<=n;k++) { 

      assert(1<=j);assert(j<=m);
      assert(1<=k);assert(k<=n);
      
    }
  }
  for (k=l;k<=n;k++) { 

    assert(1<=i);assert(i<=m);
    assert(1<=k);assert(k<=n);
    
  }
      }
    }
    
    
  }


  for (i=n;i>=1;i--) { 
    l = i+1;
    if (i < n) {
      if ( nondet_int() ) {
  for (j=l;j<=n;j++) { 

    assert(1<=j);assert(j<=n);
    assert(1<=i);assert(i<=n);
    
    assert(1<=l);assert(l<=n);
    
  }
  for (j=l;j<=n;j++) {
    
    for (k=l;k<=n;k++) { 

      
      assert(1<=k);assert(k<=n);
      assert(1<=j);assert(j<=n);
      
    }
    for (k=l;k<=n;k++) { 
      assert(1<=k);assert(k<=n);
      assert(1<=j);assert(j<=n);
      assert(1<=i);assert(i<=n);
      
    }
  }
      }
      for (j=l;j<=n;j++) { 

        assert(1<=j);assert(j<=n);
  assert(1<=i);assert(i<=n);
  
      }
    }

    assert(1<=i);assert(i<=n);
    
    assert(1<=i);assert(i<=n);
    
    
  }
}