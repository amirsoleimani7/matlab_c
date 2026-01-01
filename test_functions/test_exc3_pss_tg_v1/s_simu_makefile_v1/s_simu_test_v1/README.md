* one liner compile :  

 - g++ src/*.cpp -Iinclude -Ithird_party -O2 -std=c++17 -o bin/simu
 - ./bin/simu

* compile using make
[linux] : 

    # requiments : GCC >=9 , make
    # how to build : 
        - make [this makes the binary in the './bin' directory]
        - you can run the program usnig './simu' [the outputs will be written in the 'bin/Rep/']
        - u can clean the files using make clean


[windows] :  

    # notes : DO NOT USE , cmd , powelshell or gitbash
    # requiments : MSYS2
        - download MSYS2 from 'https://www.msys2.org/' 
        - open MSYS2 UCRT64 terminal (from the start menu)
        - install the required tools using this command 'pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make'
        - go to project directory
        - to make the program run 'mingw32-make'
        - to run the program './bin/simu.exe'

[macOS] :
    # not implemented yet