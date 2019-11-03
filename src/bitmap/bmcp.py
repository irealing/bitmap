try:
    from ._bitmap import Bitmap
except ImportError:
    from .bitmap import Bitmap


__author__ = "Memory_Leak<irealing@163.com>"


class PyBitmap:
    def __init__(self, items: int, offset: int = 0):
        self._bitmap = Bitmap(items, offset)

    def has(self, val: int):
        return self._bitmap.has(val)

    def add(self, val: int):
        return self._bitmap.add(val)
