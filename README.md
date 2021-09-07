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
