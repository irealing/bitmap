#ifndef _BITMAP_H
#define _BITMAP_H
#include <stdint.h>

#define BITMAP_ELEM_NUM 0x40000
#define BITMAP_BLOCK_SIZE 0x800000

typedef struct _BitmapBlock {
  uint64_t offset;
  uint32_t *raw;
  uint32_t counter;
} BitmapBlock;

BitmapBlock *newBitmapBloock(uint64_t);

uint64_t bitmapBlockAdd(BitmapBlock *, uint64_t);

uint64_t bitmapBlockHas(BitmapBlock *, uint64_t);

void freeBitmapBlock(BitmapBlock *);

typedef struct _bitmap {
  uint64_t offset;
  uint64_t blocks;
  BitmapBlock **raw;
} Bitmap;

Bitmap *newBitmap(uint64_t, uint64_t);

uint64_t bitmapAdd(Bitmap *, uint64_t);

uint64_t bitmapHas(Bitmap *, uint64_t);

void freeBitmap(Bitmap *);

#endif