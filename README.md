# Simple-game
Its a quick game made with raylib

# How to complie it
download msys2 from this : [Download](https://www.msys2.org/)
wait for it to download and install it
then open UCRT
then run this command : `$ pacman -S mingw-w64-ucrt-x86_64-gcc`
press enter and wait for download
then run `$ pacman -S mingw-w64-ucrt-x86_64-raylib`
and download the project and use this command with UCRT in the project directory : `g++ Main.cpp -lraylib -lopengl32 -lm -lpthread`
