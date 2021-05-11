from setuptools import setup

setup(
    name="TestMatch",
    url="https://github.com/LiamBlake/TestMatch",
    author="Liam Blake",
    author_email="",
    packages=["testmatch"],
    install_require=[],
    extras_require={"dev": ["black", "flake8", "pytest", "pytest-cov", "isort"]},
    version="0.1",
    license="GNU",
    description="Python wrappers for the TestMatch C++ library.",
    long_description=open("../../README.md").read(),
)
