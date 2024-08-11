#define RED0 0x00
#define RED1 0x20
#define RED2 0x40
#define RED3 0x60
#define RED4 0x80
#define RED5 0xa0
#define RED6 0xc0
#define RED7 0xe0
#define GREEN0 0x00
#define GREEN1 0x04
#define GREEN2 0x08
#define GREEN3 0x0c
#define GREEN4 0x10
#define GREEN5 0x14
#define GREEN6 0x18
#define GREEN7 0x1c
#define BLUE0 0x00
#define BLUE1 0x01
#define BLUE2 0x02
#define BLUE3 0x03

unsigned char quantize(unsigned char red, unsigned char green,
                       unsigned char blue) {

  unsigned char out = 0;

  unsigned char red0 = red < 0x20 ? RED0 : 0;
  unsigned char red1 = red > 0x20 && red < 0x40 ? RED1 : 0;
  unsigned char red2 = red > 0x40 && red < 0x60 ? RED2 : 0;
  unsigned char red3 = red > 0x60 && red < 0x80 ? RED3 : 0;
  unsigned char red4 = red > 0x80 && red < 0xa0 ? RED4 : 0;
  unsigned char red5 = red > 0xa0 && red < 0xc0 ? RED5 : 0;
  unsigned char red6 = red > 0xc0 && red < 0xe0 ? RED6 : 0;
  unsigned char red7 = red > 0xe0 ? RED7 : 0;

  out += red0 + red1 + red2 + red3 + red4 + red5 + red6 + red7;



  unsigned char green0 = green < 0x20 ? GREEN0 : 0;
  unsigned char green1 = green > 0x20 && green < 0x40 ? GREEN1 : 0;
  unsigned char green2 = green > 0x40 && green < 0x60 ? GREEN2 : 0;
  unsigned char green3 = green > 0x60 && green < 0x80 ? GREEN3 : 0;
  unsigned char green4 = green > 0x80 && green < 0xa0 ? GREEN4 : 0;
  unsigned char green5 = green > 0xa0 && green < 0xc0 ? GREEN5 : 0;
  unsigned char green6 = green > 0xc0 && green < 0xe0 ? GREEN6 : 0;
  unsigned char green7 = green > 0xe0 ? GREEN7 : 0;

  out += green0 + green1 + green2 + green3 + green4 + green5 + green6 + green7;


  unsigned char blue0 = blue < 0x40 ? BLUE0 : 0;
  unsigned char blue1 = blue > 0x40 && blue < 0x80 ? BLUE1 : 0;
  unsigned char blue2 = blue > 0x80 && blue < 0xc0 ? BLUE2 : 0;
  unsigned char blue3 = blue > 0xc0 ? BLUE3 : 0;

  out += blue0 + blue1 + blue2 + blue3;

  return out;
}

