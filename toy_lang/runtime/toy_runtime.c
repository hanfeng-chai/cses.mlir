#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int64_t length;
  int64_t capacity;
  char *data;
} CmlString;

typedef struct {
  int64_t *keys;
  int64_t *values;
  unsigned char *occupied;
  uint64_t capacity;
  uint64_t size;
  uint64_t seed;
} CmlMap;

static char output_buffer[65536];
static size_t output_size;
static bool output_initialized;

static void toy_flush_output(void) {
  if (output_size != 0) {
    fwrite(output_buffer, 1, output_size, stdout);
    output_size = 0;
  }
}

static void toy_initialize_output(void) {
  if (!output_initialized) {
    output_initialized = true;
    atexit(toy_flush_output);
  }
}

void toy_flush(void) {
  toy_initialize_output();
  toy_flush_output();
  fflush(stdout);
}

void toy_write_byte(int8_t value);

int64_t toy_read_i64(void) {
  int character = getchar_unlocked();
  while (character <= ' ' && character != EOF)
    character = getchar_unlocked();

  bool negative = character == '-';
  if (negative)
    character = getchar_unlocked();

  int64_t value = 0;
  while (character >= '0' && character <= '9') {
    value = value * 10 + character - '0';
    character = getchar_unlocked();
  }
  return negative ? -value : value;
}

void toy_write_i64(int64_t value, bool newline) {
  char buffer[32];
  unsigned length = 0;
  uint64_t magnitude;

  if (value < 0) {
    toy_write_byte('-');
    magnitude = (uint64_t)(-(value + 1)) + 1;
  } else {
    magnitude = (uint64_t)value;
  }
  do {
    buffer[length++] = (char)('0' + magnitude % 10);
    magnitude /= 10;
  } while (magnitude != 0);
  while (length != 0)
    toy_write_byte((int8_t)buffer[--length]);
  if (newline)
    toy_write_byte('\n');
}

void toy_write_i128(__int128 value, bool newline) {
  char buffer[48];
  unsigned length = 0;
  unsigned __int128 magnitude;

  if (value < 0) {
    toy_write_byte('-');
    magnitude = (unsigned __int128)(-(value + 1)) + 1;
  } else {
    magnitude = (unsigned __int128)value;
  }
  do {
    buffer[length++] = (char)('0' + magnitude % 10);
    magnitude /= 10;
  } while (magnitude != 0);
  while (length != 0)
    toy_write_byte((int8_t)buffer[--length]);
  if (newline)
    toy_write_byte('\n');
}

void toy_write_byte(int8_t value) {
  toy_initialize_output();
  if (output_size == sizeof(output_buffer))
    toy_flush_output();
  output_buffer[output_size++] = (char)value;
}

void toy_write_f64(double value, int64_t precision) {
  toy_flush_output();
  printf("%.*f\n", (int)precision, value);
}

void *toy_read_text(void) {
  CmlString *string = (CmlString *)malloc(sizeof(CmlString));
  if (string == NULL)
    abort();
  string->length = 0;
  string->capacity = 32;
  string->data = (char *)malloc((size_t)string->capacity);
  if (string->data == NULL)
    abort();

  int character = getchar_unlocked();
  while (character <= ' ' && character != EOF)
    character = getchar_unlocked();
  while (character > ' ') {
    if (string->length == string->capacity) {
      string->capacity *= 2;
      char *data = (char *)realloc(string->data, (size_t)string->capacity);
      if (data == NULL)
        abort();
      string->data = data;
    }
    string->data[string->length++] = (char)character;
    character = getchar_unlocked();
  }
  return string;
}

int64_t toy_string_length(const void *handle) {
  return ((const CmlString *)handle)->length;
}

int64_t toy_string_at(const void *handle, int64_t index) {
  return (unsigned char)((const CmlString *)handle)->data[index];
}

static uint64_t toy_hash_i64(uint64_t value) {
  value += 0x9e3779b97f4a7c15ULL;
  value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;
  value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;
  return value ^ (value >> 31);
}

static uint64_t toy_map_slot(const CmlMap *map, int64_t key) {
  uint64_t slot = toy_hash_i64((uint64_t)key + map->seed) & (map->capacity - 1);
  while (map->occupied[slot] && map->keys[slot] != key)
    slot = (slot + 1) & (map->capacity - 1);
  return slot;
}

static void toy_map_allocate(CmlMap *map, uint64_t capacity) {
  map->keys = (int64_t *)malloc(capacity * sizeof(int64_t));
  map->values = (int64_t *)malloc(capacity * sizeof(int64_t));
  map->occupied = (unsigned char *)calloc(capacity, 1);
  if (map->keys == NULL || map->values == NULL || map->occupied == NULL)
    abort();
  map->capacity = capacity;
}

void *toy_map_create(int64_t capacity_hint) {
  CmlMap *map = (CmlMap *)malloc(sizeof(CmlMap));
  if (map == NULL)
    abort();
  uint64_t requested = capacity_hint > 4 ? (uint64_t)capacity_hint : 4;
  uint64_t capacity = 8;
  while (capacity < requested * 2)
    capacity *= 2;
  map->size = 0;
  map->seed = toy_hash_i64((uintptr_t)map);
  toy_map_allocate(map, capacity);
  return map;
}

static void toy_map_grow(CmlMap *map) {
  int64_t *old_keys = map->keys;
  int64_t *old_values = map->values;
  unsigned char *old_occupied = map->occupied;
  uint64_t old_capacity = map->capacity;
  toy_map_allocate(map, old_capacity * 2);
  map->size = 0;
  for (uint64_t index = 0; index < old_capacity; ++index) {
    if (old_occupied[index]) {
      uint64_t slot = toy_map_slot(map, old_keys[index]);
      map->occupied[slot] = 1;
      map->keys[slot] = old_keys[index];
      map->values[slot] = old_values[index];
      ++map->size;
    }
  }
  free(old_keys);
  free(old_values);
  free(old_occupied);
}

int64_t toy_map_get(const void *handle, int64_t key, int64_t default_value) {
  const CmlMap *map = (const CmlMap *)handle;
  uint64_t slot = toy_map_slot(map, key);
  return map->occupied[slot] ? map->values[slot] : default_value;
}

void toy_map_set(void *handle, int64_t key, int64_t value) {
  CmlMap *map = (CmlMap *)handle;
  if ((map->size + 1) * 10 >= map->capacity * 7)
    toy_map_grow(map);
  uint64_t slot = toy_map_slot(map, key);
  if (!map->occupied[slot]) {
    map->occupied[slot] = 1;
    map->keys[slot] = key;
    ++map->size;
  }
  map->values[slot] = value;
}