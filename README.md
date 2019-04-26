*Compilation cheat sheet*


Normal compilation
``` bash
make clean
gcc -Wall -c main.c
gcc -Wall -c src/imagegd.c
gcc -o main.bin imagegd.o main.o -lgd
./main.bin
```

As a shared library:
``` bash
make clean
gcc -Wall -c main.c
gcc -Wall -fPIC -c src/imagegd.c
gcc -shared -o libimage.so imagegd.o
gcc -o main.bin main.o -lgd -L. -limage
LD_LIBRARY_PATH=`pwd` ./main.bin
```

Mix of static and dynamic:
``` bash
make clean
gcc -Wall -c main.c
gcc -Wall -c src/imagegd.c
ar -rc libimage.a imagegd.o
ranlib libimage.a
gcc -o main.bin main.o -lgd -L. -limage
./main.bin
```

As a static library:
``` bash
make clean
gcc -Wall -c src/imagegd.c
ar x /usr/local/lib/libgd.a
ar -rc libimage.a *.o
ranlib libimage.a
gcc -Wall -c main.c
gcc -o main.bin main.o -lm -ljpeg -L. -limage
./main.bin
```

*Tips:*
- `nm -D /usr/local/lib/libvips.so`: see symbols in shared library
- `nm -C /usr/local/lib/libvips.a`: see symbols in a static library
- `ar -t libimage.a`: see object file in a library
