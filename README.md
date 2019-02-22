[![Build Status](https://travis-ci.org/silvuss/silvuss-forcom.svg?branch=master)](https://travis-ci.org/silvuss/silvuss-forcom)

# forcom – Format comments

forcom (FORmat COMments) is a utility that allows the user format [comments](https://en.wikipedia.org/wiki/Comment_(computer_programm`in`g)) that a given file contains. The file's content may be any content that contains comments, e.g. source code.

**Read before use:** This application **is not** intended to be used according to the purpose described above. You may use it **only** to test whether the code is written the way it is expected (i.e. it produces expected results) and **only** when you know what the code will really do. For details, see the section ["Disclaimers"](#disclaimers) of this readme.

## Table of contents

1. [Copyright note](#copyright-note)
2. [Disclaimers](#disclaimers)
3. [How does this utility work?](#how-does-this-utility-work)
4. [How to run this utility?](#how-to-run-this-utility)
5. [Process details](#process-details)
6. [Supported comment types](#supported-comment-types)
7. [Example](#example)
8. [Current major problems](#current-major-problems)
9. [Environment, tools and technologies used](#environment-tools-and-technologies-used)

## Copyright note

Note that this "forcom" project (this repository) has currently **no license**, as explained in [this GitHub guide on licensing projects](https://choosealicense.com/no-permission/).

For your convenience, I am including below a quote from that site:
> When you make a creative work (which includes code), the work is under exclusive copyright by default. Unless you include a license that specifies otherwise, nobody else can use, copy, distribute, or modify your work without being at risk of take-downs, shake-downs, or litigation. Once the work has other contributors (each a copyright holder), “nobody” starts including you.

Also note that I can add a lincese in the future if it would be relevant to the needs of this project.

## Disclaimers

**This application is an example application that is not intended to be run.** Its purpose is only to show code that is known to work. While probably nothing dangerous would happen, you may run it only under your own responsibility.

Although I have made efforts to make it work as intended and described, it is not a "proffessional" application. Specifically, it was not tested in terms of separate unit tests or similar. It was tested to work only on one platform. Specifically, it deals with memory, and that never may be safe at all. For details on the platform, see the section ["Environment, tools and technologies used"](#environment-tools-and-technologies-used) of this README.

## How does this utility work?

Firstly, this utility gets the content of the specified input file. Then, it writes every line to the newly created output file – and when it come across a _block of lines with comments_, it formats the block in a way that the  length of each line of this block is less or equal to the value of the `intendedLength` parameter. The length of a line is computed as the number of characters. Currently, the length of the `intendedLength` parameter cannot be changed and equals `30`.

## How to run this utility?

This utility is intended to be run in the console, on a Linux system. Before running, it has to be compiled.

### Compiling

There are two formal prerequisites to be able to successfully compile it:
1. In order to interpret the `makefile` file, your operating system (Linux or other) has to provide an implementation of the [make utility](https://en.wikipedia.org/wiki/Make_(software)).
2. The shell that you will use has to provide three commands: the [rm command](https://en.wikipedia.org/wiki/Rm_(Unix)), the [rmdir command](https://en.wikipedia.org/wiki/Rmdir) and the [mkdir command](https://en.wikipedia.org/wiki/Mkdir).

There are several ways and many tools to run a C program having its source files.<sup>1</sup> In the case of this utility, the simplest way will using the `make` command (provided by the aforementioned make utility). All the supported commands are listed in the following table:

|No.|Command|Description|Output files|
|-|-|-|-|
|1|`make`|Default. Causes the utility to be compiled using a compiler available by the `gcc` command. Creates the `bin` subdirectory if it does not exist.|One executable file `bin/forcom`|
|2|`make default`|(same as `make`)|(same as `make`)|
|3|`make debug`|Causes the utility to be compiled using a compiler available by the `gcc` command with some debug parameters. For the list of parameters, see the `makefile` file. Creates the `bin_debug` directory if it does not exist.|One executable file `bin_debug/forcom_debug` and one object file (extension `.o`) for each of the source files (extension `.c`) in the `src` subdirectory|
|4|`make clean`|Removes all the files and directories that were created either by executing `make` or `make debug`. If some of the directories or files are not intended to be removed, do not use this command; instead, if needed, remove the appropriate files yourself.|---|

To compile, open the terminal, go into the utility main directory and execute one of the commands listed in the table above.

### Running

In the case of this utility, the simplest way will be opening the terminal, going into the utility main directory and executing the following command (`$` is the user prompt):
```
$ ./bin/forcom FILE_1 FILE_2
```
where:
- `FILE_1` is the input file path; it should be the path to a readable file containing comments to format.
- `FILE_2` is the output file path; it should be the path to an output file that will be created.

**Tip:** If only names of the files will be specified, it will be assumed that the path for each of them is the path to the current directory.

If any errors will occur during compilation, it probably means that the platform that it is running on does not meet the prerequisites for compilation. If any errors will occur during running, it probably means that the platform that it is running on does not support some functions of this utility, or some functions are supported in a way that this utility cannot handle. For details on which platform this utility was tested (i.e. runs successfully), see the section ["Tools and technologies used"](#tools-and-technologies-used) of this readme.

---

<sup>1</sup> On the internet, it is generally mentioned that you should compile a C program **separately for each [platform](https://en.wikipedia.org/wiki/Computing_platform)** that you want to run the program on (for reasons, see for example [this Stack Overflow thread](https://stackoverflow.com/questions/48235579/why-do-we-need-to-compile-for-different-platforms-e-g-windows-linux) and [this another Stack Overflow thread](https://stackoverflow.com/questions/33238345/are-c-applications-cross-platform)). That is why I have not published any single executable file or script. Instead, alongside the source files I have published a makefile that allows the user compile this utility for the platform that they want to use it on (in theory). For details on why a makefile may or may not be necessary in some cases, see for example [this StackExchange thread](https://softwareengineering.stackexchange.com/questions/273581/is-a-makefile-really-needed).

## Process details

This utility works in the following way:

1. After it is run, it gets its arguments. If there is less or more than two arguments, it writes a message to [stdout](https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)) and exits.

2. If there are exactly two arguments, it checks whether the first is the path to a readable file. If it is, then it opens the file to read. If it is not (either the file does not exist or is not readable), it writes a message to stdout and exits.

3. It checks whether the second argument is the path to a writable file. If it is, then it appends the number `1` as many times, as there is no file with the result name. If it is not, then it creates one in the current directory and opens it to write. For example, if the name provided as argument is `example-output`, the result name will be `example-output1`; if the name provided is `example-output1`, the result name will be `example-output11`; and so on.

4. For each line in the input file, it checks whether the line contains only comment or anything other than that.

5. If it contains only comment, then it checks whether the value of the `intendedLength` parameter is less than the current line length or not. If it is, then the utility writes the part of the line that has the length equal to the `intendedLength` parameter to the output file, and copies the rest of the line to the beginning of the next line. If it is not, then the utility writes the whole line to the output file.

6. If it contains anything other than comment, then the utility writes the line to the output file; then, it splits the rest that is left after splitting the last line until the length of the rest is greater than the value of the `intendedLength` parameter; after each splitting, it writes the first part of the splitting to the output file. Finally, it writes all the rest that is left to the next line.

## Supported comment types

All the supported comment types are listed in the following table:

|No.|Comment type|How is a comment marked|Example|Remarks|
|-|-|-|-|-|
|1|[Inline comment](https://en.wikipedia.org/wiki/Comparison_of_programming_languages_(syntax)#Inline_comments)|Two consecutive `/` (`U+002F`) characters at the beginning of a comment|`// this is an inline comment`|Supported by many programming languages – for example C, Java, PHP, JavaScript|

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

## Current major problems

Currently, according to the value of the `intendedLength` parameter, some words in the comments may be unintentionally divided into two parts, the first part being left in one line, and the second part being moved to the next line.

## Environment, tools and technologies used

1. This utility is written for the greater part in the [C programming language](https://en.wikipedia.org/wiki/C_(programming_language)), and for the smaller part in the [makefile language](https://en.wikipedia.org/wiki/Make_(software)#Makefile).
2. The compiler used to compile it is the [GNU GCC](https://gcc.gnu.org/), version 8.2.1 20181105 (Red Hat 8.2.1-5) (GCC).
3. The operating system used to compile and test it is Linux; distribution: [Fedora](https://getfedora.org/) Workstation 29; [kernel](https://www.kernel.org/) version: 4.19.6-300.fc29.x86_64.
4. The architecture of the processor used to run the operating system is x86-64.