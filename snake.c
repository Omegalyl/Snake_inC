#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "snake.h"

const Vector2 FOOD_SIZE = {15, 15};
const Color FOOD_COLOR = RED;
Vector2 FOOD_POS = (Vector2){0, 0};
bool FOOD_ALIVE = 0;


const char* TITLE = "SNAKE";
const char* TITLE_TEXT = "PRESS ENTER TO PLAY";

const char* END_TITLE = "GAME OVER";
const char* END_TITLE_TEXT = "PRESS ENTER TO PLAY AGAIN";

const int SCREEN_WIDTH= 800;
const int SCREEN_HEIGHT= 600;

const Vector2 SNAKE_SIZE = {15, 15};
Color SNAKE_COLOR = GREEN;

int SNAKE_LEN = 1;
Body *snake;
Vector2 dir = {15, 0};
Vector2 old_pos;
int frameCounter = 0;

#define DrawFood() \
    DrawRectangleV(FOOD_POS, FOOD_SIZE, FOOD_COLOR);


int main() {

    GameScreen currentScreen = MAIN;
    
    // INIT
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SNAKE");

    // FPS
    SetTargetFPS(30);


    // sanke
    snake = (Body*)malloc(SNAKE_LEN*sizeof(Body));


    int endtitleX = (SCREEN_WIDTH - MeasureText(END_TITLE, 40))/2;
    int endtextX = (SCREEN_WIDTH - MeasureText(END_TITLE_TEXT, 20))/2;

    int titleX = (SCREEN_WIDTH - MeasureText(TITLE, 40))/2;
    int textX = (SCREEN_WIDTH - MeasureText(TITLE_TEXT, 20))/2;

    Vector2 old_pos;

    while (!WindowShouldClose()) {

        switch (currentScreen)
        {
        case MAIN:
            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = GAMEPLAY;
            }
            break;
        
        case GAMEPLAY:

            frameCounter++;
            if (frameCounter == 2) {

                for (int i=0; i < SNAKE_LEN; i++) {


                    if (i==0){
                        old_pos = snake[i].pos;
                        snake[i].pos.x += dir.x;
                        snake[i].pos.y += dir.y;
                    } else {
                        Vector2 temp = snake[i].pos;
                        snake[i].pos = old_pos;
                        old_pos = temp;
                        // printf("new pos: %f\n", temp.x);
                    }


                    

                }
                frameCounter = 0;
            }

            if (Overlap(snake[0].pos, FOOD_POS)) {
                FOOD_ALIVE = 0;
                SNAKE_LEN++;
                Body* temp = (Body *)realloc(snake, SNAKE_LEN*sizeof(Body));
                snake = temp;
            }

            for (int i=5; i < SNAKE_LEN - 1; i++) {
                if (Overlap(snake[0].pos , snake[i].pos)) {
                    currentScreen = END;
                }
            }

            UpdatePos(snake, &dir);

            break;
        
        case END:
            reset();
            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = GAMEPLAY;
            }
            break;
        
        default:
            break;
        }

        // Draw
        BeginDrawing();

            ClearBackground(BLACK);

            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
            switch (currentScreen)
            {
                case MAIN:

                    DrawText(TITLE, titleX, 20, 40, GREEN);
                    DrawText(TITLE_TEXT, textX, SCREEN_HEIGHT/2, 20, GREEN);
                    break;

                case GAMEPLAY:
                    // Draw snake
                    SNAKE_COLOR = GREEN;
                    for (int i=0; i < SNAKE_LEN; i++) {
                        if (i!=0) {
                            SNAKE_COLOR = DARKGREEN;
                        }
                        DrawRectangleV(snake[i].pos, SNAKE_SIZE, SNAKE_COLOR);
                    }

                    // Draw Food
                    if (!FOOD_ALIVE) {
                        DrawFood_R();
                        FOOD_ALIVE = 1;
                    } else {
                        DrawFood();
                    }

                    break;

                case END:

                    DrawText(END_TITLE, endtitleX, 20, 40, GREEN);
                    DrawText(END_TITLE_TEXT, endtextX, SCREEN_HEIGHT/2, 20, GREEN);
                    break;
            
                default:
                    break;
            }

        
        EndDrawing();

    };

    return 0;
}

void DrawFood_R() {

    Vector2 pos; 

    pos.x = 1 + rand()/((RAND_MAX + 1u)/SCREEN_WIDTH);
    pos.y = 1 + rand()/((RAND_MAX + 1u)/SCREEN_HEIGHT);

    // update food pos
    FOOD_POS.x  = pos.x;
    FOOD_POS.y = pos.y;
    
    DrawRectangleV(pos, FOOD_SIZE, FOOD_COLOR);
}

void UpdatePos(Body *snake, Vector2 *dir) {

    // Update pos
    if (IsKeyPressed(KEY_D) && dir->x == 0) {
        dir->x = 15;
        dir->y = 0;
    }
            
    if (IsKeyPressed(KEY_A) && dir->x == 0) {
        dir->x = -15;
        dir->y = 0;
    }

    if (IsKeyPressed(KEY_S) && dir->y == 0) {
        dir->y = 15;
        dir->x = 0;
    }

    if (IsKeyPressed(KEY_W) && dir->y == 0) {
        dir->y = -15;
        dir->x = 0;
    }

    if (snake[0].pos.x > SCREEN_WIDTH) {
        snake[0].pos.x = 0;
    }


    if (snake[0].pos.x < 0) {
        snake[0].pos.x = SCREEN_WIDTH;
    }

    if (snake[0].pos.y < 0) {
        snake[0].pos.y = SCREEN_HEIGHT;
    }

    if (snake[0].pos.y > SCREEN_HEIGHT) {
        snake[0].pos.y = 0;
    }
}

bool Overlap(Vector2 pos1, Vector2 pos2) {
    
    if (pos1.x >= pos2.x && pos1.x <= (pos2.x + 15)) {
        if (pos1.y >= pos2.y && pos1.y <= (pos2.y + 15)) {
            return 1;
        }
    }
    return 0;
}

void reset() {
    frameCounter = 0;
    SNAKE_LEN = 1;
    snake = (Body*)malloc(SNAKE_LEN*sizeof(Body));
    old_pos.x = 0;
    old_pos.y = 0;
}