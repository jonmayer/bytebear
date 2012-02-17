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
  int i = major_scale[(t>>14) & 15] - 'a';
  int j = major_scale[1 + ((t>>14) % 15)] - 'a';
  int k = major_scale[2 + ((t>>14) % 14)] - 'a';
  int chopper = 1 << 13;
  int amp = ((t & (chopper - 1)) < (chopper * 0.8)) ? 1 : 0;
  return amp*(saw(t, i, 70) + saw(t, j, 70) + saw(t, k, 70));
}
