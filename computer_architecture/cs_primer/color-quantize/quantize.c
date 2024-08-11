

unsigned char quantize(unsigned char red, unsigned char green,
                       unsigned char blue) {

  unsigned char out = 0;

  out |= (red >> 5) << 5;

  out |= (green >> 5) << 2;

  out |= blue >> 6;

  return out;
}

