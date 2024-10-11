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
1) Compile project.
2) Run target named `tankble-test`.
3) Check output. All tests should have status `passed`.    

Tests are done using Catch2 test framework.

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
