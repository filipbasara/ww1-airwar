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

    // game scenes are "the various screens", like "splash screen", game, high scores, etc.
    int scene=1;

    // scene one: story and spash screen
    char *story[13];

    story[0]="1975 - San Francisco, California";
    story[1]="Nolan Bushnell, Steve Wozniak and Steve Bristow";
    story[2]="designed a new one player game inspired by PONG...";
    story[3]="Steve Jobs was hired to design the prototype";
    story[4]="along with his friend Steve Wozniak.";
    story[5]="They designed the 44 chips that made the game possible";
    story[6]="and handcoded the machine language to run it!";
    story[7]="IN 4 DAYS!!! This is the stuff that creates legends!";
    story[8]="Now, you have all the hardware you could ever need...";
    story[9]="You have modern compilers, game engines and libraries...";
    story[10]="Can you do the same in your modern, state of the art computer?";
    story[11]="We can all try... but we will never be their equals!";
    story[12]="This is a tribute to those pioneers...";

    int story_time=0;
    int story_text=0;


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
        ClearBackground(BLACK);

        if(scene==1) // the background story
        {
            story_time++;

            if(story_time==360 && story_text < 13)   {   story_text++;  story_time=0; }

            if(story_text < 13)
            {
                DrawText(story[story_text], screen.width/2 - MeasureText(story[story_text], screen.font_size) / 2,
                                screen.height/2 - screen.font_size / 2, 
                                screen.font_size, WHITE);
            }
            else
            {
                story_text=0; // start over when the story finishes...
                story_time=0;                
            }
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }





    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

