# Notes for Travis CI

## Configuration

There is used [Travis CI](https://travis-ci.org/) during publishing changes to this project on GitHub. I wanted that the build configuration of this project conform to the default build configuration that Travis CI uses for projects written in the C language. Therefore, I had to set the `script` parameter in the `.travis.yml` configuration file to `make`. Also, in order that this project conforms to the default configuration of the gcc compiler version that Travis CI uses, I had to change the `gcc` command in the makefile to use the C99 C standard.

For details on the default Travis CI's configuration for projects written in the C language, see the article "[Building a C Project](https://docs.travis-ci.com/user/languages/c/)" in Travis CI's documentation.