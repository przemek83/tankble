## Table of content
- [Example screenshot](#example-screenshot)
- [Description](#description)
- [History](#history)
- [Used tools and libs](#used-tools-and-libs)
- [Compilation and installation](#compilation-and-installation)
- [Licensing](#licensing)
- [Testing](#testing)
- [Potential further improvements](#potential-further-improvements)
- [Screenshots](#screenshots)

## Example screenshot

 ![Alt text](game_firing.png?raw=true "")

## Description
Clone of old arcade game named Battle City / Tank 1990 based on very old group project from studies.

TODO

## History
TODO

## Used tools and libs
| Tool |  Windows | Lubuntu |
| --- | --- | --- |
| OS version | 10 22H2 | 22.04 |
| GCC | 8.1.0 | 9.5.0 |
| Cmake | 3.25.0 | 3.25.0 |
| Git | 2.38.1 | 2.34.1 |
| QtCreator | 9.0.0 | 9.0.0 |
| Allegro | 5.2.6.0 | 5.2.6.0 |
| Catch2 | 3.3.0 | 3.3.0 |
| VSCode | 1.73.1 | -|

## Compilation and installation
Use directly Cmake or any IDE supporting Cmake project. Cmake **should**:
- configure everything automatically, 
- download dependencies using Git (Allegro, Catch2), 
- build dependencies, 
- compile Tankble and link binaries.  

This is of course happy path...

**TIPS**: on Linux you might need to install `libxcursor-dev` to be able to use Allegro library.  

## Licensing
Tankble is published under MIT license. 

Project uses following software and licenses:
* Allegro - The giftware license (more on https://liballeg.org and https://github.com/liballeg/allegro5),    
* Catch2 - Boost Software License 1.0 (more on https://github.com/catchorg/Catch2).

## Testing
1) Compile project.
2) Run target named `tankble-test`.
3) Check output. All tests should have status `passed`.    

Tests are done using Catch2 test framework.

## Potential further improvements
TODO

## Screenshots
![Alt text](menu_main.png?raw=true "")

![Alt text](game_cruising.png?raw=true "")

![Alt text](game_level_3.png?raw=true "")

![Alt text](game_level_4.png?raw=true "")

![Alt text](menu_screen.png?raw=true "")

![Alt text](menu_levels.png?raw=true "")