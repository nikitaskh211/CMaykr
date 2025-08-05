# CMaykr

This is a simple make and build tool for complex applications.

# Common questions and answers

## What is it ?

This program is written within one .c source file which is compatible with any common C compiler. To use it you must a C compiler installed. Although the name might mislead you by being similar to `CMake` you should know that it is not compatible.

## How to use it ?

In order to create a project you must create a configuration text file `config.cm` (or any other kind of `.cm` file that will contain configuration). In order to make this step easier for everyone this project will feature extensive documentation on the matter of configuration.
After the configuration file is created you only have to write ``cmaykr [flag] [working directory]`` command in order to build everything within working directory.

## How it works ?

I guess it works as any other similar build system. In case you are unfamiliar with how common build systems work here is a quick rundown of how things work 'under the hood'. A compiler for C has this usage:
``[compiler] [flags] [source files] -o [executable name]``.
Instead of compiling into an executable we can modify the process a bit:
- We know what source files we have to compile we just have to recieve time of their latest modification.
- Based on the time of latest modification we compile object files for them using:
    ``[compiler] -c [flags] [source files] -o [object files]``
- After the object files are compiled we link every object into an executable using:
    ``[compiler] [object files] -o [executable]``

We will also add a feature to log history of changes between files.

All the source code must be self-explanatory so there must be no confusion.
