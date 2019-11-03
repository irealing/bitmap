#include "py_bitmap.h"

static int Bitmap_init(PyBitmap *self, PyObject *args, PyObject *kw) {
  uint64_t items = 0, offset = 0;
  if (!PyArg_ParseTuple(args, "KK", &items, &offset)) {
    return -1;
  }
  self->raw = newBitmap(items, offset);
  return 0;
}

static void Bitmap_dealloc(PyBitmap *self) {
  freeBitmap(self->raw);
  Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyTypeObject BitmapType = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "Bitmap",
    .tp_doc = "Python Bitmap Extension",
    .tp_basicsize = sizeof(PyBitmap),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)Bitmap_init,
    .tp_dealloc = (destructor)Bitmap_dealloc,
    .tp_methods = Bitmap_methods,
};

PyMODINIT_FUNC PyInit__bitmap(void) {
  PyObject *m = NULL;
  if (PyType_Ready(&BitmapType) < 0) {
    return NULL;
  }
  m = PyModule_Create(&bitmapmodule);
  if (m == NULL) {
    return NULL;
  }
  Py_INCREF(&BitmapType);
  if (PyModule_AddObject(m, "Bitmap", (PyObject *)&BitmapType) < 0) {
    Py_DECREF(&BitmapType);
    Py_DECREF(m);
    return NULL;
  }
  return m;
}

static PyObject *Bitmap_add(PyBitmap *self, PyObject *args) {
  uint64_t val = 0;
  if (!PyArg_ParseTuple(args, "K", &val)) {
    return Py_None;
  }
  return PyLong_FromUnsignedLongLong(bitmapAdd(self->raw, val));
}
static PyObject *Bitmap_has(PyBitmap *self, PyObject *arg) {
  uint64_t val = 0;
  if (!PyArg_ParseTuple(arg, "K", &val)) {
    return PyLong_FromUnsignedLongLong(0);
  }
  return PyLong_FromUnsignedLongLong(bitmapHas(self->raw, val));
}
