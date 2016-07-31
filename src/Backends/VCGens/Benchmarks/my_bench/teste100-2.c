extern void assert(int x);
extern void assume(int x);
extern int nondet_int();  

// void f(){
//   int x = nondet_int();


//   assume(x <= 50);

//   while(x < 100){
//     assert(x < 100);
//     x = x + 1;
//     assert(x < 200);
//   }
// }

void f(){
  int x = nondet_int();
  int y = nondet_int();

  assume(x <= 50);
  assume(y < x);

  while(x < 100){
    assert(y < 100);
    //assume(y < 100);
    x = x + 1;
    y = y + 1;
    assert(y <= 100);
    //assume(y <= 100);
  }
}