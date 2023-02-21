#ifndef BITS_H
#define BITS_H

#include "types.h"

// // clang-format off
// inline u8 u8_ll(u32 v) { return  v        & 0xff; }
// inline u8 u8_lh(u32 v) { return (v >> 8)  & 0xff; }
// inline u8 u8_hl(u32 v) { return (v >> 16) & 0xff; }
// inline u8 u8_hh(u32 v) { return (v >> 24) & 0xff; }

// inline u16 u16_l(u32 v) { return  v        & 0xffff; }
// inline u16 u16_h(u32 v) { return (v >> 16) & 0xffff; }

// inline u16 join2_u8(u8 h, u8 l)    { return (h << 8)  | l; }
// inline u32 join2_u16(u16 h, u16 l) { return (h << 16) | l; }
// // clang-format on

// inline u32 join4_u8(u8 hh, u8 hl, u8 lh, u8 ll)
// {
//   return (hh << 24) | (hl << 16) | (lh << 8) | ll;
// }

#endif