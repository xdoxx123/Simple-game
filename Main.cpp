#include "raylib.h"
#include "random"
#include "time.h"
#include <iostream>
#include <string>
#include <vector>

int Clamp(float num, float min, float max) 
{
    if (num > max) {
        return max;
    }
    if (num < min) {
        return min;
    }
    return num;
}

int main() {
    const int screenWidth = 1600;
    const int screenHeight = 1000;
    bool RenderFPS = false;


    InitWindow(screenWidth, screenHeight, "Raylib Camera Example");

    Texture2D txt = LoadTexture("images/parrot.png");

    typedef struct {
        int x;
        int y;
    } Rock;

    std::vector<Rock> table(556);

    Camera2D cam = { 0 };
    cam.target = { screenWidth / 2.0f, screenHeight / 2.0f };
    cam.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    cam.zoom = 1.0f;  
    cam.rotation = 0.0f; 

    float x = 0;
    float timer = 0;
    float y = 500;


    SetTargetFPS(60);
    bool yea = true;
    int Speed = 500;


    while (!WindowShouldClose() && yea) {
        HideCursor();
        float deltaTime = GetFrameTime();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, screenHeight);
        int random_number = dis(gen);

        if (IsKeyDown(KEY_W)) {
            y -= Speed * deltaTime;
        }
        if (IsKeyDown(KEY_S)) {
            y += Speed * deltaTime;
        }
        if (IsKeyPressed(KEY_F1)) {
            RenderFPS = !RenderFPS;
        }

        timer += 1;
        if (timer > 10) {
            timer = 0;
            Speed += 1;
            Rock temp = {screenWidth, random_number};
            table.push_back(temp);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);


        BeginMode2D(cam);

        if (y > 1000.0f) {
            y = 1000.0f;
        };
        if (y < 0.0f) {
            y = 0.0f;
        };

        Rectangle imgRect = {x, y, (float)txt.width * 0.5f, (float)txt.height * 0.5f};
        DrawTextureEx(txt, {x, y}, 0.0f, 0.5f, WHITE);

        if (RenderFPS) {
            DrawFPS(50, 100);
        }

        for (size_t i = 0; i < table.size(); i++) {
            Rock& thing = table[i]; 

            thing.x -= 10;

           
            Rectangle rockRect = { (float)thing.x, (float)thing.y, 50.0f, 50.0f };
            if (CheckCollisionRecs(rockRect, imgRect)) {
              
                yea = false;
                break;
                table.erase(table.begin() + i);
                i--; 
            }

            if (thing.x >= screenWidth) {
                table.erase(table.begin() + i);
                i--;  
            }
        }

        for (size_t i = 0; i < table.size(); i++) {
            Rock thing = table[i];
            DrawRectangle(thing.x, thing.y, 50, 50, RED);
        }

    
        EndMode2D();

        EndDrawing();
    }

    UnloadTexture(txt);
    CloseWindow();

    return 0;
}
