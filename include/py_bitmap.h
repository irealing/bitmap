#ifndef _PY_BITMAP_H
#define _PY_BITMAP_H
#include "bitmap.h"

typedef struct _PyBitmap {
  PyObject_HEAD;
  Bitmap *raw;
} PyBitmap;

static PyModuleDef bitmapmodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "bitmap",
    .m_doc = "Python Bitmap extension module ",
    .m_size = -1,
};
static int Bitmap_init(PyBitmap *, PyObject *, PyObject *);
static void Bitmap_dealloc(PyBitmap *);
static PyObject *Bitmap_add(PyBitmap *, PyObject *);
static PyMethodDef Bitmap_methods[];
#endif