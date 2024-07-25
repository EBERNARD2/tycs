#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define STARTING_CAPACITY 8

typedef struct DA {
  // TODO define our struct
  void **data; 
  unsigned int index;
  int current_capacity;
} DA;


DA* DA_new (void) {
  // TODO allocate and return a new dynamic array
  struct DA* da_new = malloc(sizeof(DA));
  if (da_new == NULL) {
    printf("Not enough heap memory to create dynamic array\n");
    exit(1);
  }
  da_new->data = malloc(sizeof(void *) * STARTING_CAPACITY);

  if (da_new->data == NULL) {
    free(da_new);
    printf("Could not allocate space for dynamic array\n");
    exit(1);
  }
  
  da_new->index = 0;
  da_new->current_capacity = STARTING_CAPACITY;
  return da_new;
}

int DA_size(DA *da) {
  // TODO return the number of items in the dynamic array
  return da->index;
}

void DA_push (DA* da, void* x) {
  // TODO push to the end
    // if the current index is >= to current capacity 
    if (da->index == da->current_capacity) {
      // reallocate space for data array... take current capacity * 2
      da->data = realloc(da->data, sizeof(da->current_capacity) *2);
      if (da->data == NULL) {
        printf("Not enough heap memory to create dynamic array\n");
        exit(1);
      }
      da->current_capacity = da->current_capacity * 2;
    } 
    // otherwise set value at da index and update index
    da->data[da->index++] = x;
    
}

void *DA_pop(DA *da) {
  // TODO pop from the end
  // grab value at current index and decrement
  if (da->index == 0)
    return NULL;
  else
    return da->data[--da->index];
}

void DA_set(DA *da, void *x, int i) {
  // TODO set at a given index, if possible
  // only set an invoice if it is in range // throw an 
  if (i > -1 && i < da->current_capacity){
    da->data[i] = x;
  } else {
    printf("Error: index outside of range\n");
    exit(1);
  }
}

void *DA_get(DA *da, int i) {
  // TODO get from a given index, if possible
  if (i > -1 && i < da->current_capacity) {
    return da->data[i];
  } else {
    printf("Error index outside of range.\n");
    exit(1);
  }
}


void DA_free(DA *da) {
  // TODO deallocate anything on the heap
  free(da->data);
  free(da);
}

int main() {
    DA* da = DA_new();

    assert(DA_size(da) == 0);

    // basic push and pop test
    int x = 5;
    float y = 12.4;
    DA_push(da, &x);
    DA_push(da, &y);
    assert(DA_size(da) == 2);

    assert(DA_pop(da) == &y);
    assert(DA_size(da) == 1);

    assert(DA_pop(da) == &x);
    assert(DA_size(da) == 0);
    assert(DA_pop(da) == NULL);

    // basic set/get test
    DA_push(da, &x);
    DA_set(da, &y, 0);
    assert(DA_get(da, 0) == &y);
    DA_pop(da);
    assert(DA_size(da) == 0);

    // expansion test
    DA *da2 = DA_new(); // use another DA to show it doesn't get overriden
    DA_push(da2, &x);
    int i, n = 100 * STARTING_CAPACITY, arr[n];
    for (i = 0; i < n; i++) {
      arr[i] = i;
      DA_push(da, &arr[i]);
    }
    assert(DA_size(da) == n);
    for (i = 0; i < n; i++) {
      assert(DA_get(da, i) == &arr[i]);
    }
    for (; n; n--)
      DA_pop(da);
    assert(DA_size(da) == 0);
    assert(DA_pop(da2) == &x); // this will fail if da doesn't expand

    DA_free(da);
    DA_free(da2);
    printf("OK\n");
}
