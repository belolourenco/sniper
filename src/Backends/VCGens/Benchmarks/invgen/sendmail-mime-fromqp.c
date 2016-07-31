
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();


int f (void)
{
  int outfilelen = nondet_int();

  int nchar = 0;

  int out = 0; 

  if(outfilelen > 0); else goto RETURN;

  while(nondet_int()){
    if(nondet_int())
    {
      if(nondet_int())
	goto AFTERLOOP; 

      if(nondet_int())
      {
	       out = 0;
	       nchar = 0;
	       goto LOOPEND;
      }else{
	     if(nondet_int())  goto AFTERLOOP;

	     nchar++;
	     if (nchar >= outfilelen)
	       goto AFTERLOOP;

	     assert(0<=out);//1
	     assert(out<outfilelen);//2
	     out++;
      }
    }
    else
    {

      nchar++;
      if (nchar >= outfilelen)
	     goto AFTERLOOP;

      assert(0<=out);//3
      assert(out<outfilelen);//4
      out++;

      if(nondet_int()) goto AFTERLOOP;
    }
    LOOPEND:
    assert(1);
  }
  
 AFTERLOOP:

  assert(0<=out);//5
  assert(out<outfilelen);
  out++;
 RETURN:  
 return 0;
}
