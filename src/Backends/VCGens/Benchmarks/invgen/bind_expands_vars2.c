
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

int f() {
  
  int cp1_off= nondet_int(), n1= nondet_int(), n2= nondet_int(), mc_i= nondet_int();
  int MAXDATA = nondet_int();
  if (MAXDATA > 0 ); else goto END;

  if ((n1 <= MAXDATA * 2)); else goto END;

  if ((cp1_off <= n1)); else goto END;

  if ((n2 <= MAXDATA*2 - n1)); else goto END;

  for (mc_i = 0; mc_i < n2; mc_i++) {
    assert (cp1_off+mc_i < MAXDATA * 2);
  }
  
 END:  

  return 0;
}
