// ryg.cc is transcribed from a screnshot posted to
// http://canonical.org/~kragen/bytebeat/
// Ownership and license unknown.

#include "bytebear.h"

ByteBear::ByteBear() {}
ByteBear::~ByteBear() {}

int ByteBear::Run(unsigned long t) {
  return ((t*("3634589"[t>>13&7]&15))/12&128)
       + (((((t>>12)^(t>>12)-2)%11*t)/4|t>>13)&127);
}
