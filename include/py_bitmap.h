#ifndef _PY_BITMAP_H
#define _PY_BITMAP_H
#include "bitmap.h"
#include <Python.h>

typedef struct _PyBitmap {
  PyObject_HEAD Bitmap *raw;
} PyBitmap;

static PyModuleDef bitmapmodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "bitmap",
    .m_doc = "Python Bitmap extension module ",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit__bitmap(void);

static int Bitmap_init(PyBitmap *, PyObject *, PyObject *);

static void Bitmap_dealloc(PyBitmap *);

static PyObject *Bitmap_add(PyBitmap *, PyObject *);

static PyObject *Bitmap_has(PyBitmap *self, PyObject *arg);

static PyMethodDef Bitmap_methods[] = {
    {"add", (PyCFunction)Bitmap_add, METH_VARARGS},
    {"has", (PyCFunction)Bitmap_has, METH_VARARGS},
    {NULL},
};
#endif
