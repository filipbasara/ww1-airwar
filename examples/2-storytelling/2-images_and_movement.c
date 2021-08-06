/*
*     Welcome to the first example using raylib in Pointers "gentle intruduction to the C language" 
*/
#include "raylib.h"
#include <stdio.h>

#define DEFAULT_FONT_SIZE 120


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
int FULLSCREEN=1;  // use "0" to start with Window display OR "1" to start full screen


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

    // scene one: story and splash screen
    char *story[13];

    story[0]="1975 - San Francisco, California";
    story[1]="Nolan Bushnell, Steve Wozniak and Steve Bristow";
    story[2]="designed a new one player game inspired by PONG...";
    story[3]="Steve Jobs was hired to design the prototype";
    story[4]="along with his friend Steve Wozniak";
    story[5]="They designed the 44 chips that made the game possible";
    story[6]="and handcoded the machine language to run it";
    story[7]="In just 4 days!";
    story[8]="Atari took a few months get it ready for prime time...";
    story[9]="1976 - the Breakout arcade game was released!";
    story[10]="Steve Jobs and Steve Wozniak moved on...";
    story[11]="and founded a company called Apple";
    story[12]="This remake is a tribute to those pioneers...";

    Texture2D texture[14];
    texture[0] = LoadTexture("../resources/SanFrancisco.png");
    texture[1] = LoadTexture("../resources/Nolan.png");
    texture[2] = LoadTexture("../resources/Woz.png");
    texture[3] = LoadTexture("../resources/Steve.png");
    texture[4] = LoadTexture("../resources/Jobs.png");
    texture[5] = LoadTexture("../resources/DreamTeam.png");
    texture[6] = LoadTexture("../resources/Breakout.png");
    texture[7] = LoadTexture("../resources/Arcade.png");
    texture[8] = LoadTexture("../resources/4days.png");
    texture[9] = LoadTexture("../resources/apple.png");
    texture[10] = LoadTexture("../resources/atari.png");
    texture[11] = LoadTexture("../resources/chips.png");
    texture[12] = LoadTexture("../resources/code.png");
    texture[13] = LoadTexture("../resources/MovedOn.png");

    InitAudioDevice();              // Initialize audio device
    Sound music = LoadSound("../resources/Music.mp3");


    Vector2 position;

    int story_time=0;
    int story_text=0;

    PlaySound(music);

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
        ClearBackground(WHITE);

        if(scene==1) // the background story
        {
            story_time++;

            if(story_time==560 && story_text < 13)   {   story_text++;  story_time=0; }

            if(story_text < 13)
            {
                // images
                if(story_text==0)
                {
                    position.x = 0.0f * screen.scale_x - story_time/5*screen.scale_x;
                    position.y = -780.0f * screen.scale_y - story_time/2.5*screen.scale_y;

                    DrawTextureEx(texture[story_text], position, 0.0f, screen.scale_x, WHITE);
                }

                if(story_text==1)
                {
                    position.x = 600.0f * screen.scale_x;
                    position.y = 600.0f * screen.scale_y - story_time/2.5*screen.scale_y;
                    DrawTextureEx(texture[story_text], position, 0.0f, screen.scale_x * 0.20, WHITE);

                    position.x = 1600.0f * screen.scale_x;
                    position.y =  600.0f * screen.scale_y - story_time/2.5*screen.scale_y;
                    DrawTextureEx(texture[story_text+1], position, 0.0f, screen.scale_x * 0.20, WHITE);

                    position.x = 2600.0f * screen.scale_x;
                    position.y =  600.0f * screen.scale_y - story_time/2.5*screen.scale_y;
                    DrawTextureEx(texture[story_text+2], position, 0.0f, screen.scale_x * 0.20, WHITE);
                }

                if(story_text==2)
                {
                    position.x = 480.0f * screen.scale_x - story_time/20*screen.scale_x;
                    position.y = -300.0f * screen.scale_y - story_time/2.5*screen.scale_y;

                    DrawTextureEx(texture[story_text+4], position, 0.0f, screen.scale_x * 0.70, WHITE);
                }

                if(story_text==3)
                {
                    position.x = 480.0f * screen.scale_x - story_time/5*screen.scale_x;
                    position.y = -380.0f * screen.scale_y - story_time/2.5*screen.scale_y;

                    DrawTextureEx(texture[story_text+1], position, 0.0f, screen.scale_x * 0.70, WHITE);
                }

                if(story_text==4)
                {
                    position.x = 480.0f * screen.scale_x - story_time/20*screen.scale_x;
                    position.y = -300.0f * screen.scale_y - story_time/2.5*screen.scale_y;

                    DrawTextureEx(texture[story_text+1], position, 0.0f, screen.scale_x * 0.70, WHITE);
                }

                if(story_text==5)
                {
                    position.x = 480.0f * screen.scale_x - story_time/20*screen.scale_x;
                    position.y = -300.0f * screen.scale_y - story_time/2.5*screen.scale_y;

                    DrawTextureEx(texture[story_text+6], position, 0.0f, screen.scale_x * 3, WHITE);
                }

                if(story_text==6)
                {
                    position.x = 480.0f * screen.scale_x - story_time/20*screen.scale_x;
                    position.y = 300.0f * screen.scale_y - story_time/2.5*screen.scale_y;

                    DrawTextureEx(texture[story_text+6], position, 0.0f, screen.scale_x * 6, WHITE);
                }

                if(story_text==7)
                {
                    position.x = 580.0f * screen.scale_x - story_time/20*screen.scale_x;
                    position.y = -300.0f * screen.scale_y - story_time/2.5*screen.scale_y;

                    DrawTextureEx(texture[story_text+1], position, 0.0f, screen.scale_x * 4, WHITE);
                }

                if(story_text==8)
                {
                    position.x = 1200.0f * screen.scale_x - story_time/20*screen.scale_x;
                    position.y = 100.0f * screen.scale_y - story_time/2.5*screen.scale_y;

                    DrawTextureEx(texture[story_text+2], position, 0.0f, screen.scale_x * 5, WHITE);
                }

                if(story_text==9)
                {
                    position.x = 480.0f * screen.scale_x - story_time/20*screen.scale_x;
                    position.y = -300.0f * screen.scale_y - story_time/2.5*screen.scale_y;

                    DrawTextureEx(texture[story_text-2], position, 0.0f, screen.scale_x * 0.70, WHITE);
                }

                if(story_text==10)
                {
                    position.x = 200.0f * screen.scale_x - story_time/20*screen.scale_x;
                    position.y = 100.0f * screen.scale_y - story_time/2.5*screen.scale_y;

                    DrawTextureEx(texture[story_text+3], position, 0.0f, screen.scale_x * 6, WHITE);
                }

                if(story_text==11)
                {
                    position.x = 480.0f * screen.scale_x - story_time/20*screen.scale_x;
                    position.y = 100.0f * screen.scale_y - story_time/2.5*screen.scale_y;

                    DrawTextureEx(texture[story_text-2], position, 0.0f, screen.scale_x * 5, WHITE);
                }

                // the text
                Color faded_color1=Fade(BLACK,(float)story_time/360.0);
                Color faded_color2=Fade(WHITE,(float)story_time/360.0);

                DrawText(story[story_text], 
                                screen.width/2 + 5 * screen.scale_x - MeasureText(story[story_text], screen.font_size) / 2,
                                screen.height/2 + 905 * screen.scale_y - screen.font_size / 2, 
                                screen.font_size, 
                                faded_color2);

                DrawText(story[story_text], 
                                screen.width/2 - MeasureText(story[story_text], screen.font_size) / 2,
                                screen.height/2 + 900 * screen.scale_y - screen.font_size / 2, 
                                screen.font_size, 
                                faded_color1);
            }
/*            else
            {
                story_text=0; // start over when the story finishes...
                story_time=0;                
            }
*/
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }





    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadSound(music);   // Unload music stream buffers from RAM
    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

