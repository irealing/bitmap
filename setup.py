from setuptools import Extension, setup

setup(
    name="bitmap",
    version="0.0.1",
    author="Memory_Leak",
    author_email="irealing@163.com",
    ext_modules=[
        Extension(
            "bitmap._bitmap",
            ["src/bitmap.c", "src/py_bitmap.c"], include_dirs=["include"]
        )
    ]
)
