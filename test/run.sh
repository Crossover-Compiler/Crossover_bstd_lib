mkdir -p out
gcc -o out/test ./*.c ../include/*.h ../src/*.c -lcriterion -lm
out/test