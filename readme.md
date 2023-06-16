# Crossover standard library

This repository contains the Crossover standard library.

## Testing
Testing requires the Criterion dependency. Please make sure you have this library installed on your system. On Ubuntu: ```apt install libcriterion-dev``` (will require sudo privileges).

Besides Criterion also make sure you have lcov. ```apt install lcov``` (will require sudo privileges).

To test the library simply run:

``gcc -o test test.c ../include/*.h ../src/*.c -lcriterion -lm``

in the test folder.

To generate a report of the testing add ``--xml[=FILE]`` to the command above.