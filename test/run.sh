mkdir -p out
gcc -o out/test ./*.c ../src/*.c -I../include/*.h -lcriterion -lm
out/test >> /dev/null
