#include "rand64-sw.h"

/* Software implementation.  */

/* Input stream containing random bytes.  */
FILE *urandstream;
// For mrand48_r
struct drand48_data state;

/* Initialize the software rand64 implementation.  */
void software_rand64_init(const char *filepath) {
  urandstream = fopen(filepath, "r");
  if (!urandstream)
    abort();
}

/* Return a random value, using software operations.  */
unsigned long long software_rand64(void) {
  unsigned long long int x;
  if (fread(&x, sizeof x, 1, urandstream) != 1)
    abort();
  return x;
}

/* Finalize the software rand64 implementation.  */
void software_rand64_fini(void) { fclose(urandstream); }


// Functions for mrand48_r
void mrand_rand64_init(void) { srand48_r(time(NULL), &state); }

unsigned long long mrand_rand64(void) {
  unsigned long long int x;
  
  // first random 32 bits
  long int first;
  int rtn_val_1 = mrand48_r(&state, &first);

  // second random 32 bits
  long int second;
  int rtn_val_2 = mrand48_r(&state, &second);

  // check if valid return value
  if (rtn_val_1 < 0 || rtn_val_2 <0) {
    fprintf(stderr, "mrand48 returned invalid data");
    return 1;
  }

  unsigned long long int unsig_first = ((unsigned long long int)first) & 0xFFFFFFFF;
  unsigned long long int unsig_second = (unsigned long long int)second & 0xFFFFFFFF;
  unsigned long long int shift_unsig_first = unsig_first << 32;
  x = shift_unsig_first | unsig_second;
  return x;
}

void mrand_rand64_fini(void) {}
