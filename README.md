[![Build & test](https://github.com/przemek83/tankble/actions/workflows/buld-and-test.yml/badge.svg)](https://github.com/przemek83/tankble/actions/workflows/buld-and-test.yml)
[![CodeQL](https://github.com/przemek83/tankble/actions/workflows/codeql.yml/badge.svg)](https://github.com/przemek83/tankble/actions/workflows/codeql.yml)
[![codecov](https://codecov.io/gh/przemek83/tankble/graph/badge.svg?token=86RCNSFA0U)](https://codecov.io/gh/przemek83/tankble)

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=przemek83_tankble&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=przemek83_tankble)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=przemek83_tankble&metric=bugs)](https://sonarcloud.io/summary/new_code?id=przemek83_tankble)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=przemek83_tankble&metric=code_smells)](https://sonarcloud.io/summary/new_code?id=przemek83_tankble)
[![Coverage](https://sonarcloud.io/api/project_badges/measure?project=przemek83_tankble&metric=coverage)](https://sonarcloud.io/summary/new_code?id=przemek83_tankble)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=przemek83_tankble&metric=duplicated_lines_density)](https://sonarcloud.io/summary/new_code?id=przemek83_tankble)

## Table of content
- [Example screenshot](#example-screenshot)
- [Description](#description)
- [Used tools and libs](#used-tools-and-libs)
- [Compilation and installation](#compilation-and-installation)
- [Licensing](#licensing)
- [Testing](#testing)
- [Potential further improvements](#potential-further-improvements)
- [Screenshots](#screenshots)

## Example screenshot

 ![Alt text](game_firing.png?raw=true "")

## Description
Clone of old arcade game named Battle City / Tank 1990 based on very old group project from studies. 15 years after the original version, I've decided to heavily revamp, modernize, apply new ideas and publish it as open source. The effects can be observed in this repository.

**Remark**: For creation of bitmaps I've used all my graphics designing skills which are somewhat close to none ;)

## Used tools and libs

| Tool |  Windows | Ubuntu |
| --- | --- | --- |
| OS version | 10 22H2 | 24.04 |
| GCC | 13.1.0 | 13.2.0 |
| CMake | 3.30.2 | 3.28.3 |
| Git | 2.46.0 | 2.43.0 |
| Allegro | 5.2.9.1 | 5.2.9.1 |
| Catch2 | 3.7.0 | 3.7.0 |
| Visual Studio Code | 1.92.0 | 1.92.0 |

## Compilation and installation
Use directly CMake or any IDE supporting CMake project. CMake **should**:
- configure everything automatically, 
- download dependencies using Git (Allegro, Catch2), 
- build dependencies, 
- compile Tankble and link binaries.  

This is of course a happy path...

**TIPS**: on Linux, you might need to install `libgl1-mesa-dev` and `libxcursor-dev` to be able to use Allegro library.  

## Licensing
Software is released under the MIT license.

The project uses the following open-source software:
| Name | License | Home | Description |
| --- | --- | --- | --- |
| Allegro | Allegro - The giftware license | https://github.com/liballeg/allegro5 | cross-platform library for game and multimedia programming |
| Catch2 | BSL-1.0 | https://github.com/catchorg/Catch2 | testing framework for C++ |

## Testing
For testing of code logic, there is a responsible `Catch2` framework. As it is well integrated with `CMake` it should be straightforward to use. As the first step, build the project. Make sure that the `tankble-tests` target is built. Modern IDEs supporting CMake also support running tests with monitoring of failures. But in case you would like to run it manually, go to the `build\tests` directory, where the⁣ binary `tankble-tests` should be available after building. Calling it directly should produce the following output on Linux:

    $ ./tankble-tests
    Randomness seeded to: 3114824452
    ===============================================================================
    All tests passed (350 assertions in 29 test cases)

As an alternative, CTest can be used to run tests:

    $ ctest
    Test project <path>/tankble/build/tests
        Start  1: Bullet getters
    1/29 Test  #1: Bullet getters ..............................   Passed    0.00 sec
        Start  2: Bullet coordinates
    2/29 Test  #2: Bullet coordinates ..........................   Passed    0.00 sec
        Start  3: Bullet moving
    3/29 Test  #3: Bullet moving ...............................   Passed    0.00 sec
        Start  4: Bullet moving to invalid area
    4/29 Test  #4: Bullet moving to invalid area ...............   Passed    0.00 sec
        Start  5: Map loading
    5/29 Test  #5: Map loading .................................   Passed    0.00 sec
        Start  6: Check driving and flying
    6/29 Test  #6: Check driving and flying ....................   Passed    0.00 sec
        Start  7: Check hitting
    7/29 Test  #7: Check hitting ...............................   Passed    0.00 sec
        Start  8: Power ups
    8/29 Test  #8: Power ups ...................................   Passed    0.00 sec
        Start  9: shift
    9/29 Test  #9: shift .......................................   Passed    0.00 sec
        Start 10: changed area
    10/29 Test #10: changed area ................................   Passed    0.00 sec
        Start 11: Tank creation
    11/29 Test #11: Tank creation ...............................   Passed    0.00 sec
        Start 12: Tank direction
    12/29 Test #12: Tank direction ..............................   Passed    0.00 sec
        Start 13: check control
    13/29 Test #13: check control ...............................   Passed    0.00 sec
        Start 14: location related
    14/29 Test #14: location related ............................   Passed    0.00 sec
        Start 15: statistics
    15/29 Test #15: statistics ..................................   Passed    0.00 sec
        Start 16: hitting
    16/29 Test #16: hitting .....................................   Passed    0.00 sec
        Start 17: respawn
    17/29 Test #17: respawn .....................................   Passed    0.00 sec
        Start 18: firing
    18/29 Test #18: firing ......................................   Passed    0.00 sec
        Start 19: power-ups
    19/29 Test #19: power-ups ...................................   Passed    0.00 sec
        Start 20: Move points
    20/29 Test #20: Move points .................................   Passed    0.00 sec
        Start 21: Set element sizes
    21/29 Test #21: Set element sizes ...........................   Passed    0.00 sec
        Start 22: Config::getFps returns correct FPS values
    22/29 Test #22: Config::getFps returns correct FPS values ...   Passed    0.00 sec
        Start 23: MenuItem initialization and properties
    23/29 Test #23: MenuItem initialization and properties ......   Passed    0.00 sec
        Start 24: Display initialization and properties
    24/29 Test #24: Display initialization and properties .......   Passed    0.00 sec
        Start 25: Menu usage
    25/29 Test #25: Menu usage ..................................   Passed    0.00 sec
        Start 26: Status usage
    26/29 Test #26: Status usage ................................   Passed    0.00 sec
        Start 27: Check winning conditions
    27/29 Test #27: Check winning conditions ....................   Passed    0.00 sec
        Start 28: Player actions
    28/29 Test #28: Player actions ..............................   Passed    0.00 sec
        Start 29: Drawing
    29/29 Test #29: Drawing .....................................   Passed    0.00 sec

    100% tests passed, 0 tests failed out of 29

    Total Test time (real) =   0.06 sec

## Potential further improvements
Ideas:
- Add sounds and some music in menu.
- Add points received during gameplay.
- Use more sophisticated font than basic built in one from Allegro library.
- Implement proper mechanism for dropping frames in cases of CPU spikes and performance lags.

## Screenshots
![Alt text](menu_main.png?raw=true "")

![Alt text](game_cruising.png?raw=true "")

![Alt text](game_level_3.png?raw=true "")

![Alt text](game_level_4.png?raw=true "")

![Alt text](menu_screen.png?raw=true "")

![Alt text](menu_levels.png?raw=true "")
