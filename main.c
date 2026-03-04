#include "tsts.h"

int main(void){
  tsts ts;
  init_tsts(&ts, sizeof(int));

  int x = 5;
  tsts_push(&ts, x);
  tsts_push(&ts, 3);
  tsts_push(&ts, 2);
  tsts_push(&ts, 1);
  tsts_push(&ts, 5);
  tsts_push(&ts, 1);
  tsts_push(&ts, 92);
  
  int popped;
  pop(&ts, &popped);
  printf("%d\n", popped);

  int y = 69;
  set(&ts, 2, &y);

  sort(&ts, int_cmp);
  for(uint32_t i = 0; i < len(&ts); i++){
    int* g = get(&ts, i);
    printf("i.%d: %d\n", i, *g); 
  }

  free_tsts(&ts);
  return 0;
}

