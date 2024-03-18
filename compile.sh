gcc -DLIBSAIS_OPENMP=1 libsais/src/libsais64.c libsais/src/libsais16.c libsais/src/libsais.c main.c -I libsais/include -fopenmp
