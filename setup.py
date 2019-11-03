from setuptools import Extension, setup, find_packages

setup(
    name="bitmap",
    version="0.0.1",
    author="Memory_Leak",
    author_email="irealing@163.com",
    packages=find_packages('src'),
    package_dir={"": "src"},
    ext_modules=[
        Extension(
            "bitmap._bitmap",
            ["src/bitmap.c", "src/py_bitmap.c"], include_dirs=["include"]
        )
    ]
)
