#include "bitmap.h"
#include <memory.h>
#include <stdlib.h>

BitmapBlock *newBitmapBloock(uint64_t offset) {
  BitmapBlock *block = calloc(sizeof(BitmapBlock), 1);
  block->offset = offset;
  block->raw = calloc(sizeof(uint32_t), BITMAP_ELEM_NUM);
  return block;
}
uint64_t bitmapBlockAdd(BitmapBlock *block, uint64_t val) {
  val -= block->offset;
  uint64_t index = val >> 5;
  if (index >= BITMAP_ELEM_NUM) {
    return 0;
  }
  return *(block->raw + index) |= 1 << (val & 0x1f);
}
uint64_t bitmapBlockHas(BitmapBlock *block, uint64_t val) {
  val -= block->offset;
  uint64_t index = val >> 5;
  if (index >= BITMAP_ELEM_NUM) {
    return 0;
  }
  return *(block->raw + index) & (1 << (val & 0x1f));
}

void freeBitmapBlock(BitmapBlock *block) {
  free(block->raw);
  free(block);
}

Bitmap *newBitmap(uint64_t items, uint64_t offset) {
  Bitmap *bitmap = calloc(sizeof(Bitmap), 1);
  uint64_t blocks = items / BITMAP_BLOCK_SIZE;
  if (items % BITMAP_BLOCK_SIZE)
    blocks++;
  bitmap->raw = calloc(sizeof(BitmapBlock *), blocks);
  bitmap->blocks = blocks;
  bitmap->offset = offset;
  return bitmap;
}

uint64_t bitmapAdd(Bitmap *bitmap, uint64_t val) {
  val -= bitmap->offset;
  uint64_t index = val / BITMAP_BLOCK_SIZE;
  if (index >= bitmap->blocks) {
    return 0;
  }
  BitmapBlock *block = *(bitmap->raw + index);
  if (!block) {
    block = newBitmapBloock(index * BITMAP_BLOCK_SIZE);
    *(bitmap->raw + index) = block;
  }
  return bitmapBlockAdd(block, val);
}
uint64_t bitmapHas(Bitmap *bitmap, uint64_t val) {
  val -= bitmap->offset;
  uint64_t index = val / BITMAP_BLOCK_SIZE;
  if (index >= bitmap->blocks) {
    return 0;
  }
  BitmapBlock *block = *(bitmap->raw + index);
  if (!block) {
    return 0;
  }
  return bitmapBlockHas(block, val);
}

void freeBitmap(Bitmap *bitmap) {
  for (uint64_t i = 0; i < bitmap->blocks; i++) {
    BitmapBlock *block = *(bitmap->raw + i);
    if (block == NULL) {
      continue;
    }
    free(block);
    *(bitmap->raw + i) = NULL;
  }
  free(bitmap);
}