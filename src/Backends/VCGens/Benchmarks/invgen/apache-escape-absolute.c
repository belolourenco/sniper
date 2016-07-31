
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f ()
{
  int scheme = nondet_int();
  int urilen = nondet_int();
  int tokenlen = nondet_int();
  int cp = nondet_int();
  int c = nondet_int();

  if(urilen>0); else goto END;
  if(tokenlen>0); else goto END;
  if(scheme >= 0 );else goto END;
  if (scheme == 0 || (urilen-1 < scheme)) {
    goto END;
  }

  cp = scheme;
  
  assert(cp-1 < urilen);
  assert(0 <= cp-1);

  if (nondet_int()) {
    assert(cp < urilen);
    assert(0 <= cp);
    while ( cp != urilen-1) {
      if(nondet_int()) break;
      assert(cp < urilen);
      assert(0 <= cp);
      ++cp;
    }
    assert(cp < urilen);
    assert( 0 <= cp );
    if (cp == urilen-1) goto END;
    assert(cp+1 < urilen);
    assert( 0 <= cp+1 );
    if (cp+1 == urilen-1) goto END;
    ++cp;

    scheme = cp;

    if (nondet_int()) {
      c = 0;
      assert(cp < urilen);
      assert(0<=cp);
      int AUXVARIABLE = cp != urilen-1 && c < tokenlen - 1;
      while (AUXVARIABLE) {
	      assert(cp < urilen);
	      assert(0<=cp);
        if (nondet_int()) {
          ++c;
	        assert(c < tokenlen);
	        assert(0<=c);
	        assert(cp < urilen); //Interesting assert
	        assert(0<=cp);
        }
        ++cp;
        AUXVARIABLE = cp != urilen-1 && c < tokenlen - 1;
      }
      goto END;
    }
  }

 END:

 return;
}
