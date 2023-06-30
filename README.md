# Crossover standard library

This repository contains the Crossover standard library.

## Installation
To install the BSTD as a shared library, you can use cmake with the `install` target from the project root:
`cmake --target install`
The shared library will be installed in the GNU install directories in `/usr/local`. You will need to `sudo` this.

You will have to run `ldconfig` to make your system aware of the newly installed library.

## Testing
Testing requires the Criterion dependency. Please make sure you have this library installed on your system. On Ubuntu: ```apt install libcriterion-dev``` (will require sudo privileges).

Besides Criterion also make sure you have lcov. ```apt install lcov``` (will require sudo privileges).

To test the library simply run:

``gcc -o test test.c ../include/*.h ../src/*.c -lcriterion -lm``

in the test folder.

To generate a report of the testing add ``--xml[=FILE]`` to the command above.