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
| Tool |  Windows | Lubuntu |
| --- | --- | --- |
| OS version | 10 22H2 | 22.04 |
| GCC | 8.1.0 | 9.5.0 |
| CMake | 3.25.0 | 3.25.0 |
| Git | 2.38.1 | 2.34.1 |
| Qt Creator | 9.0.0 | 9.0.0 |
| Allegro | 5.2.6.0 | 5.2.6.0 |
| Catch2 | 3.3.0 | 3.3.0 |
| VS Code | 1.73.1 | -|

## Compilation and installation
Use directly CMake or any IDE supporting CMake project. CMake **should**:
- configure everything automatically, 
- download dependencies using Git (Allegro, Catch2), 
- build dependencies, 
- compile Tankble and link binaries.  

This is of course a happy path...

**TIPS**: on Linux, you might need to install `libxcursor-dev` to be able to use Allegro library.  

## Licensing
Tankble is published under MIT license. 

The project uses the following software and licenses:
* Allegro - The giftware license (more on https://liballeg.org and https://github.com/liballeg/allegro5),    
* Catch2 - Boost Software License 1.0 (more on https://github.com/catchorg/Catch2).

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
- Divide Game class and add tests for its logic.
- Implement proper mechanism for dropping frames in cases of CPU spikes and performance lags.

## Screenshots
![Alt text](menu_main.png?raw=true "")

![Alt text](game_cruising.png?raw=true "")

![Alt text](game_level_3.png?raw=true "")

![Alt text](game_level_4.png?raw=true "")

![Alt text](menu_screen.png?raw=true "")

![Alt text](menu_levels.png?raw=true "")
