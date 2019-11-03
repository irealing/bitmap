from setuptools import Extension, setup

setup(
    name="bitmap",
    ext_modules=[
        Extension("bitmap._bitmap", ["src/bitmap.c", "src/py_bitmap.c"],
                  include_dirs=["include"])
    ]
)
