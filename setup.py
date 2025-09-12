from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext
import pathlib

this_dir = pathlib.Path(__file__).parent.resolve()
long_description = (this_dir / "README.md").read_text(encoding="utf-8")

ext_modules = [
    Pybind11Extension(
        "_evoke_cpp",
        sources=[
            "cpp/evoke.cpp",
            "cpp/Escape/Graph.cpp",
            "cpp/Escape/GraphIO.cpp",
            "cpp/Escape/TriangleProgram.cpp",
        ],
        include_dirs=["cpp"],
        language="c++",
        cxx_std=17,
    ),
    Pybind11Extension(
        "_orca_cpp",
        sources=[
            "cpp/orca.cpp",
            "cpp/ORCA/orca_core.cpp"
        ],
        include_dirs=["cpp"],
        language="c++",
        cxx_std=17,
    )
]

setup(
    ext_modules=ext_modules,
    packages=["orbitsi"],
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)
