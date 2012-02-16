// bytebear
// Creative Commons Attribution 3.0 License
// http://creativecommons.org/licenses/by/3.0/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "bytebear.h"

using namespace std;

class PgmWriter {
 public:
  PgmWriter(const string& filename, int width);
  ~PgmWriter();
  void write(int byte);
 private:
  FILE *f;
  int x;
  int y;
  int width;
};

PgmWriter::PgmWriter(const string& filename, int w)
  : width(w), x(0), y(0)
{
  f = fopen(filename.c_str(), "w");
  fprintf(f, "P5\n"
             "%08d\n"  // width
             "00000000\n"  // height (bytes 13:+8)
             "255\n",  // max
             width);
}

void PgmWriter::write(int byte) {
  fputc(byte, f);
  ++x;
  if (x == (width)) {
    x = 0;
    ++y;
  }
}

PgmWriter::~PgmWriter() {
  // square off the raster
  while (x != 0) write(0);
  // rewrite the height
  fseek(f, 12, SEEK_SET);
  fprintf(f, "%08d", y);
  // close
  fclose(f);
}

int main(int argc, char* argv[])
{
  ByteBear b;
  unsigned long samples = 0;
  if (argc > 1) {
    samples = atol(argv[1]);
  }

  string imgfile = argv[0];
  imgfile += ".pgm";
  PgmWriter pgm(imgfile, 1024);

  for (unsigned long t = 0; (t < samples) || (!samples); ++t) {
    int c = b.Run(t);
    putchar(c);
    pgm.write(c);
  }

  return 0;
}
