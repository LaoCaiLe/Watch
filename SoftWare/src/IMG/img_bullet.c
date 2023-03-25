#include "lvgl/lvgl.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_IMG_BULLET
#define LV_ATTRIBUTE_IMG_IMG_BULLET
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_IMG_IMG_BULLET uint8_t img_bullet_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Alpha 8 bit, Red: 3 bit, Green: 3 bit, Blue: 2 bit*/
  0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xfb, 0x3b, 0xfa, 0x4c, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xff, 0x2c, 0xcc, 0xeb, 0xcc, 0xfc, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xf5, 0x9c, 0xc8, 0xff, 0xc8, 0xff, 0xf1, 0xb7, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xf6, 0x8c, 0xc8, 0xff, 0xcc, 0xff, 0xcc, 0xcc, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xf6, 0x8c, 0xc8, 0xff, 0xc8, 0xff, 0xf1, 0xbb, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xf5, 0x9c, 0xc8, 0xff, 0xc8, 0xff, 0xf1, 0xbb, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xf6, 0x84, 0xc8, 0xff, 0xc8, 0xff, 0xf1, 0xa7, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xff, 0x14, 0xcc, 0xfc, 0xc8, 0xff, 0xfb, 0x40, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xf6, 0x7b, 0xf1, 0xc3, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xfa, 0x30, 0xf6, 0x5f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9d, 0xff, 0x00, 0x75, 0xf6, 0x3b, 0x13, 0xee, 0x4c, 0xbe, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb8, 0xf6, 0x2c, 0x44, 0xd3, 0xeb, 0x43, 0xd3, 0xfc, 0x1a, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xab, 0xdc, 0x9c, 0xe0, 0xc1, 0xff, 0x20, 0xc2, 0xff, 0x07, 0xdc, 0xb7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xed, 0xe4, 0x8c, 0x40, 0xc2, 0xff, 0x80, 0xca, 0xff, 0x84, 0xd3, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xed, 0xe4, 0x8c, 0x40, 0xc2, 0xff, 0x80, 0xca, 0xff, 0xe6, 0xd3, 0xbb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8b, 0xdc, 0x9c, 0x20, 0xc2, 0xff, 0x80, 0xca, 0xff, 0xe6, 0xd3, 0xbb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xe5, 0x84, 0x40, 0xc2, 0xff, 0x20, 0xc2, 0xff, 0x6a, 0xdc, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb7, 0xf6, 0x14, 0x22, 0xd3, 0xfc, 0x20, 0xc2, 0xff, 0x34, 0xee, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xff, 0x00, 0x6f, 0xe5, 0x7b, 0x49, 0xdc, 0xc3, 0xf9, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xff, 0x00, 0x14, 0xee, 0x30, 0x4f, 0xed, 0x5f, 0xb8, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit  BUT the 2  color bytes are swapped*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x9d, 0x00, 0xf6, 0x75, 0x3b, 0xee, 0x13, 0x4c, 0xff, 0xbe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf6, 0xb8, 0x2c, 0xd3, 0x44, 0xeb, 0xd3, 0x43, 0xfc, 0xff, 0x1a, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0xab, 0x9c, 0xc1, 0xe0, 0xff, 0xc2, 0x20, 0xff, 0xdc, 0x07, 0xb7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe4, 0xed, 0x8c, 0xc2, 0x40, 0xff, 0xca, 0x80, 0xff, 0xd3, 0x84, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe4, 0xed, 0x8c, 0xc2, 0x40, 0xff, 0xca, 0x80, 0xff, 0xd3, 0xe6, 0xbb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0x8b, 0x9c, 0xc2, 0x20, 0xff, 0xca, 0x80, 0xff, 0xd3, 0xe6, 0xbb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe5, 0x0e, 0x84, 0xc2, 0x40, 0xff, 0xc2, 0x20, 0xff, 0xdc, 0x6a, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf6, 0xb7, 0x14, 0xd3, 0x22, 0xfc, 0xc2, 0x20, 0xff, 0xee, 0x34, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x7c, 0x00, 0xe5, 0x6f, 0x7b, 0xdc, 0x49, 0xc3, 0xf6, 0xf9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x7c, 0x00, 0xee, 0x14, 0x30, 0xed, 0x4f, 0x5f, 0xf6, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 32
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xec, 0xf2, 0xfd, 0x00, 0xaa, 0xcb, 0xef, 0x3b, 0x9a, 0xc0, 0xeb, 0x4c, 0xf1, 0xf6, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0xd4, 0xf3, 0x2c, 0x1e, 0x68, 0xcf, 0xeb, 0x1b, 0x67, 0xce, 0xfc, 0xd1, 0xe1, 0xf6, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5a, 0x93, 0xdc, 0x9c, 0x00, 0x3e, 0xc2, 0xff, 0x00, 0x45, 0xc3, 0xff, 0x3b, 0x81, 0xd7, 0xb7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0x9d, 0xe0, 0x8c, 0x00, 0x48, 0xc3, 0xff, 0x00, 0x51, 0xc7, 0xff, 0x1f, 0x6f, 0xd0, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0x9c, 0xe0, 0x8c, 0x00, 0x48, 0xc4, 0xff, 0x00, 0x4f, 0xc5, 0xff, 0x33, 0x7b, 0xd4, 0xbb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0x92, 0xdb, 0x9c, 0x00, 0x46, 0xc4, 0xff, 0x00, 0x4f, 0xc6, 0xff, 0x34, 0x7c, 0xd4, 0xbb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6e, 0xa1, 0xe2, 0x84, 0x00, 0x4a, 0xc4, 0xff, 0x00, 0x45, 0xc3, 0xff, 0x4f, 0x8d, 0xda, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xba, 0xd3, 0xf1, 0x14, 0x0f, 0x66, 0xce, 0xfc, 0x00, 0x43, 0xc2, 0xff, 0xa3, 0xc3, 0xeb, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe2, 0xee, 0xf8, 0x00, 0x7a, 0xab, 0xe3, 0x7b, 0x46, 0x8a, 0xda, 0xc3, 0xc9, 0xdc, 0xf4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdf, 0xeb, 0xf7, 0x00, 0x9d, 0xc1, 0xea, 0x30, 0x79, 0xa9, 0xe5, 0x5f, 0xbd, 0xd4, 0xf1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
};

const lv_img_dsc_t img_bullet = {
  .header.always_zero = 0,
  .header.w = 8,
  .header.h = 10,
  .data_size = 80 * LV_IMG_PX_SIZE_ALPHA_BYTE,
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .data = img_bullet_map,
};