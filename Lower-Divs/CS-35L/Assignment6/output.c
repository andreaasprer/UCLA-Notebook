#include "output.h"
bool writebytes(unsigned long long x, int nbytes) {
    do {
      if (putchar(x) < 0)
        return false;
      x >>= CHAR_BIT;
      nbytes--;
    } while (0 < nbytes);
  
    return true;
}

int handle_output(char *input, char *output, int nbytes) {
  /* Now that we know we have work to do, arrange to use the
  appropriate library.  */
  void (*initialize)(const char *);
  unsigned long long (*rand64)(void);
  void (*finalize)(void);
  char *path = "/dev/random"; // default file path to read from

  // Error handling for missing input or output
  if (!input || !output) {
    fprintf(stderr, "Error: Missing input or output");
    return 1;
  }

  // Handle input options
  if (strcmp(input, "rdrand") == 0 && rdrand_supported()) {
    // Handle hardware option
    if (rdrand_supported()) {
      initialize = (void (*)(const char *))hardware_rand64_init;
      rand64 = hardware_rand64;
      finalize = hardware_rand64_fini;
    } else {
      fprintf(stderr, "rdrand is not supported\n");
      return 1;
    }

  } else if (strcmp(input, "mrand48_r") == 0) {
    // Handle mrand48_r option
    initialize = (void (*)(const char *))mrand_rand64_init;
    rand64 = mrand_rand64;
    finalize = mrand_rand64_fini;
  } else if (strncmp(input, "/", 1) == 0) {
    // Handle /F option
    path = input;
    initialize = software_rand64_init;
    rand64 = software_rand64;
    finalize = software_rand64_fini;
  } else {
    // Handle invalid file error
    fprintf(stderr, "Not valid file name: %s\n", input);
    return 1;
  }  

  initialize(path);
  int wordsize = sizeof rand64();
  int output_errno = 0;

  if (strcmp(output, "stdio") == 0) {
    do {
      unsigned long long x = rand64();
      int outbytes = nbytes < wordsize ? nbytes : wordsize;
      if (!writebytes(x, outbytes)) {
        output_errno = errno;
        break;
      }
      nbytes -= outbytes;
    } while (0 < nbytes);
  
    if (fclose(stdout) != 0)
      output_errno = errno;
  
    if (output_errno) {
      errno = output_errno;
      perror("output");
    }
  } else {
    char *endptr;
    errno = 0;
    long long N = strtoll(output, &endptr, 10);

    // Check for valid N
    if (endptr == output || *endptr != '\0' || N <= 0 || errno != 0) {
      fprintf(stderr, "Invalid N\n");
      return 1;
    }
    
    // Create buffer
    char *buff = (char *)malloc(nbytes);

    // Verify if buffer was created correctly
    if (!buff) {
      fprintf(stderr, "Creating buffer failed");
      return 1;
    }

    // stdout file descriptor for write
    int fd = 1;
    int remaining = nbytes;

    while (remaining) {
      // edge case: update N if N is larger than remaining
      N = remaining < N ? remaining : N;

      // fill buffer
      int buff_pos = 0; // reset buffer position
      while (buff_pos < N) {
        unsigned long long x = rand64();
        for (int i = 0; i < wordsize && buff_pos < N; i++) {
          buff[buff_pos++] = x & 0xFF;
          x >>= 8;
        }
      }
      
      if (write(fd, buff, N) < 0) {
        output_errno = errno;
        break;
      }

      remaining -= N;
    }

    free(buff);

    if (fclose(stdout) != 0) {
      output_errno = errno;
    }

    if (output_errno) {
      errno = output_errno;
      perror("output");
    }
  }

  finalize();
  return !!output_errno;
}