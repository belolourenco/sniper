
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

int f (){

  int MAXPATHLEN=nondet_int();
  int pathbuf_off=nondet_int();

  int bound_off=nondet_int();

  int glob2_p_off=nondet_int();
  int glob2_pathbuf_off=nondet_int();
  int glob2_pathlim_off=nondet_int();

  if(MAXPATHLEN > 0); else goto END;

  pathbuf_off = 0;
  bound_off = pathbuf_off + (MAXPATHLEN + 1) - 1;

  glob2_pathbuf_off = pathbuf_off;
  glob2_pathlim_off = bound_off;

  for (glob2_p_off = glob2_pathbuf_off;
      glob2_p_off <= glob2_pathlim_off;
      glob2_p_off++) {

    assert (0 <= glob2_p_off ); 
    assert (glob2_p_off < MAXPATHLEN + 1);

  }


 END:  
 return 0;
}
