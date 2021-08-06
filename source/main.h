#pragma once
#include "constants.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>

int global_entity_count = 0;

struct Window
{
  char* title;
  int render_width;
  int render_height;
  int width;
  int height;
  int mode;
} Window;

struct Entity
{
  int id;
  Vector2 position;
  Vector2 size;
  Vector2 velocity;
  float speed;
  float scale;
  float rotation;
  float health;
  float damage;
  char* display_name;
  Rectangle shape;
  Texture texture;
  Color tint;

} entity;

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
              Color tint);

struct Entity entities[MAX_ENTITIES];

void
render_entities(void);

void
update_entities(void);

void
init(void);

void
deinit(void);

void
setup(void);

void
update(void);

void
process_input(void);

void
render_setup(void);

void
render(void);

void
update_window_mode(int window_mode);

Vector2
ClampValue(Vector2 value, Vector2 min, Vector2 max);

void
draw_debug_text(void);