[![Build Status](https://travis-ci.org/silvuss/silvuss-forcom.svg?branch=master)](https://travis-ci.org/silvuss/silvuss-forcom)

# forcom – Format comments

forcom (FORmat COMments) is a utility that allows the user format [comments](https://en.wikipedia.org/wiki/Comment_(computer_programming)) that a given file contains. The file's content may be any content that contains comments (e.g. source code).

**Read before use:** This utility **is not** intended to be used according to the purpose described above. You may use it **only** to test whether the code is written the way it is expected to be (i.e. it produces expected results) and **only** when you know what the code will really do. For details, see the section "[Disclaimers](#disclaimers)" of this README.

## Table of contents

1. [Copyright note](#copyright-note)
2. [Disclaimers](#disclaimers)
3. [How to install and run this utility?](#how-to-install-and-run-this-utility)
4. [How does this utility work (in general)?](#how-does-this-utility-work-in-general)
5. [Example](#example)
6. [Environment, tools and technologies used](#environment-tools-and-technologies-used)
7. [Details](#details)

## Copyright note

Note that this "forcom" project (this repository) has currently **no license**, as explained in [this GitHub guide on licensing projects](https://choosealicense.com/no-permission/).

For your convenience, I am including below a quote from that site:

> When you make a creative work (which includes code), the work is under exclusive copyright by default. Unless you include a license that specifies otherwise, nobody else can use, copy, distribute, or modify your work without being at risk of take-downs, shake-downs, or litigation. Once the work has other contributors (each a copyright holder), “nobody” starts including you.

Also note that I can add a lincese in the future if it would be relevant to the needs of this project.

## Disclaimers

**This application is an example application that is not intended to be run.** Its purpose is only to show code that is known to work. While probably nothing dangerous would happen, you may run it only under your own responsibility.

Although I have made efforts to make it work as intended and described, it is not a "proffessional" application. Specifically, it was not tested in terms of separate unit tests or similar. It was tested to work only on one platform. Specifically, it deals with memory, and that never may be safe at all. For details on the platform, see the section ["Environment, tools and technologies used"](#environment-tools-and-technologies-used) of this README.

## How to install and run this utility?

This utility is intended to be run in the console, on a Linux system. Before running, it has to be compiled.

### Compiling

There are two formal prerequisites to be able to successfully compile this utility:
1. In order to interpret the `makefile` file, the operating system (Linux or other) must provide an implementation of the [make utility](https://en.wikipedia.org/wiki/Make_(software)).
2. The shell that you will use has to provide three commands: the [rm command](https://en.wikipedia.org/wiki/Rm_(Unix)), the [rmdir command](https://en.wikipedia.org/wiki/Rmdir) and the [mkdir command](https://en.wikipedia.org/wiki/Mkdir).

There are several ways and many tools to compile a C program having its source files.<sup>1</sup> In the case of this utility, the simplest way will using the `make` command (provided by the aforementioned make utility). All the supported commands are listed in the following table:

|No.|Command|Description|Output files|
|-|-|-|-|
|1|`make`|Default. Causes the utility to be compiled using a compiler available by the `gcc` command. Creates the `bin` subdirectory if it does not exist.|One executable file `bin/forcom`|
|2|`make default`|(same as `make`)|(same as `make`)|
|3|`make debug`|Causes the utility to be compiled using a compiler available by the `gcc` command with some debug parameters. For the list of parameters, see the `makefile` file. Creates the `bin_debug` directory if it does not exist.|One executable file `bin_debug/forcom_debug` and one object file (extension `.o`) for each of the source files (extension `.c`) in the `src` subdirectory|
|4|`make clean`|Removes all the files and directories that were created either by executing `make` or `make debug`. If some of the directories or files are not intended to be removed, do not use this command – instead, if needed, remove the appropriate files yourself.|---|

To compile, open the terminal, go into the utility main directory and execute one of the commands listed in the table above.

### Running

In the case of this utility, the simplest way will be opening the terminal, going into the utility's main directory and executing the following command (`$` is the user prompt):

```
$ ./bin/forcom FILE_1 FILE_2
```

where:
- `FILE_1` is the input file path; it should be path to a readable file containing comments to format.
- `FILE_2` is the output file path; it should be path to an output file that will be created.

**Tip:** If only names of the files will be specified, it will be assumed that the path for each of them is the path to the current directory.

If any errors will occur during compilation, it probably means that the platform that it is running on does not meet the prerequisites for compilation. If any errors will occur during running, it probably means that the platform that it is running on does not support some functions of this utility, or some functions are supported in a way that this utility cannot handle. For details on which platform this utility was tested (i.e. runs successfully), see the section ["Tools and technologies used"](#tools-and-technologies-used) of this readme.

---

<sup>1</sup> On the internet, it is generally mentioned that you should compile a C program **separately for each [platform](https://en.wikipedia.org/wiki/Computing_platform)** that you want to run the program on (for reasons, see for example [this Stack Overflow thread](https://stackoverflow.com/questions/48235579/why-do-we-need-to-compile-for-different-platforms-e-g-windows-linux) and [this another Stack Overflow thread](https://stackoverflow.com/questions/33238345/are-c-applications-cross-platform)). That is why I have not published any single executable file or script. Instead, alongside the source files I have published a makefile that allows the user compile this utility for the platform that they want to use it on (in theory). For details on why a makefile may or may not be necessary in some cases, see for example [this StackExchange thread](https://softwareengineering.stackexchange.com/questions/273581/is-a-makefile-really-needed).

---

## How does this utility work (in general)?

Firstly, this utility gets the content of the file specified as its input. Then, it creates a new file and starts to scan the content line by line. When it come across _a line_ or _a block of lines with comments_, it formats them in a specified way; otherwise, it writes the line as is to the created file. The formatting is the following: the length of each line of a block should be less or equal to the value of the `intendedLength` parameter. The length of a line is computed as the number of characters. Currently, the length of the `intendedLength` parameter cannot be changed and equals `30`.

## Example

If the content of the input file looks like this:
```
#include <stdio.h>

int i = 0;
int j = 0;

// comment comment comment comment
// comment
// comment comment comment comment

for (; i < 10; ++i) {
    printf("lalala");
}

// another comment another comment another comment
// another comment
// another comment another comment another
```

then the content of the output file will look like this:
```
#include <stdio.h>

int i = 0;
int j = 0;

// comment comment comment commen
// t comment
// comment comment comment commen
// t

for (; i < 10; ++i) {
    printf("lalala");
}

// another comment another commen
// t another comment another comm
// ent another comment another co
// mment another
```

## Environment, tools and technologies used

1. Programming languages:
    - [C language](https://en.wikipedia.org/wiki/C_(programming_language)) (the whole utility except the `makefile` file) – C99 standard;
    - [makefile language](https://en.wikipedia.org/wiki/Make_(software)#Makefile) (only the `makefile` file).
2. There was used two environments to compile this utility:
    1. First one:
        - The compiler used to compile it is the [GNU GCC](https://gcc.gnu.org/), version 8.2.1 20181105 (Red Hat 8.2.1-5) (GCC).
        - The operating system used to compile it is Linux; distribution: [Fedora](https://getfedora.org/) Workstation 29; [kernel](https://www.kernel.org/) version: 4.19.6-300.fc29.x86_64.
        - The architecture of the processor used to run the operating system is x86-64.
    2. Second one: default Travis CI environment for the C language; for details, see the following sections in the Travis CI documentation: [CI environment for C Projects](https://docs.travis-ci.com/user/languages/c/#ci-environment-for-c-projects) and [Infrastructure and environment notes](https://docs.travis-ci.com/user/for-beginners/#infrastructure-and-environment-notes).
3. The operating system used to test it is the same as the first one for compilation.
4. The architecture of the processor used to run the operating system for testing is x86-64.

### A note about Travis CI's configuration

I use [Travis CI](https://travis-ci.org/) publishing this project on GitHub. In order that this project build configuration conforms to the default build configuration that Travis uses for projects written in the C language, I had to set the `script` parameter in the `.travis.yml` configuration file to `make`.

Also, in order that this project conforms to the default configuration of the gcc compiler version that Travis uses, I had to change the `gcc` command in the makefile to use the C99 C standard.

For details on the default Travis's configuration for projects written in the C language, see the article "[Building a C Project](https://docs.travis-ci.com/user/languages/c/)" in Travis's documentation.

## Details

For detailed information about this project, see [this project wiki](https://github.com/silvuss/silvuss-forcom/wiki). Particularly, the wiki includes:
- [the details of text processing that this utility performs](https://github.com/silvuss/silvuss-forcom/wiki/Process-details);
- [what comment types are currently supported](https://github.com/silvuss/silvuss-forcom/wiki/Supported-comment-types);
- [major problems that this utility (currently) cannot handle](https://github.com/silvuss/silvuss-forcom/wiki/Current-major-problems).