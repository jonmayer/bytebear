// ryg.cc is transcribed from a screnshot posted to
// http://canonical.org/~kragen/bytebeat/

#include "bytebear.h"

ByteBear::ByteBear() {}
ByteBear::~ByteBear() {}

int fn(unsigned long t, int i) {
  int x =
         ((t*("3634589"[t>>13&7]&15))/12&128)
       + (((((t>>12)^(t>>12)-2)%11*t)/4|t>>13)&127);
  if (i > 0) x += (70 * (255&fn(t - 32*1024, i-1))) / 100;
  return x;
}

int ByteBear::Run(unsigned long t) {
  fn(t,5);
}
