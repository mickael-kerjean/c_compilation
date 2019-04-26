# Context

I made this as a cheat sheet to showcase different style of compilation technics. The program is made of:
- src/imagegd.c: contains a function to resize an image. As a depedency, this program rely on another lirary called gd
- main.c: our main function that essentially benchmark our fast our imagegd is

# Normal compilation
``` bash
make clean
gcc -Wall -c main.c
gcc -Wall -c src/imagegd.c
gcc -o main.bin imagegd.o main.o -lgd
./main.bin
```
- 1. compile all our C code into object
- 2. link our objects together + dynamically link the gd library to our code

Pro: as simple as possible, not unecessary stuff
Cons: program won't start is gd isn't install in the user's machine

# Library: Shared
``` bash
make clean
gcc -Wall -c main.c
gcc -Wall -fPIC -c src/imagegd.c
gcc -shared -o libimage.so imagegd.o
gcc -o main.bin main.o -lgd -L. -limage
LD_LIBRARY_PATH=`pwd` ./main.bin
```

- 1. Compile all our C code into object
- 2. Create a shared library
- 3. link it all together

Pro: not much, remember this is a cheat sheet :)
Cons: Same as previous + we need to specify the path where the program will find our library

# Library: Shared and dynamic
``` bash
make clean
gcc -Wall -c main.c
gcc -Wall -c src/imagegd.c
ar -rc libimage.a imagegd.o
ranlib libimage.a
gcc -o main.bin main.o -lgd -L. -limage
./main.bin
```

- 1. Compile all our C code into object
- 2. Create a static libary from our code
- 3. link it all together by statically link our library and dynamically link the dependencies of our static library

# As a static library (.a)
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

- 1. Compile all our C code into objects
- 2. Extract the objects from the libraries we depend on and want to link statically
- 3. Create a static library from all those objects
- 4. Link all of it together with our dependencies include in our static library.

At this state we still dynamically link against some dependencies of our dependencies but we can extract all those as well and repeat the process to get a 100% static build

# Tips
```
# See symbols in a shared / static library:
nm -D /usr/local/lib/libvips.so
nm -C /usr/local/lib/libvips.a

# See the object within a library:
ar -t libimage.a
```
