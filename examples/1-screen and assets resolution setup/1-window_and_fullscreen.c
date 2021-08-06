/*
*     Welcome to the first example using raylib in Pointers "gentle intruduction to the C language" 
*/
#include "raylib.h"
#include <stdio.h>

// debug /dev modes
int FULLSCREEN=0;  // 0 - Small Window display, 1 - full screen, max resolution of display

// structs allow us to group variables under a label
// here is the definition of Dimensions struct we will be using for 2d stuff that has... well, a size...
struct Dimensions
{
    float width;
    float height;
    float font_size;
};


// globals
struct Dimensions screen;



int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    // our window size
    // - half of 720p (640x360) as minimun
    // - 720p (1280x720)
    // - 1080p (1920×1080)
    // - 4k UHD (3840x2160)
    screen.width=640; 
    screen.height=360;
    screen.font_size=20;

    InitWindow(screen.width, screen.height, "Pointers example: \"window_and_fullscreen.c\"");
 
    if(FULLSCREEN==1) 
    {
        screen.width=GetMonitorWidth(0);
        screen.height=GetMonitorHeight(0);
        screen.font_size=40;

        printf("%f, %f\n", screen.width, screen.height);

        //re initialize window and opengl context
        CloseWindow(); //close the default window
        InitWindow(screen.width, screen.height, "");
        ToggleFullscreen();
    }

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
                                screen.font_size, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }





    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}