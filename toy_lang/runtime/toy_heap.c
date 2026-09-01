#include <stdint.h>
#include <stdlib.h>

typedef struct {
  int64_t *first;
  int64_t *second;
  int64_t size;
  int64_t capacity;
} CmlHeap;

static int less(const CmlHeap *heap, int64_t left, int64_t right) {
  return heap->first[left] < heap->first[right]
      || (heap->first[left] == heap->first[right]
          && heap->second[left] < heap->second[right]);
}

static void swap(CmlHeap *heap, int64_t left, int64_t right) {
  int64_t temporary = heap->first[left];
  heap->first[left] = heap->first[right];
  heap->first[right] = temporary;
  temporary = heap->second[left];
  heap->second[left] = heap->second[right];
  heap->second[right] = temporary;
}

void *toy_heap_create(int64_t capacity_hint) {
  CmlHeap *heap = (CmlHeap *)malloc(sizeof(CmlHeap));
  if (heap == NULL)
    abort();
  heap->size = 0;
  heap->capacity = capacity_hint > 4 ? capacity_hint : 4;
  heap->first = (int64_t *)malloc((size_t)heap->capacity * sizeof(int64_t));
  heap->second = (int64_t *)malloc((size_t)heap->capacity * sizeof(int64_t));
  if (heap->first == NULL || heap->second == NULL)
    abort();
  return heap;
}

static void grow(CmlHeap *heap) {
  heap->capacity *= 2;
  heap->first = (int64_t *)realloc(heap->first, (size_t)heap->capacity * sizeof(int64_t));
  heap->second = (int64_t *)realloc(heap->second, (size_t)heap->capacity * sizeof(int64_t));
  if (heap->first == NULL || heap->second == NULL)
    abort();
}

void toy_heap_push(void *handle, int64_t first, int64_t second) {
  CmlHeap *heap = (CmlHeap *)handle;
  if (heap->size == heap->capacity)
    grow(heap);
  int64_t position = heap->size++;
  heap->first[position] = first;
  heap->second[position] = second;
  while (position > 0) {
    int64_t parent = (position - 1) / 2;
    if (!less(heap, position, parent))
      break;
    swap(heap, position, parent);
    position = parent;
  }
}

void toy_heap_pop(void *handle) {
  CmlHeap *heap = (CmlHeap *)handle;
  --heap->size;
  heap->first[0] = heap->first[heap->size];
  heap->second[0] = heap->second[heap->size];
  int64_t position = 0;
  while (position * 2 + 1 < heap->size) {
    int64_t child = position * 2 + 1;
    if (child + 1 < heap->size && less(heap, child + 1, child))
      ++child;
    if (!less(heap, child, position))
      break;
    swap(heap, position, child);
    position = child;
  }
}

int64_t toy_heap_query(const void *handle, int64_t mode) {
  const CmlHeap *heap = (const CmlHeap *)handle;
  if (mode == 0)
    return heap->first[0];
  if (mode == 1)
    return heap->second[0];
  return heap->size;
}