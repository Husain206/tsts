#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define tsts_push(ts_ptr, val) do { \
  __typeof__(val) _temp = (val);    \
  push(ts_ptr, &_temp);             \
} while(0)


typedef struct tsts {
  void* data;
  uint32_t size; // byte size of each element
  uint32_t len;
  uint32_t cap;
} tsts;

// not the best but go with it
// something goes wrnwrn program goes crcr hahaha...
static void xmalloc(void* ptr){
    if(!ptr){
    perror("malloc failed");
    exit(0);
  }
}

static void init_tsts(tsts* ts, uint32_t size){
  ts->data = NULL;
  ts->cap = ts->len = 0;
  ts->size = size;
}

static inline void resize(tsts* ts){
  uint32_t cap = (ts->cap) ? ts->cap : 1;

  cap *= 2;

  void* new_ptr = realloc(ts->data, cap * ts->size);
  xmalloc(new_ptr);

  ts->data = new_ptr;
  ts->cap = cap;  
} 

static void push(tsts* ts, void* item){
  if(ts->len + 1 > ts->cap){
    resize(ts);
  }
  void* dest = (uint8_t*)ts->data + ts->len * ts->size;
  memcpy(dest, item, ts->size);

  ts->len++;
}

static void pop(tsts* ts, void* item){
  if(ts->len == 0) return;
  ts->len--;

  void* pos = (uint8_t*)ts->data + ts->len * ts->size;
  memcpy(item, pos, ts->size);
}

static void* get(tsts* ts, uint32_t index){
  if(index >= ts->len) return NULL;

  return (uint8_t*)ts->data + (ts->size * index);
}

static void set(tsts* ts, uint32_t index, void* value){
  if(index >= ts->len) return;
  void* pos = (uint8_t*)ts->data + (ts->size * index);
  memcpy(pos, value, ts->size);
}

static void insert(tsts* ts, uint32_t index, void* item){
  if(index > ts->len) return;

  if(ts->len + 1 < ts->cap){
    resize(ts);
  }

  void* pos = (uint8_t*)ts->data + (ts->size * index);
  if(index < ts->len){
    // number of bytes to move: (total elements - current index) * size
    memmove((uint8_t*)pos + ts->size, pos, (ts->len - index) * ts->size);
  }

  memcpy(pos, item, ts->size);
  ts->len++;
}

static void erase(tsts* ts, uint32_t index){
  if(index >= ts->len) return;

  void* pos = (uint8_t*)ts->data + (ts->len * index);

  if(index < ts->len - 1){
    memmove(pos, (uint8_t*)pos + ts->size, (ts->len - index - 1) * ts->size);
  }
  ts->len--;
}

static void sort(tsts* ts, int (*compar)(const void*, const void*)){
  qsort(ts->data, ts->len, ts->size, compar);
}

static uint32_t len(tsts* ts){
  return ts->len;
}


static void free_tsts(tsts* ts){
  free(ts->data);
  ts->data = NULL;
  ts->cap = ts->len = 0;
}

// lol reminds me of js :"D
// use when calling sort() to sort integers
static int int_cmp(const void* a, const void* b){
  return (*(int*)a - *(int*)b);
}


