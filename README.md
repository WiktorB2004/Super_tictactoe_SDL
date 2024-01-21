## Super tic tac toe
- The project involves creating tic tac toe game using SDL in regular(3x3) / ultimate(9x9) mode with possiblity to host games over LAN. <br>
- Source code documentation (Doxygen) - [Super Tic Tac Toe Docs](https://wiktorb2004.github.io/Super_tictactoe_SDL/)

## How to play

- Use docker image
```
$ docker pull ghcr.io/wiktorb2004/super_tictactoe_sdl:master
$ docker run -it ghcr.io/wiktorb2004/super_tictactoe_sdl:master
``` 
- Download repository and build the source code
```
$ git clone https://github.com/WiktorB2004/Super_tictactoe_SDL.git
$ cd Super_tictactoe_SDL
$ mkdir build
$ cd build
$ cmake .. -DRELEASE_BUILD=1
$ cmake --build .
$ cd ..
$ ./bin/supertictactoe
```

#### Generating documentation - you need to have Doxygen installed

```
$ git clone https://github.com/WiktorB2004/Super_tictactoe_SDL.git
$ cd WLang_interpreter-C/
$ doxygen Doxyfile
```
The documentation will be available inside /docs folder

- - - -
Thank you for exploring this project, and I hope it demonstrates our dedication to the craft of software development and commitment to delivering high-quality solutions. If you have any questions or would like to collaborate with us, please feel free to get in touch.
