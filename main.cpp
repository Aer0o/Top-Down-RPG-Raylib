#include "raylib.h"
#include "raymath.h"

int main()
{
  //Background dimensions
  int windowDimensions[2] = {384, 384};
  InitWindow(windowDimensions[0], windowDimensions[1], "Top Down RPG");

  Texture2D worldMap = LoadTexture("nature_tileset/WorldMap.png");
  Vector2 worldMapPos = {0.0, 0.0};
  float speed = 4.0;

  Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
  Vector2 knightPos = {
    (float)windowDimensions[0]/2.0f - 4.0f * (0.5f * (float)knight.width/6.0f),
    (float)windowDimensions[1]/2.0f - 4.0f * (0.5f * (float)knight.height)  
  };

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    Vector2 direction = {0,0};

    if(IsKeyDown(KEY_A)) direction.x -= 1.0;
    if(IsKeyDown(KEY_D)) direction.x += 1.0;
    if(IsKeyDown(KEY_W)) direction.y -= 1.0;
    if(IsKeyDown(KEY_S)) direction.y += 1.0; 
    if(Vector2Length(direction) != 0.0) 
    {
      // Subtract direction from mapPos to move the map
      worldMapPos = Vector2Subtract(worldMapPos,Vector2Scale(Vector2Normalize(direction), speed));
    }

    //Draw World Map
    DrawTextureEx(worldMap, worldMapPos, 0.0, 4.0, WHITE);

    //Draw a player
    Rectangle source = {0.0f, 0.0f, (float)knight.width/6.f, (float)knight.height};
    Rectangle dest = {knightPos.x, knightPos.y, 4.0f * (float)knight.width/6, 4.0f * (float)knight.height};
    DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);  

    EndDrawing();
  }
  UnloadTexture(worldMap);
  CloseWindow();
}