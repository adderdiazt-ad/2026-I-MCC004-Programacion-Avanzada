from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

ext_modules = [
    Pybind11Extension(
        "_matrix",
        ["topy.cpp"],
        cxx_std=20,
    ),
]

setup(
    name="_matrix",
    version="1.0",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)