# MakefileExamples

Several generic makefile examples for C, such as
- automatic compilation of sub-folders
- recursive compilation of sub-makefiles, similar to the linux kernel.

If you want to know more about makefile, please visit [GNU make](http://www.gnu.org/software/make/manual/make.html). If you need the Chinese version, please visit [how-to-write-makefile](https://github.com/seisman/how-to-write-makefile).

## Automatic Folder

**Features:**

- Automatically find all source files and header file search paths in the specified code directory.
- Automatically generate dependent files, only compile the files that have been modified recently and ensure that they are correct.
- Clear all compiled files.

**How to use:**

- `BUILD_OUTPUT` - Specify the directory where the compiled object files and dependent files are located, if not specified, the default is `./` .
- `BUILD_SRC` - Specify the code search path, it will compile all searched files with the suffix of `.c` , and include the search path of all header files with the suffix of `.h` . If not specified, the default is `./` .
- `BUILD_EXE` - Specify the file name of the compiled executable file.
- `INCLUDES` - Usually do not need to be specified, because it will be automatically searched, but it can be used to add a header file search path other than the code search path.
- `LD_DIRS` - Specify the library search directory.
- `LD_LIBS` - Specify the required libraries.

**Test:**

```txt
xhr@ubuntu:~/MakefileExamples$ cd automatic/
xhr@ubuntu:~/MakefileExamples/automatic$ make
    CC  _build/./foo/bar/proc.o
    CC  _build/./main.o
    CC  _build/./src/good.o
    LD  test.exe

>>>  successful !!

xhr@ubuntu:~/MakefileExamples/automatic$ ./test.exe
hello
thread_task
print_good: GOOD_GOOD
AUTHOR: xhr
xhr@ubuntu:~/MakefileExamples/automatic$ ls
_build  foo  include  main.c  Makefile  src  test.exe
xhr@ubuntu:~/MakefileExamples/automatic$ make clean
xhr@ubuntu:~/MakefileExamples/automatic$ ls
foo  include  main.c  Makefile  src
```

## Recursive Folder

**Features:**

- Use method similar to linux kernel.
- You need to add sub-makefiles(`BUILD.mk`) under each source file directory to determine which directories or source files need to be compiled.
- Only compile files that have been modified.

**How to use:**

Only describe the differences from `Automatic Folder`.

- There is no `BUILD_SRC`, need to use the `BUILD.mk` to specify compilation of contents.
- `INCLUDES` - Do not use relative paths, use `ROOT_DIR` as a prefix.

**Test:**

```txt
xhr@ubuntu:~/MakefileExamples$ cd recursive/
xhr@ubuntu:~/MakefileExamples/recursive$ make
    CC  ./main.o
    CC  foo/bar/deep/deeper/deep.o
    CC  foo/bar/proc.o
    LD  foo/bar/_built-in.a
    CC  foo/bar/deep/deep.o
    LD  foo/bar/deep/_built-in.a
    LD  foo/_built-in.a
    CC  src/good.o
    LD  src/_built-in.a
    LD  ./_built-in.a
    LD  test.exe

>>>  successful !!

xhr@ubuntu:~/MakefileExamples/recursive$ ./test.exe
hello main: GOOD GOOD
thread_task
print_good: GOOD GOOD
The more deeper file depth.
You can see the sub-makefile example in `foo/BUILD.mk`.
AUTHOR: xhr
xhr@ubuntu:~/MakefileExamples/recursive$ ls
_build  BUILD.mk  foo  include  main.c  Makefile  src  test.exe
xhr@ubuntu:~/MakefileExamples/recursive$ make clean
xhr@ubuntu:~/MakefileExamples/recursive$ ls
BUILD.mk  foo  include  main.c  Makefile  src
```
