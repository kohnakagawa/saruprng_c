#ifndef SARUPRNG_H
#define SARUPRNG_H

#include <math.h>
#include <stdint.h>

#define LCGC 0x2600e1f7
#define CTpow_LCGA_1 1273716057
#define CTpowseries_LCGA_1 1
#define oWeylOffset 0x8009d14b
#define oWeylPeriod 0xda879add

#undef  M_PI
#define M_PI    3.14159265358979323846
#define TWO_N31 4.65661287307739257812e-10

#define advanceLCG(state) state = CTpow_LCGA_1 * state + LCGC * CTpowseries_LCGA_1
#define advanceWeyl(wstate) wstate += oWeylOffset + ((((int32_t)wstate) >> 31) & oWeylPeriod)

typedef struct Saru_t {
  uint32_t state;
  uint32_t wstate;
} Saru;

static inline void saru_init(Saru* self,
                             uint32_t seed1,
                             uint32_t seed2,
                             uint32_t seed3) {
  seed3 ^= (seed1 << 7) ^ (seed2 >> 6);
  seed2 += (seed1 >> 4) ^ (seed3 >> 15);
  seed1 ^= (seed2 << 9) + (seed3 << 8);
  seed3 ^= 0xA5366B4D * ((seed2 >> 11) ^ (seed1 << 1));
  seed2 += 0x72BE1579 * ((seed1 << 4)  ^ (seed3 >> 16));
  seed1 ^= 0X3F38A6ED * ((seed3 >> 5)  ^ (((int32_t)seed2) >> 22));
  seed2 += seed1 * seed3;
  seed1 += seed3 ^ (seed2 >> 2);
  seed2 ^= ((int32_t)seed2) >> 17;
  self->state  = 0x79dedea3 * (seed1 ^ (((int32_t)seed1) >> 14));
  self->wstate = (self->state + seed2) ^ (((int32_t)self->state) >> 8);
  self->state  = self->state + (self->wstate * (self->wstate ^ 0xdddf97f5));
  self->wstate = 0xABCB96F7 + (self->wstate >> 1);
}

static inline uint32_t saru_u32(Saru* self) {
  advanceLCG(self->state);
  advanceWeyl(self->wstate);
  const uint32_t v = (self->state ^ (self->state >> 26)) + self->wstate;
  return (v ^ (v >> 20)) * 0x6957f5a7;
}

static inline double saru_uniform(Saru* self) {
  return ((double)((int32_t)(saru_u32(self) >> 1)) + 0.5) * TWO_N31;
}

static inline double saru_normal(Saru* self) {
  return sqrt(-2.0 * log(saru_uniform(self)))
    * cos(2.0 * M_PI * saru_uniform(self));
}

#undef LCGC
#undef CTpow_LCGA_1
#undef CTpowseries_LCGA_1
#undef oWeylOffset
#undef oWeylPeriod
#undef M_PI
#undef TWO_N31

#undef advanceLCG
#undef advanceWeyl

#endif
