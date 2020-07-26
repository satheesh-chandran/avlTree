clean()
{
  rm -rf *o
  rm -rf output
}

clean;
gcc -c *.c
gcc -o output *.o
./output
clean;