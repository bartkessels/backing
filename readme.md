# Backing

Application to mock your back-end for front-end testing

## Table of contents

- [1. Screemshots](#1-screenshots)
- [2. Features](#2-features)
- [3. Roadmap](#3-roadmap)
- [4. Required packages](#4-required-packages)
- [5. Build](#5-build)
    - [5.1 Tests](#51-tests)
        - [5.1.1 Test coverage](#511-test-coverage)
    - [5.2 Application](#52-application)

## 1. Screenshots

![Mainwindow for Backing](data/screenshot_1.png)

## 2. Features

Simply setup a base uri with a specific port and add multiple listeners.
Each listener can be configured to use a specific resource, return
any status code. And of course return a body with your own Content-Type
header.

All requests will be logged to the output at the bottom of the screen
so you can easily detect if your front-end is sending data to the expected
back-end.

## 3. Roadmap

Right now Backing is an early stage of development so some bugs are
expected, most notably error handling when the request listeners are
started and/or stopped.

The first things we'll add is error handling for the following cases:

- Trying to start the listener with an empty uri
- Trying to start multiple listeners on the same resource
    - (We'll try to allow it for multiple methods on the same resource)

Some other things we'd like to see different is the GUI, right now
it's just functional but not very pleasing to the eyes, so if you have
any ideas on how to make it look better please open a pull request or
an issue.

There are some things we want get up and running to make life easier for the developers of Backing, mostly for distributing the application.

- Setup an automated CD pipeline
- Setup CI for Windows machine
- Setup GUI test framework

## 4. Required packages

Backing relies on a couple of external packages, some are being fetched using Cmake's `FetchContent` while others
are expected to be installed on your system.

The packages that are fetched by Cmake are [CppRestRequest](https://github.com/microsoft/cpprestsdk), a library from
[Microsoft](https://microsoft.com) to send HTTP requests using an easy C++ interface. This package is both used for
building the `backing` executable as well as the `backing_tests` executable. For the `backing_tests` executable the
[Catch2](https://github.com/catchorg/catch2) library is fetched as the unit-tests framework used by Backing.

The packages you need to install

- `Qt5`, this is used for the GUI of Backing
- `Boost`, these libraries are used within [CppRestSdk](https://github.com/microsoft/cpprestsdk) library
- `CMake`, this is the build system used by Backing

## 5. Build

Once you've installed the required packages you're ready to compile Backing or the Backing tests.

### 5.1 Tests

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make backing_tests
$ ./bin/backing_tests
```

#### 5.1.1 Test coverage

When building the tests the required compiler flags are set to generate the coverage reports for each individual
source file. The coverage reports can be bundled using `lcov` which will generate a `*.info` file which can be transformed
into a `html` file using the `genhtml` command.

```bash
$ lcov --directory tests/CMakeFiles/backing_tests.dir --capture --output-file backing_coverage.info
$ genhtml -o coverage/ backing_coverage.info
$ open coverage/index.html
```

### 5.2 Application

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make backing
$ ./bin/backing
```