/*
 * Variant: This one just blindly copies the input into buffer and writes '>''\0' at the end.
 */

extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

int f (void)
{

  int in = nondet_int();
  int inlen=nondet_int();
  int bufferlen=nondet_int();
  int buf=nondet_int();
  int buflim=nondet_int();
  
  if(bufferlen >1);else goto END;
  if(inlen > 0);else goto END;
  if(bufferlen < inlen);else goto END;

  buf = 0;
  in = 0;
  buflim = bufferlen - 2;

  while (nondet_int())
  {
    if (buf == buflim)
      break;
    assert(0<=buf);
    assert(buf<bufferlen); 

    buf++;
out:
    in++;
    assert(0<=in);//3
    assert(in<inlen);//4

  }

  assert(0<=buf);//5
  assert(buf<bufferlen);//5

  buf++;

  assert(0<=buf);//6
  assert(buf<bufferlen);

  buf++;

 END:  
 return 0;
}
