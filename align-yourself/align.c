#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ALIGNMENT (16)

#define KB (1024)
#define MB (1024 * KB)
#define GB (1024 * MB)

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint8_t u8;

static u8 *memory;
static u8 *base;
static u8 *cap;
static u8 *next_free;

#define ALIGNUP(nAddress, nBytes)                                              \
  ((((u64)nAddress) + (nBytes) - 1) & (~((nBytes) - 1)))

void init_memory(u64 num_bytes) {
  printf("Initializing memory system with %zu bytes.\n", num_bytes);
  memory = (u8 *)malloc(num_bytes + ALIGNMENT);
  base = (u8 *)ALIGNUP(memory, ALIGNMENT);
  cap = (u8 *)ALIGNUP(memory + num_bytes, ALIGNMENT);
  printf("set cap to memory (%p) + num_bytes (%zu) = %p (unaligned)\n", memory,
         num_bytes, memory + num_bytes);

  next_free = base;
}

u8 *arena_alloc(u64 num_bytes) {
  u64 avail = cap - next_free;
  if (num_bytes > (avail)) {
    fprintf(stderr,
            "Out of memory. You tried to alloc %zu, but only %zu bytes "
            "available.\n",
            num_bytes, avail);
    abort();
  }
  u8 *new_memory = next_free;
  next_free = (u8 *)ALIGNUP(next_free + num_bytes, ALIGNMENT);
  return new_memory;
}

void arena_print_stats() {
  printf("-------------------\n");
  printf("memory ptr:    %p\n", memory);
  printf("base ptr:      %p\n", base);
  printf("next_free ptr: %p\n", next_free);
  printf("cap ptr:       %p\n", cap);
  printf("-------------------\n");
}

int main(int argc, char **argv) {

  printf("System stats:\n");
  printf("-------------\n");
  printf("_Alignof(max_align_t): %zu\n", _Alignof(max_align_t));
  printf("_Alignof(u8): %zu\n", _Alignof(u8));
  printf("_Alignof(u32): %zu\n", _Alignof(u32));
  printf("_Alignof(double): %zu\n", _Alignof(double));
  printf("_Alignof(long double): %zu\n", _Alignof(long double));

  printf("Initialize Memory Sytem:\n");
  init_memory(513);
  arena_print_stats();

  printf("Allocate 1 byte:\n");
  u8 *one_byte = arena_alloc(1);
  arena_print_stats();

  printf("Allocate 16 bytes:\n");
  u8 *sixteen_bytes = arena_alloc(16);
  arena_print_stats();

  printf("Allocate 17 bytes:\n");
  u8 *seventeen_bytes = arena_alloc(17);
  arena_print_stats();

  return 0;
}
