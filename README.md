# RP6502 Game Demo for LLVM-MOS

Get started by using the vscode-llvm-mos template from https://github.com/picocomputer/vscode-llvm-mos.  Find the "Use this template" button and follow the instructions to create a new repository.  

Once you have your respository set up, we are going to update CMakeLists.txt to build the demo game.  Update the contents of CMakeLists.txt to have the name of the game you want to make.  In this example, we are going to make a game called RPDemo.  The CMakeLists.txt file should look something like this:

```cmake
cmake_minimum_required(VERSION 3.18)

add_subdirectory(tools)

set(LLVM_MOS_PLATFORM rp6502)
find_package(llvm-mos-sdk REQUIRED)

project(RPDemo C CXX ASM)

add_executable(RPDemo)

rp6502_asset(RPDemo help src/help.txt)

rp6502_executable(RPDemo 
    DATA file 
    RESET file
)

target_sources(RPDemo PRIVATE
    src/main.c
)
```

At this point, you should be able to build the project in VScode with the build button and run it on your Picocomputer via F5 or the run button.  You can also run it from the command line with the following command:
```
python3 ./tools/rp6502.py run build/RPDemo.rp6502
```
[Note: If you are on a Mac, you can use rp6502_mac.py found in the tools directory of this repository.]

## Setting up Graphics

The documentation for the Picocomputer is excellent:
https://picocomputer.github.io

For this demo we are going to work with a 320x240 canvas.   Let's start by initializing the graphics system.  We can do this by calling the xreg_vga_canvas function with a parameter of 1.  Add the following to your main.c file, as well as ```#include <stdbool.h>``` at the top of the file:


```c
static bool init_graphics(void)
{
    // 320×240 canvas
    int rc;
    rc = xreg_vga_canvas(1);
    if (rc < 0) {
        puts("Error: xreg_vga_canvas(1) failed");
        return false;
    }
    return true;
}
```

and then we will call this function from our main, and also set up a vsync loop to keep the program running.  Update your main function to look like this:

```c

uint8_t vsync_last = 0;

int main(void)
{
    if (!init_graphics()) {
        puts("Fatal: graphics initialization failed");
        return 1;
    }

    // Main loop
    while (true) {
        // 1. SYNC
        if (RIA.vsync == vsync_last) continue;
        vsync_last = RIA.vsync;
    }

    return 0;
}
```

If you build and run this code, you should see a blank screen on your Picocomputer.  This means that we have successfully initialized the graphics system and are running a main loop that is synced to the vertical refresh of the display.  In the next section, we will start drawing some pixels to the screen!  To exit the program hit "CTRL + ALT + DEL" on the keyboard connected to your Picocomputer.

## Adding a Sprite



