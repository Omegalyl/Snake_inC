#include "raylib.h"

typedef enum GameScreen { MAIN = 0, GAMEPLAY, END } GameScreen;

typedef struct Dir {
    Vector2 x;
    Vector2 y;
} Dir;

typedef struct Body {
    Vector2 pos;
    Dir dir;
} Body;

void UpdatePos(Body *snake, Vector2 *dir);
void DrawFood_R();
bool Overlap(Vector2 pos1, Vector2 pos2);