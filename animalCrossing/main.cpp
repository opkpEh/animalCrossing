#include <raylib.h>

class Game {
public:

    Texture2D grassSprite, playerSprite;
    Rectangle playerSrc, playerDest;
    float playerSpeed=2.25;
    bool musicPaused = false;
    Music music;

    Game() {
       
        InitWindow(screenWidth, screenHeight, "Animal Crossing");
        SetWindowState(FLAG_VSYNC_HINT);
        SetExitKey(0);

        grassSprite = LoadTexture("res/Tilesets/Grass.png");
        playerSprite = LoadTexture("res/Characters/BasicCharakterSpritesheet.png");

        playerSrc = Rectangle{ 0, 0, 48, 48 };
        playerDest = Rectangle{ 200, 200, 100, 100 };

        InitAudioDevice();
        music = LoadMusicStream("res/morning.mp3");
        PlayMusicStream(music);
      
    }

    void drawScene()
    {
        DrawTexture(grassSprite, 100, 50, WHITE);
        DrawTexturePro(playerSprite, playerSrc, playerDest, Vector2{ playerDest.width, playerDest.height }, 0, WHITE);
    }
    

    void input()
    {
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        {
            playerDest.y -= playerSpeed;
        }
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        {
            playerDest.y += playerSpeed;
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        {
            playerDest.x += playerSpeed;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        {
            playerDest.x -= playerSpeed;
        }
        if (IsKeyPressed(KEY_Q))
        {
            musicPaused = !musicPaused;
        }

    }
    void update()
    {
        running = !WindowShouldClose();
        UpdateMusicStream(music);
        if (musicPaused)
        {
            PauseMusicStream(music);
        }
        else
        {
            ResumeMusicStream(music);
        }
    }

    void render() {
        BeginDrawing();
        ClearBackground(bkgColor);

        drawScene();

        EndDrawing();
    }

    void quit() {
        CloseWindow();
        UnloadTexture(grassSprite);
        UnloadTexture(playerSprite);
        UnloadMusicStream(music);
        CloseAudioDevice;
    }   

    bool isRunning() const {
        return running;
    }

private:
    const int screenWidth = 1000;
    const int screenHeight = 480;
    bool running = true;
    Color bkgColor = { 147, 211, 196, 255 };
};

int main() {
    Game game;

    while (game.isRunning()) {
        game.input();
        game.update();
        game.render();
    }

    game.quit();

    return 0;
}
