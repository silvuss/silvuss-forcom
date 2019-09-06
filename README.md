[![Build Status](https://travis-ci.org/silvuss/silvuss-forcom.svg?branch=master)](https://travis-ci.org/silvuss/silvuss-forcom)

# forcom – format comments

**forcom** (FORmat COMments) is a utility that allows the user to format [comments](https://en.wikipedia.org/wiki/Comment_(computer_programming)) that a given file contains. The file's content may be any content that contains comments (e.g. source code).

**Read before use:** This application **is not** intended to be used according to the purpose described above. You may use it **only** to test whether the code is written the way it is expected to be (i.e. it produces expected results) and **only** when you know what the code will really do. For details, see the section "[Disclaimers](#disclaimers)" below.

## Table of contents

1. [Copyright note](#copyright-note)
2. [Disclaimers](#disclaimers)
3. [How does this application work?](#how-does-this-application-work)
4. [Building](#building)
5. [Installation](#installation)
6. [Usage](#usage)
7. [Environments, tools and technologies used](#environments-tools-and-technologies-used)
8. [Details](#details)

## Copyright note

Note that this project "forcom" (this repository) has currently **no license**, as explained in [this GitHub guide on licensing projects](https://choosealicense.com/no-permission/).

For your convenience, I am including below a quote from that site:

> When you make a creative work (which includes code), the work is under exclusive copyright by default. Unless you include a license that specifies otherwise, nobody else can use, copy, distribute, or modify your work without being at risk of take-downs, shake-downs, or litigation. Once the work has other contributors (each a copyright holder), “nobody” starts including you.

Also note that I can add a license in the future if it would be relevant to the needs of this project.

## Disclaimers

**The application that this project contains is an example application that is not intended to be run.** Its purpose is only to show code that is known to work. While probably nothing dangerous would happen, you may run it only under your own responsibility.

Although I have made efforts to make it work as intended and described, it is not a "professional" application. Specifically, it was not tested in terms of separate unit tests or similar. It was tested to build and work only on one platform. Specifically, it deals with memory, and that never may be safe at all. For details on the platform, see the section ["Environment, tools and technologies used"](#environment-tools-and-technologies-used) below.

## How does this application work?

Firstly, this application gets the content of the file specified on the input. Then, it creates a new file and starts to scan the content line by line. When it come across _a line_ or _a block of lines with comments_, it formats them in a specified way; otherwise, it writes the line as is to the created file.

The formatting is the following: the length of each line of a block should be less or equal to the value of the `intendedLength` parameter. The length of a line is computed as the number of characters. Currently, the length of the `intendedLength` parameter cannot be changed and equals `30`.

## Building

Before using, this application has to be compiled.

There are two prerequisites to be able to compile this application:
1. In order to interpret the `makefile` file, the operating system (Linux or other) must provide an implementation of the application [make](https://en.wikipedia.org/wiki/Make_(software)).
2. The shell that you will use has to provide three commands: the [rm command](https://en.wikipedia.org/wiki/Rm_(Unix)), the [rmdir command](https://en.wikipedia.org/wiki/Rmdir) and the [mkdir command](https://en.wikipedia.org/wiki/Mkdir).

There are several ways and many tools to compile a C program having its source files. \* In the case of this application, the simplest way is to use the `make` command (provided by the aforementioned application make). All the supported commands (all using make) are listed in the following table:

|No.|Command|Description|Output|
|-|-|-|-|
|1|`make`|Default. Causes the application to be compiled using a compiler available by the `gcc` command. Creates the `bin` subdirectory if it does not exist.|One executable file `bin/forcom`|
|2|`make default`|(same as `make`)|(same as `make`)|
|3|`make debug`|Causes the application to be compiled using a compiler available by the `gcc` command with some debug parameters. For the list of parameters, see the `makefile` file. Creates the `bin_debug` directory if it does not exist.|One executable file `bin_debug/forcom_debug` and one object file (extension `.o`) for each of the source files (extension `.c`) in the `src` subdirectory|
|4|`make clean`|Removes all the files and directories that were created either by executing `make` or `make debug`. If some of the directories or files are not intended to be removed, do not use this command – instead, if needed, remove the appropriate files yourself.|---|

To compile, open the terminal, go into the main directory of the application and execute one of those commands.

If any errors will occur during compilation, it probably means that the platform that it is running on does not meet the prerequisites for compilation. If any errors will occur during running, it probably means that the platform that it is running on does not support some functions of this application, or some functions are supported in a way that this application cannot handle. For details on which platform this application was tested (i.e. runs successfully), see the section ["Tools and technologies used"](#tools-and-technologies-used) of this readme.

---

\* On the internet, it is generally mentioned that you should compile a C program **separately for each [platform](https://en.wikipedia.org/wiki/Computing_platform)** that you want to run the program on (for reasons, see for example [this Stack Overflow thread](https://stackoverflow.com/questions/48235579/why-do-we-need-to-compile-for-different-platforms-e-g-windows-linux) and [this another Stack Overflow thread](https://stackoverflow.com/questions/33238345/are-c-applications-cross-platform)). That is why I have not published any single executable file or script. Instead, alongside the source files I have published a makefile that allows the user compile this application for the platform that they want to use it on (in theory). For details on why a makefile may or may not be necessary in some cases, see for example [this StackExchange thread](https://softwareengineering.stackexchange.com/questions/273581/is-a-makefile-really-needed).

## Installation

This application neither can be installed (onto any platform), nor require it.

## Usage

**_Note:_** _Before using, this application has to be compiled. For details, see the section "[Building](#building)" above._

The only interface to use this application is a CLI provided within this project.

One can run this application by executing the following command from within its main directory:

```
bin/forcom FILE_1 FILE_2
```

where:
- `FILE_1` is the path to a file containing comments to format.
- `FILE_2` is the path to a file that will be created as the output of the application.

### Input

The input data of the application has to meet the following requirements (in this order):
1. it has to be the path to a file (i.e. it may not be empty); this file is assumed to contain a text to get the speeches from;
2. the file has to be readable by the user that runs the Java runtime environment;
3. the file has to be printable;
4. the file's content has to be encoded using the [UTF-8 encoding](https://en.Wikipedia.org/wiki/UTF-8).

### Output

#### Example

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

**Tip:** If any errors occur during running, it probably means that the platform that this application is running on does not support some functions of this application, or some functions are supported in a way that this application cannot handle. For details on which platform this application was tested (i.e. builds and/or runs successfully), see the section "[Environment, tools and technologies used](#environment-tools-and-technologies-used)" below.

## Environments, tools and technologies used

### Environments and tools

- This application has been compiled using the following two environments:
    1. First one:
        - **Compiler:** GNU GCC, version: `8.2.1 20181105 (Red Hat 8.2.1-5) (GCC)`
        - **Operating system:** Linux, distribution: Fedora Workstation 29, kernel's version: `4.19.6-300.fc29.x86_64`
        - **Processor's architecture:** `x86-64`
    2. Second one: default Travis CI environment for the C language; for details, see the following sections in the Travis CI's documentation: [CI environment for C Projects](https://docs.travis-ci.com/user/languages/c/#ci-environment-for-c-projects) and [Infrastructure and environment notes](https://docs.travis-ci.com/user/for-beginners/#infrastructure-and-environment-notes). For additional information on the used configuration for Travis CI, see this project's documentation page with notes for Travis CI (inside the directory `/docs` of this project).
- This application has been tested to work in the same environment as the first one for compilation.

### Technologies and tools

- Programming languages:
    - The [C language](https://en.wikipedia.org/wiki/C_(programming_language)) (the whole application except the `makefile` file), standard: C99
    - The [makefile language](https://en.wikipedia.org/wiki/Make_(software)#Makefile) (only the `makefile` file)

## Details

For other information about this website, see the documentation in the directory `/docs` of this project.