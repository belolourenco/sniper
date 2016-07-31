
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();


int f (){
  //  char buf [BASE_SZ];
  // char str [BASE_SZ];
  int BASE_SZ = nondet_int();
  int i = nondet_int();
  int j = nondet_int();
  int len = BASE_SZ;
  int AUXVARIABLE = nondet_int();

  assume(AUXVARIABLE == 1);

  if(BASE_SZ > 0 ); else goto END;

  // str [BASE_SZ-1] = 0;
  assert( 0 <= BASE_SZ-1 );

  if (len == 0)
    goto END; 
  
  i = 0;
  j = 0;
  while (AUXVARIABLE) {
    if ( len == 0 ){ 
      goto END;
    } else {
      assert( 0<= j ); assert(j < BASE_SZ);
      assert( 0<= i ); assert(i < BASE_SZ );
      //      buf[j] = str[i];
      if ( nondet_int() ) {
        i++;
        j++;
        goto END;
      }
    }
    i ++;
    j ++;
    len --;
  }
  
 END:  
 return 0;
}

