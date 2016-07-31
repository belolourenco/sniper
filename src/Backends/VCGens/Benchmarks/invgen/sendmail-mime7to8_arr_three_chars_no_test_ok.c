
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

int f (void){
  
  int fbuflen=nondet_int();
  int fb=nondet_int();

  if(fbuflen >0);else goto END;
  fb = 0;
  while ( nondet_int())
  {
    if ( nondet_int())
      break;

    if ( nondet_int())
      break;

    assert(0<=fb);
    assert(fb<fbuflen);

    fb++;
    if (fb >= fbuflen-1)
      fb = 0;

    assert(0<=fb);
    assert(fb<fbuflen);

    fb++;
    if (fb >= fbuflen-1)
      fb = 0;

    assert(0<=fb);
    assert(fb<fbuflen);

    fb++;
    if (fb >= fbuflen-1)
      fb = 0;
  }

  if (fb > 0)
  {
    assert(0<=fb);
    assert(fb<fbuflen);
  }

 END:  
 return 0;
}
