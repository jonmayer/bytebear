// major scales
// jonathan.mayer@gmail.com

#include "bytebear.h"
#include <math.h>

ByteBear::ByteBear() {}
ByteBear::~ByteBear() {}

const double fsamp = 44100.0;
const double C = 110.0;
const double ratio = pow(2.0, 1.0/12.0);
inline double period_in_samples(int ord) {
  double freq = C * pow(ratio, ord);
  // samples/sec / cycles/sec = samples/cycle
  double samples = fsamp / freq;
  return samples;
}

inline int saw(unsigned long t, int ord, int amp) {
  int p = period_in_samples(ord);
  int o = (t % p) * amp / p;
}

int ByteBear::Run(unsigned long t) {
  //                                2212221 1222122
  static const char* major_scale = "acefhjlmmljhfeca";
  int ord = major_scale[(t>>13) % 16] - 'a';
  int ord2 = major_scale[(t>>15) % 16] - 'a' - 24;
  int chopper = 1 << 12;
  int amp = ((t & (chopper - 1)) < (chopper * 0.5)) ? 1 : 0;
  return amp*saw(t, ord, 120) + saw(t, ord2, 250-120);
}
