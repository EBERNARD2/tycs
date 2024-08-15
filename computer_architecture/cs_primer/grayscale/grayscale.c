#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define int32le(b) (b)[0] | ((b)[1] << 8) | ((b)[2] << 16) | ((b)[3] << 24)

// TODO: make a small change to this function to make it much faster
void grayscale(unsigned char *pixels, int32_t width, int32_t height) {
  int x, y, offset;
  unsigned char lum;

  /* - In modern processors, 64 bytes are retrived and placed in a cache line at a time
    - Multi Dimensional arrays are stored in a continguous array of bytes throughout memory
    - If height is in the inner loop, every loop iteration would be a cache miss so we would need 
      15-20 clock cycles to fetch the next value from RAM
    - Using width in the inner loop let's 16 width values to be cached at a time (64 b / 4 byte int32_t size)
    - Ultimately there will be more cache hits thus limiting the amount of fetches to RAM improving program performance
  
  */

  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      offset = 3 * (y * width + x);
      lum = 0.0722 * (double)pixels[offset] +
            0.7152 * (double)pixels[offset + 1] +
            0.2126 * (double)pixels[offset + 2];
      pixels[offset] = lum;
      pixels[offset + 1] = lum;
      pixels[offset + 2] = lum;
    }
  }
}

int main () {
  // open source file and read bytes
  FILE *fh = fopen("teapots.bmp", "r");
  fseek(fh, 0, SEEK_END);
  long size = ftell(fh);
  rewind(fh);
  unsigned char *buffer = malloc(size);
  fread(buffer, size, 1, fh);
  fclose(fh);
  // process in place
  //
  int32_t offset = int32le(buffer + 10), width = int32le(buffer + 18),
          height = int32le(buffer + 22);
  clock_t start = clock();
  grayscale(buffer + offset, width, height);
  clock_t end = clock();
  printf("Elapsed: %0.3fs\n", (double)(end - start) / CLOCKS_PER_SEC);
  // write output
  fh = fopen("out.bmp", "w");
  fwrite(buffer, size, 1, fh);
  fclose(fh);
  free(buffer);
}
