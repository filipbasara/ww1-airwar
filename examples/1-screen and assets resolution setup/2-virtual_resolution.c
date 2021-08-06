/*
*     Welcome to the first example using raylib in Pointers "gentle intruduction to the C language" 
*/
#include "raylib.h"
#include <stdio.h>

#define DEFAULT_FONT_SIZE 60


// structs allow us to group variables under a label
// here is the definition of Dimensions struct we will be using for 2d stuff that has... well, a size...
struct Dimensions
{
    // real screen coordinates
    float width;
    float height;

    // virtual screen (internal resolution of the game assets)
    float virtual_width;
    float virtual_height;

    // scale used for graphics
    float scale_x;
    float scale_y;

    //default font size (scaled)
    float font_size;
};

// debug /dev modes
int FULLSCREEN=0;  // use "0" to start with Window display OR "1" to start full screen


// globals
struct Dimensions screen;




// toggle fullscreen
void toggle_fullscreen(int fs)
{
    CloseWindow(); //close the default window

    //re initialize window and opengl context
    InitWindow(screen.width, screen.height, "");
    if(fs == 1) ToggleFullscreen();
}


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------



    // our window/fullscreen size can be forced or we accept whatever GetMonitorWidth / GetMonitorHeight gives us...
    // interesting resolutions to consider
    // - half of 720p (640x360)
    // - 720p (1280x720)
    // - 1080p (1920×1080)
    // - 1440p (2560x1440)
    // - 4k UHD (3840x2160)

    InitWindow(screen.width, screen.height, "Pointers example: \"window_and_fullscreen.c\"");
    printf("Resolution returned to raylib: %f, %f\n", screen.width, screen.height);

    if(FULLSCREEN==1)
    {
        screen.width=GetMonitorWidth(0);
        screen.height=GetMonitorHeight(0);
    }
    else
    {
        screen.width=1280;
        screen.height=720;
    }

    // virtual screen game dimensions (we use assets is a different resolutions and then scale them)
    screen.virtual_width=3840;
    screen.virtual_height=2160;

    // calculate the scale
    screen.scale_x = screen.width / screen.virtual_width;
    screen.scale_y = screen.height / screen.virtual_height ;

    // default font sized (once scaled)
    screen.font_size = DEFAULT_FONT_SIZE * screen.scale_x;

    toggle_fullscreen(FULLSCREEN);

    //--------------------------------------------------------------------------------------


    SetTargetFPS(60);               // Set our frames-per-second target
    //--------------------------------------------------------------------------------------




    char my_string[]="We have something to write in our new window";


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);


            DrawText(my_string, screen.width/2 - MeasureText(my_string, screen.font_size) / 2,
                                screen.height/2 - screen.font_size / 2, 
                                screen.font_size, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }





    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

