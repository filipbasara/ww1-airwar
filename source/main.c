#include "main.h"
#include <stdbool.h>
struct Window screen;
struct Entity* Player;
struct Entity* Enemy;
struct Entity Projectile;

RenderTexture2D render_target;
Rectangle viewport_buffer;
Rectangle render_buffer;
Vector2 mouse;

float render_scale;
float delta;

bool enable_debug;
bool is_key_pressed;

KeyboardKey key;

void
init(void)
{

  enable_debug = false;

  screen.title = "Raylib Test";
  screen.mode = WINDOWED;
  screen.width = SCREEN_WIDTH;
  screen.height = SCREEN_HEIGHT;
  screen.render_width = RENDER_WIDTH;
  screen.render_height = RENDER_HEIGHT;

  InitWindow(screen.width, screen.height, screen.title);

  SetConfigFlags(FLAG_VSYNC_HINT);
  SetTargetFPS(TARGET_FPS);
  SetWindowMinSize(320, 240);
  SetTraceLogLevel(LOG_NONE);

  printf(
    "Resolution returned to raylib: %d, %d\n", screen.width, screen.height);

  update_window_mode(screen.mode);
}

void
setup(void)
{

  Player = create_entity("Player",
                         (Vector2){ 32, screen.render_height - 32 },
                         (Vector2){ 32, 16 },
                         (Vector2){ 0, 0 },
                         50.0f,
                         1.0f,
                         0.0f,
                         100.0f,
                         0.0f,
                         "P:/raylib_starter/source/assets/planes/ww1_plane.png",
                         WHITE);
}

void
process_input(void)
{

  if (IsKeyDown(KEY_W)) {
    Player->velocity.y = -1;

  } else if (IsKeyReleased(KEY_W)) {
    Player->velocity.y = 0;
  }
  if (IsKeyDown(KEY_S)) {
    Player->velocity.y = 1;

  } else if (IsKeyReleased(KEY_S)) {
    Player->velocity.y = 0;
  }
  if (IsKeyDown(KEY_D)) {
    Player->velocity.x = 1;

  } else if (IsKeyReleased(KEY_D)) {
    Player->velocity.x = 0;
  }
  if (IsKeyDown(KEY_A)) {
    Player->velocity.x = -1;

  } else if (IsKeyReleased(KEY_A)) {
    Player->velocity.x = 0;
  }

  if (IsKeyDown(KEY_SPACE)) {
  }
  if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT))) {
    if (screen.mode == WINDOWED) {
      update_window_mode(FULLSCREEN);
    } else {
      update_window_mode(WINDOWED);
    }
  }
}
void
update(void)
{
  delta = GetFrameTime();

  render_scale = min((float)GetScreenWidth() / screen.render_width,
                     (float)GetScreenHeight() / screen.render_height);

  mouse = GetMousePosition();

  SetMouseOffset(-(screen.render_width * render_scale),
                 -(screen.render_height * render_scale));
  SetMouseScale(1 / render_scale, 1 / render_scale);

  update_entities();
}

void
render_setup(void)
{
  render_target = LoadRenderTexture(screen.render_width, screen.render_height);
  SetTextureFilter(render_target.texture, FILTER_POINT);
}

void
render(void)
{

  // Write all render updates to a render target textures
  BeginTextureMode(render_target);
  ClearBackground(BLACK);

  if (enable_debug == true) {
    draw_debug_text();
  }

  render_entities();

  EndTextureMode();

  // Start writing to framebuffer
  BeginDrawing();

  viewport_buffer.x = 0.0f;
  viewport_buffer.y = 0.0f;
  viewport_buffer.width = (float)render_target.texture.width;
  viewport_buffer.height = (float)-render_target.texture.height;

  render_buffer.x = 0.0f;
  render_buffer.y = 0.0f;
  render_buffer.width = (float)screen.render_width * render_scale;
  render_buffer.height = (float)screen.render_height * render_scale;

  ClearBackground(WHITE);
  // Draw render texture to screen, properly scaled

  DrawTexturePro(render_target.texture,
                 viewport_buffer,
                 render_buffer,
                 (Vector2){ 0, 0 },
                 0.0f,
                 WHITE);

  DrawFPS(10, 10);

  int entitiy_count;
  for (int i = 0; i < MAX_ENTITIES; ++i) {
    if (entities[i].id == 0) {
      entitiy_count = i;
      break;
    }
  }
  DrawText(FormatText("TOTAL ENTITIES: %i", entitiy_count), 20, 20, 30, RED);

  EndDrawing();
}

void
deinit(void)
{
  UnloadRenderTexture(render_target);
}

void
update_window_mode(int window_mode)
{

  screen.mode = window_mode;

  if (screen.mode == FULLSCREEN) {
    screen.width = GetMonitorWidth(0);
    screen.height = GetMonitorHeight(0);
    ToggleFullscreen();
    SetWindowSize(screen.width, screen.height);

  } else {
    screen.width = SCREEN_WIDTH;
    screen.height = SCREEN_HEIGHT;
    SetWindowSize(screen.width, screen.height);
    if (IsWindowFullscreen()) {
      ToggleFullscreen();
    }
  }
}

// Clamp Vector2 value with min and max and return a new vector2
// NOTE: Required for virtual mouse, to clamp inside virtual game size
Vector2
ClampValue(Vector2 value, Vector2 min, Vector2 max)
{
  Vector2 result = value;
  result.x = (result.x > max.x) ? max.x : result.x;
  result.x = (result.x < min.x) ? min.x : result.x;
  result.y = (result.y > max.y) ? max.y : result.y;
  result.y = (result.y < min.y) ? min.y : result.y;
  return result;
}

void
draw_debug_text()
{
  DrawText(TextFormat("Default Mouse: [%i , %i]", (int)mouse.x, (int)mouse.y),
           10,
           20,
           5,
           GREEN);

  DrawText(TextFormat("WINDOW MODE: %d", (IsWindowFullscreen() ? 1 : 0)),
           10,
           40,
           5,
           GREEN);

  DrawText(TextFormat("WINDOW SIZE: [%i , %i]", screen.width, screen.height),
           10,
           60,
           5,
           GREEN);

  DrawText(TextFormat("RENDER SIZE: [%i , %i]",
                      screen.render_width,
                      screen.render_height),
           10,
           80,
           5,
           GREEN);

  DrawText(TextFormat("RENDER SCALE: %f", render_scale), 10, 100, 5, GREEN);

  printf("Physical mouse position: %f:%f\n",
         GetMousePosition().x,
         GetMousePosition().y);

  printf(
    "Render size W: %d | H: %d\n", screen.render_width, screen.render_height);

  printf("Window size W: %d | H: %d\n", screen.width, screen.height);
}

struct Entities*
create_entity(char* display_name,
              Vector2 position,
              Vector2 size,
              Vector2 velocity,
              float speed,
              float scale,
              float rotation,
              float health,
              float damage,
              const char* texture_path,
              Color tint)
{
  struct Entity entity;
  entity.id = ++global_entity_count;
  entity.display_name = display_name;
  entity.position = position;
  entity.size = size;
  entity.scale = scale;
  entity.speed = speed;
  entity.rotation = rotation;
  entity.velocity = velocity;
  entity.tint = tint;
  entity.health = health;
  Texture texture = LoadTexture(texture_path);

  if (texture.id <= 0) {
    printf("Texture [%s] could not be loaded!\n", texture_path);
  }
  entity.texture = texture;
  entity.texture.width = entity.size.x;
  entity.texture.height = entity.size.y;

  for (int i = 0; i < MAX_ENTITIES; ++i) {

    if (entities[i].id == 0) {
      entities[i] = entity;
      return &entities[i];
      break;
    }
  }

  return 0;
}

void
render_entities(void)
{

  for (int i = 0; i < MAX_ENTITIES; ++i) {
    if (entities[i].id == 0) {
      break;
    }

    if (entities[i].texture.id != 0) {
      DrawTexture(entities[i].texture,
                  entities[i].position.x,
                  entities[i].position.y,
                  entities[i].tint);
    }
  }
}

void
update_entities(void)
{

  for (int i = 0; i < MAX_ENTITIES; ++i) {

    if (entities[i].id != 0) {
      if (entities[i].velocity.x != 0) {
        entities[i].position.x +=
          entities[i].velocity.x * entities[i].speed * delta;
      }
      if (entities[i].velocity.y != 0) {
        entities[i].position.y +=
          entities[i].velocity.y * entities[i].speed * delta;
      }

    } else {
      break;
    }
  }
}

int
main(void)
{

  init();

  setup();

  render_setup();

  while (!WindowShouldClose()) {
    process_input();
    update();
    render();
  }
  deinit();

  CloseWindow();

  return 0;
}
