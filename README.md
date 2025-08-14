C90 to RISC-V compiler written using C++
==============================

This project was part of the Instruction Architectures and Compilers module taught at Imperial College London.  My compiler was written using C++ and supports all basic and intermediate features described [here](docs/c_compiler.md)

The source language is pre-processed C90, and the target language is RISC-V assembly. The target environment is Ubuntu 22.04, as described [here](docs/environment_guide.md). See [here](docs/c_compiler.md) for the full set of requirements and more information about the testing environment.

Note for any current Imperial students: please do not directly copy or take from this repository as part of your coursework, or you will be caught for plagarism.

Acknowledgements
================

The coursework was originally designed by [David Thomas](https://www.southampton.ac.uk/people/5z9bmb/professor-david-thomas), who lectured this module until 2017-18. It is nowadays maintained by [John Wickerson](https://johnwickerson.github.io/), to whom any feedback should be sent. I'd like to thank Quentin Corradi, Archie Crichton, Yann Herklotz, William Huynh, James Nock, Simon Staal, and Filip Wojcicki for making many contributions to this repository over several years, such as improving the compiler-testing scripts, providing a basic "getting started" compiler, writing instructions for setting up development environments on a variety of operating systems, configuring automation using GitHub actions, and setting up coverage testing.
