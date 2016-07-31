
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

int f ()
{
  int buf_off=nondet_int(), pattern_off=nondet_int(), bound_off=nondet_int();

  int MAXPATHLEN=nondet_int();

  int error=nondet_int();

  int pathbuf_off=nondet_int();
  int pathend_off=nondet_int();
  int pathlim_off=nondet_int();
  int AUXVARIABLE = nondet_int();

  assume(AUXVARIABLE == 1);

  if(MAXPATHLEN >0); else goto END;

  buf_off = 0;
  pattern_off = 0;

  bound_off = MAXPATHLEN;

  pathbuf_off = 0;
  pathend_off = 0;
  pathlim_off = MAXPATHLEN;
	    
  error = 0;

  while (nondet_int()) {
    int i;

    assert(0 <= pattern_off ); assert( pattern_off <= MAXPATHLEN);

      if (nondet_int()) continue;

    i = 0;
    while(AUXVARIABLE)
      if (i > MAXPATHLEN) goto END;
      else {
	      assert(0 <= i);	assert( i <= MAXPATHLEN);

        i++;
        if (nondet_int()) goto END;
      }

      assert(0 <= pathlim_off );
      assert( pathlim_off <= MAXPATHLEN);

      if (i > MAXPATHLEN){
        if ( nondet_int() ) {

	         if ( nondet_int() ) {
	           error = 5;
	           goto END;
	         }
	         else {
	           assert (0 <= i);
             assert (i <= MAXPATHLEN + 1);

	           continue;
	         }
        }
      }

      if (nondet_int()) {
  
        assert (i <= MAXPATHLEN + 1);
  
        continue;
      }
  
      END_LOOP1:
      assert(1);
    }
 END:  

 return 0;
}
