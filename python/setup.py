from setuptools import setup

setup(
    name="TestMatch",
    url="https://github.com/LiamBlake/TestMatch",
    author="Liam Blake",
    author_email="",
    packages=["testmatch"],
    install_requires=[],
    extra_requires={"dev": ["black", "flake8", "pytest", "pytest-cov"]},
    version="0.1",
    license="GNU",
    description="Python wrappers for the TestMatch C++ library.",
    long_description=open("../README.md").read(),
)
