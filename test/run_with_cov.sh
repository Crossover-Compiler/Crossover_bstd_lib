mkdir -p out
gcc --coverage -o out/test ./*.c ../src/*.c -I../include/*.h -lcriterion -lm
out/test
geninfo ./out/ -b ../../Crossover_bstd_lib/src/ -b ../../Crossover_bstd_lib/test/ -o ./coverage.info
genhtml coverage.info -o coverage