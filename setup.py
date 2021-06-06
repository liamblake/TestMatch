from setuptools import find_packages
from skbuild import setup

setup(
    name="testmatch",
    url="https://github.com/LiamBlake/TestMatch",
    author="Liam Blake",
    author_email="",
    packages=find_packages("src"),
    package_dir={"": "src"},
    install_requires=["rich"],
    extras_require={"dev": ["black", "flake8", "pytest", "pytest-cov", "isort"]},
    cmake_args=["-DBUILD_PYTHON=ON"],
    cmake_install_dir="src/testmatch",
    include_package_data=True,
    version="0.1",
    license="GNU",
    description="Cricket simulation built on historical data.",
    long_description=open("README.md").read(),
)
