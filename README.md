# Crossover standard library

This repository contains the Crossover standard library.

## Installation
There is a convenient installation script `install.sh` included in the project root directory. This will build and install the shared BSTD library on your system.
You might need to make this file executable
(`chmod +x install.sh`)
and you will need to run it with `sudo`. The scrips simply automates the steps listed below.

### Manual installation

To install the BSTD as a shared library, you can use cmake and make the `install` target. From the project root:
`cd build && cmake .. && make install`
The shared library will be installed in the GNU install directories (i.e. `/usr/local/lib`). You will probably need to `sudo` the `make` step.

You will have to run `ldconfig` to make your system aware of the newly installed library (you'll have to be able to `sudo` this too).

## Testing
Testing requires the Criterion dependency. Please make sure you have this library installed on your system. On Ubuntu: ```apt install libcriterion-dev``` (will require sudo privileges).

Besides Criterion also make sure you have lcov. ```apt install lcov``` (will require sudo privileges).

To test the library simply run:

``gcc -o test test.c ../include/*.h ../src/*.c -lcriterion -lm``

in the test folder.

To generate a report of the testing add ``--xml[=FILE]`` to the command above.