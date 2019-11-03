"""Python版Bitmap"""
import array


__author__ = "Memory_Leak<irealing@163.com>"


class BitmapBlock(object):
    BLOCKSIZE = 1024*1024*8

    def __init__(self, offset: int = 0):
        self.offset = offset
        self.raw = array.array("L", map(lambda _: 0), range(self.BLOCKSIZE))

    def add(self, val: int) -> int:
        val -= self.offset
        index = val >> 5
        if val < 0 or val >= len(self.raw):
            return 0
        self.raw[index] |= (1 << (val & 0x1f))
        return 1

    def has(self, val: int) -> bool:
        val -= self.offset
        index = val >> 5
        if val < 0 or val >= len(self.raw):
            return False
        return (self.raw[index] & 1 << (val & 0x1f)) > 0


class Bitmap:
    def __init__(self, items: int, offset: int = 0):
        self.offset = 0
        blocks = items//BitmapBlock.BLOCKSIZE
        if items % BitmapBlock.BLOCKSIZE:
            blocks += 1
        self.raw = list(map(lambda x: None, range(blocks)))

    def add(self, val: int) -> int:
        val -= self.offset
        index = val//BitmapBlock.BLOCKSIZE
        if index < 0 or not index >= len(self.raw):
            return 0
        block = self.raw[index]
        return 0 if not block else block.add(val)

    def has(self, val: int) -> bool:
        val -= self.offset
        index = val//BitmapBlock.BLOCKSIZE
        if index < 0 or not index >= len(self.raw):
            return False
        block = self.raw[index]
        return False if not block else block.has(val)
