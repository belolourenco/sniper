
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();


int f (){
  
  int MAXPATHLEN=nondet_int();
  int buf_off=nondet_int();
  int pattern_off=nondet_int();
  int bound_off=nondet_int();

  int glob3_pathbuf_off= nondet_int();
  int glob3_pathend_off= nondet_int();
  int glob3_pathlim_off= nondet_int();
  int glob3_pattern_off= nondet_int();
  int glob3_dc = nondet_int();
  int AUXVARIABLE = nondet_int();

  assume(AUXVARIABLE == 1);

  if(MAXPATHLEN > 0); else goto END;

  buf_off = 0;
  pattern_off = 0;

  bound_off = 0 + (MAXPATHLEN + 1) - 1;

  glob3_pathbuf_off = buf_off;
  glob3_pathend_off = buf_off;
  glob3_pathlim_off = bound_off;
  glob3_pattern_off = pattern_off;

  glob3_dc = 0;
  while (AUXVARIABLE)
    if (glob3_pathend_off + glob3_dc >= glob3_pathlim_off) break;
    else {
      glob3_dc++;
      assert(0 <= glob3_dc);
      assert (glob3_dc < MAXPATHLEN + 1);
      if (nondet_int()) goto END;
    }

 END:  
 return 0;
}
