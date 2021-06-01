from setuptools import find_packages, setup

setup(
    name="testmatch",
    url="https://github.com/LiamBlake/TestMatch",
    author="Liam Blake",
    author_email="",
    packages=find_packages("src"),
    package_dir={"": "src"},
    install_requires=["rich"],
    extras_require={"dev": ["black", "flake8", "pytest", "pytest-cov"]},
    version="0.1",
    license="GNU",
    description="Cricket simulation built on historical data.",
    long_description=open("README.md").read(),
)
