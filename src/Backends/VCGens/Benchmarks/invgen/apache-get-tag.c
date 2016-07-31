
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f()
{
  int tagbuf_len = nondet_int();
  int t = nondet_int();
  int AUXVARIABLE = nondet_int();

  if(tagbuf_len >= 1); else goto END;

  assume(AUXVARIABLE == 1);

  t = 0;

  --tagbuf_len;

  while (AUXVARIABLE) {
    if (t == tagbuf_len) {
      assert(0 <= t);
      assert(t <= tagbuf_len);
      goto END;
    }
    if (nondet_int()) {
      break;
    }
    assert(0 <= t);
    assert(t <= tagbuf_len);
    t++;
  }
  assert(0 <= t);
  assert(t <= tagbuf_len);
  t++;
  while (AUXVARIABLE) {
    if (t == tagbuf_len) {
      assert(0 <= t);
      assert(t <= tagbuf_len);
      goto END;
    }

    if (nondet_int()) {
      if ( nondet_int()) {
        assert(0 <= t);
        assert(t <= tagbuf_len);
        t++;
        if (t == tagbuf_len) {
	       assert(0 <= t);
	       assert(t <= tagbuf_len);
         goto END;
        }
      }
    } else if ( nondet_int()) {
      break;
    }
    assert(0 <= t);
    assert(t <= tagbuf_len); 
    t++;                
  }
  assert(0 <= t);
  assert(t <= tagbuf_len);

  END:
  return;
}
