extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
  int n[7];
  int g[7];
  int u[7];
  int t[7];
  int i=nondet_int(), j=nondet_int(), h=nondet_int(), c=nondet_int(), diff=nondet_int(), AUX=nondet_int(), AUX2=nondet_int();
  
  i=0;
  while(i <= 6){
    assert(i>=0 && i<6+1);
    g[i] = 0;
    t[i] = g[i];
    u[i] = 1;
    n[i] = 3;
    i=i+1;
  }
  c=0;
  AUX=c<12 && g[6] == 0;
  while( AUX){
    h=0;
    while(h<6-1){
      assert(h>=0 && h<6+1);
      t[h] = g[h];
      h=h+1;
    }
    i = 0;
    j = g[0] + u[0];
    assert(i>=0 && i<6+1);
    AUX2 = (j >= n[i]) || (j < 0);
    while(AUX2){
      assert(i>=0 && i<6+1);
      u[i] = -u[i];
      i=i+1;
      assert(i>=0 && i<6+1);
      j = g[i] + u[i];
      assert(i>=0 && i<6+1);
      AUX2 = (j >= n[i]) || (j < 0);
    }
    assert(i>=0 && i<6+1);
    g[i] = j;
    diff=0;
    h=0;
    while(h<6-1){
      assert(h>=0 && h<6+1);
      diff= diff+g[h]-(t[h]);
      h=h+1;
    }
    assert( diff==1 || diff==-1);
    c=c+1;
  AUX=c<12 && g[6] == 0;
  }
  
}
