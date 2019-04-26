#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "gd.h"

int image_resize(const char *input, const char *output, int size, int crop, int quality, int exif) {
  FILE *outfile;
  FILE *infile;

  if ((infile = fopen(input, "rb")) == NULL) {
    fprintf(stderr, "error while opening %s - '%s'\n", input, strerror(errno));
    return 1;
  }
  gdImagePtr im = gdImageCreateFromJpeg(infile);
  fclose(infile);

  if ((outfile = fopen(output, "wb")) == NULL) {
    fprintf(stderr, "can't open %s\n", input);
    return 1;
  }

  im = gdImageScale(im, size, size);
  
  gdImageJpeg(im, outfile, -1);
  fclose(outfile);
  gdImageDestroy(im);
  return 0;
}
