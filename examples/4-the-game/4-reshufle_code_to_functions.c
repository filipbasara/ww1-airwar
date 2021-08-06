/*
*     Welcome to the first example using raylib in Pointers "gentle intruduction to the C language" 
*/
#include "raylib.h"
#include <stdio.h>
#include <string.h>












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


struct Player
{
    int lives;
    int level;
    int score;
    int record;
};



struct Actor
{
    // 0 - player / 1 - brick / 2 - ball / 3 - maze wall
    int role;

    // color
    Color rgba;

    // shape (0 - rectangle / 1 - circle)
    int shape;

    // position on screen is x & y of collision rectangle
    // dimensions of the thing in width & height
    Rectangle rect;

    // speed for moving objects
    Vector2 speed;
};










// our game globals

// debug /dev modes
int FULLSCREEN=0;  // use "0" to start with Window display OR "1" to start full screen

// game scenes are "the various screens", like "splash screen", game, high scores, etc.
// we start with the splash screen (2) by default... scene one is the intro, scene 3 the game
int scene=2;


Rectangle temprect;
Vector2 position;

int time_to_die=0;

struct Dimensions screen;
struct Player player;
struct Actor obj[200];

int story_time=0;
int story_text=0;

char *story[13];        // intro text
Texture2D texture[14];  // intro images
Sound music;            // intro music












// toggle fullscreen
void toggle_fullscreen(int fs)
{
    CloseWindow(); //close the default window

    //re initialize window and opengl context
    InitWindow(screen.width, screen.height, "");
    if(fs == 1) ToggleFullscreen();
}














void draw_game_info()
{
    char outtext[32];

    sprintf(outtext, "Lives: %d", player.lives);
    DrawText(outtext, 
                0,
                0, 
                screen.font_size, 
                LIGHTGRAY);

    sprintf(outtext, "Score: %d", player.score);
    DrawText(outtext, 
                0,
                200, 
                screen.font_size, 
                LIGHTGRAY);

    sprintf(outtext, "HS: %d", player.record);
    DrawText(outtext, 
                0,
                400, 
                screen.font_size, 
                LIGHTGRAY);

    sprintf(outtext, "Level %d", player.level);
    DrawText(outtext, 
                0,
                600, 
                screen.font_size, 
                LIGHTGRAY);
}














void draw_intro_frame()
{
    ClearBackground(WHITE);

    // left mouse click or pressing space skips to scene 2 (splash screen)
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyDown(KEY_SPACE) )
    {
        if( IsSoundPlaying(music) ) StopSound(music);
        scene=2;
    }

    // (keep) tell(ing) the story
    story_time++;

    // start the music at the start of the intro
    if(story_time==1 && story_text==0) PlaySound(music);

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
    else
    {
        scene=2; // intro ended, go to splash scene
    }
}













void ball_hits_brick(int brick)
{
    obj[brick].rect.y = -1000;  // Literally remove it from screen
                               // no bricks are harmed in the production of this game!
    player.score += 1;

    if(player.record < player.score)   player.record=player.score;           
}















void ball_collision(int which)
{
    for(int other=0; other<117; other++)
    {
        if(which != other) // ball does not collide with itself...
        {
            temprect=obj[which].rect;

            int test_please=0;
            Vector2 movement;
            movement.x=0;
            movement.y=0;

            // test the x axis
            if(obj[which].speed.x<0 && movement.x > obj[which].speed.x)
            {    
                movement.x -= 1;
                temprect.x -= 1;
                test_please=1;
            }

            if(obj[which].speed.x>0 && movement.x < obj[which].speed.x) 
            {
                movement.x += 1;  
                temprect.x += 1;
                test_please=1;
            }

            if(test_please != 0)  
            {                                  
                if(CheckCollisionRecs(temprect, obj[other].rect) )
                {
                    // hits a brick, lets remove it from our screen and add points to player score
                    if(obj[other].role==1) ball_hits_brick(other);

                    obj[which].speed.x *= -1;
                }
            }

            // test the Y axis
            if(obj[which].speed.y<0 && movement.y > obj[which].speed.y)
            {    
                movement.y -= 1;
                temprect.y -= 1;
                test_please=1;
            }

            if(obj[which].speed.y>0 && movement.x < obj[which].speed.y) 
            {
                movement.y += 1;
                temprect.y += 1;
                test_please=1;
            }

            if(test_please != 0)  
            {                                  
                if(CheckCollisionRecs(temprect, obj[other].rect) )
                {
                    // hits a brick, lets remove it from our screen and add points to player score
                    if(obj[other].role==1) ball_hits_brick(other);

                    obj[which].speed.y *= -1;
                }
            }
        }
    }                    
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

    // scene one: story and splash screen
 
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
    music = LoadSound("../resources/Music.mp3");






    // scene 2 (splash page assets)
    Texture2D splash_background = LoadTexture("../resources/splash.png");

    Texture2D button[3];
    button[0] = LoadTexture("../resources/play.png");
    button[1] = LoadTexture("../resources/intro.png");
    button[2] = LoadTexture("../resources/exit.png");




    // scene 3 (the game) 
    player.lives=3;
    player.level=1;
    player.score=0;
    player.record=0;

    // player bat
    obj[0].role=0;
    obj[0].rgba=LIGHTGRAY;
    obj[0].shape=0;
    obj[0].rect.width = 150 * screen.scale_x;                                                   
    obj[0].rect.height = 20 * screen.scale_y;                                                   
    obj[0].rect.x = (screen.virtual_width / 2 - obj[0].rect.width / 2) * screen.scale_x;    
    obj[0].rect.y = (screen.virtual_height - obj[0].rect.height * 10) * screen.scale_y;      
    obj[0].speed.x=0;
    obj[0].speed.y=0;

    // maze walls
    obj[1].role=3;
    obj[1].rgba=LIGHTGRAY;
    obj[1].shape=0;
    obj[1].rect.width = 20 * screen.scale_x;                                                   
    obj[1].rect.height = screen.virtual_height * screen.scale_y * 0.90;                                                   
    obj[1].rect.x = 840 * screen.scale_x;    
    obj[1].rect.y = 200 * screen.scale_y;      
    obj[1].speed.x=0;
    obj[1].speed.y=0;

    obj[2].role=3;
    obj[2].rgba=LIGHTGRAY;
    obj[2].shape=0;
    obj[2].rect.width = 20 * screen.scale_x;                                                   
    obj[2].rect.height = screen.virtual_height * screen.scale_y * 0.90;                                                   
    obj[2].rect.x = 3000 * screen.scale_x;    
    obj[2].rect.y = 200 * screen.scale_y;      
    obj[2].speed.x=0;
    obj[2].speed.y=0;

    obj[3].role=3;
    obj[3].rgba=LIGHTGRAY;
    obj[3].shape=0;
    obj[3].rect.width = obj[2].rect.x - obj[1].rect.x;                                                   
    obj[3].rect.height = 20 * screen.scale_y;                                                   
    obj[3].rect.x = obj[1].rect.x;    
    obj[3].rect.y = obj[1].rect.y;   
    obj[3].speed.x=0;
    obj[3].speed.y=0;

    // ball
    obj[4].role=2;
    obj[4].rgba=LIGHTGRAY;
    obj[4].shape=0;
    obj[4].rect.width = 20 * screen.scale_x;                                                   
    obj[4].rect.height = 20 * screen.scale_y;                                     
    obj[4].rect.x = obj[0].rect.x + obj[0].rect.width / 2 - obj[4].rect.width / 2;    
    obj[4].rect.y = obj[0].rect.y - obj[0].rect.height * 1.5;   
    obj[4].speed.x=0;
    obj[4].speed.y=0;

    // bricks   
    int bid=4;
    int brick_startx= obj[1].rect.x + obj[1].rect.width + 10 * screen.scale_x;
    int brick_starty= obj[3].rect.y + obj[3].rect.height + 150* screen.scale_y;

    for(int c=0; c<8; c++)
    {
        for(int l=0; l<14; l++)
        {
            bid++;

            obj[bid].role=1;
            obj[bid].rgba=LIGHTGRAY;
            obj[bid].shape=0;
            obj[bid].rect.width = 142 * screen.scale_x;                                                   
            obj[bid].rect.height = 50 * screen.scale_y;                                                   
            obj[bid].rect.x = brick_startx + (obj[bid].rect.width + 10 * screen.scale_x) * l;    
            obj[bid].rect.y = brick_starty + (obj[bid].rect.height + 10 * screen.scale_y) * c;     
            obj[bid].speed.x=0;
            obj[bid].speed.y=0;
        }
    }



    // Main game loop
    while (!WindowShouldClose() && time_to_die==0)    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        if(scene==1) // the background story
        {
            draw_intro_frame();
        }



        if(scene==2) // splash screen
        {
            ClearBackground(BLACK);

            // draw the background image
            position.x = 0.0f;
            position.y = 0.0f;
            DrawTextureEx(splash_background, position, 0.0f, screen.scale_x, WHITE);

            // the buttons
            for(int b=0;b<3;b++)
            {
                //position the buttons
                position.x = (screen.virtual_width / 2 - button[b].width / 2) * screen.scale_x;
                position.y = (1000.0f + b * 250) * screen.scale_y;

                //define button bounds
                Rectangle bounds = { position.x, position.y, button[b].width * screen.scale_x, button[b].height * screen.scale_y};

                if( CheckCollisionPointRec(GetMousePosition(), bounds) )
                {
                    // if we are hoovering the button make it slightly larger and adjust X position
                    position.x -= 10 * screen.scale_x;
                    DrawTextureEx(button[b], position, 0.0f, screen.scale_x+0.01, WHITE);

                    if( IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && b==0)
                    {
                        //play the game
                        scene=3;
                    }

                    if( IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && b==1)
                    {
                        //play the intro
                        scene=1;
                        story_text=0;
                        story_time=0;
                    }

                    if( IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && b==2)
                    {
                        // exit game
                        time_to_die=1;
                    }
                }
                else
                {
                    DrawTextureEx(button[b], position, 0.0f, screen.scale_x, WHITE);                    
                }
            }

        }



        if(scene==3) // game scene
        {
            ClearBackground(BLACK);

            position=GetMousePosition();

            // bat is at mouse X position if within play area
            if(position.x >= obj[1].rect.x + obj[1].rect.width && position.x <= obj[2].rect.x - obj[0].rect.width)
                obj[0].rect.x=position.x;
            else if(position.x < obj[1].rect.x + obj[1].rect.width)
            {
                obj[0].rect.x = obj[1].rect.x + obj[1].rect.width;
            }
            else if(position.x > obj[1].rect.x + obj[1].rect.width)
            {
                obj[0].rect.x = obj[2].rect.x - obj[0].rect.width;
            }            

            // draw everything
            for(int which=0; which<117; which++)
            {
                if(obj[which].shape==0)
                {
                    // If object is a ball 
                    if(obj[which].role==2)
                    {
                        // ...and there is no movement (start ou restart a new ball)
                        if(obj[which].speed.x==0 && obj[which].speed.y==0 && player.lives>0)
                        {
                           if ( IsMouseButtonReleased(MOUSE_LEFT_BUTTON)   || 
                                IsMouseButtonReleased(MOUSE_MIDDLE_BUTTON) ||
                                IsMouseButtonReleased(MOUSE_RIGHT_BUTTON))
                           {
                                obj[which].speed.x = 0;
                                obj[which].speed.y = -2;
                           }    
                        }

                        // check collisions (only balls collide... remember that.)
                        // the ball must be moving to collide with anything...
                        if(obj[which].speed.x != 0 || obj[which].speed.y != 0) 
                        {
                            ball_collision(which);
                        }
                    }
 

                    //move the object
                    obj[which].rect.x += obj[which].speed.x;
                    obj[which].rect.y += obj[which].speed.y;

                    // draw
                    DrawRectangle(obj[which].rect.x, obj[which].rect.y, obj[which].rect.width, obj[which].rect.height, obj[which].rgba);
 
                    // loosing a life
                    if(obj[which].role==2 && (obj[which].rect.y>screen.virtual_height * screen.scale_y ||
                                              obj[which].rect.y<0)  )
                    {
                        player.lives -= 1;
                        obj[which].speed.x=0;
                        obj[which].speed.y=0;
                        obj[which].rect.y = obj[0].rect.y - obj[0].rect.height * 1.5;   
                        obj[which].rect.x = obj[0].rect.x + obj[0].rect.width / 2 - obj[4].rect.width / 2;    
                    }





                    // player / game information
                    draw_game_info();
                }
            }

        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }





    // De-Initialization
    //--------------------------------------------------------------------------------------
    
    // unload our textures

    // story/intro
    for(int t=0; t<14;t++) UnloadTexture(texture[t]);

    // splash screen & buttons
    UnloadTexture(splash_background);
    for(int t=0; t<3;t++)  UnloadTexture(button[t]);

    // Unload sounds from RAM
    UnloadSound(music);  

    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)
    CloseWindow();        // Close window and OpenGL context

    //--------------------------------------------------------------------------------------

    return 0;
}

