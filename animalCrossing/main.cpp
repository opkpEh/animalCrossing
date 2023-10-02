#include <raylib.h>

class Game {
public:

    Texture2D grassSprite, playerSprite;
    Rectangle playerSrc, playerDest;
    float playerSpeed=3;
    
    bool playerMoving=false ;
    int playerDir = 0;
    bool playerUp = false, playerDown = false, playerLeft = false, playerRight = false;
    int playerFrame=0;

    int frameCount=0;

    Camera2D cam;
    float cameraZoom = 2.0f;

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

        cam = Camera2D{ Vector2{(float)(GetScreenWidth() / 2.0f),(float)(GetScreenHeight() / 2.0f)}, Vector2{(playerDest.x - playerDest.width / 2),(playerDest.y - playerDest.height / 2)}, 0.0, 1.0 };
        cam.zoom= cameraZoom;
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
            playerMoving = true;
            playerDir = 1;
            playerUp = true;
        }
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        {
            playerMoving = true;
            playerDir = 0;
            playerDown = true;
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        {
            playerMoving = true;
            playerDir = 3;
            playerRight = true;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        {
            playerMoving = true;
            playerDir = 2;
            playerLeft = true;
        }
        if (IsKeyPressed(KEY_Q))
        {
            musicPaused = !musicPaused;
        }

    }
    void update()
    {
        running = !WindowShouldClose();


        playerSrc.x = playerSrc.width * (float)playerFrame;

        if (playerMoving)
        {
            if (playerUp) { playerDest.y -= playerSpeed; }
            if (playerDown) { playerDest.y += playerSpeed; }
            if (playerLeft) { playerDest.x -= playerSpeed; }
            if (playerRight) { playerDest.x += playerSpeed; }
            if (frameCount % 8 == 1) { playerFrame++; }
        }
        else if (frameCount % 45 == 1) { playerFrame++; }

        frameCount++;

        if (playerFrame > 3) { playerFrame = 0; }
        if (!playerMoving && playerFrame > 1) { playerFrame = 0; }

        playerSrc.x = playerSrc.width * (float)playerFrame;
        playerSrc.y = playerSrc.height * (float)playerDir;

        UpdateMusicStream(music);
        if (musicPaused)
        {
            PauseMusicStream(music);
        }
        else
        {
            ResumeMusicStream(music);
        }

        cam.target = Vector2{ (playerDest.x - playerDest.width / 2),(playerDest.y - playerDest.height / 2) };

        playerMoving = false;
        playerUp = false;
        playerDown = false;
        playerRight = false;
        playerLeft =  false;
        
    }

    void render() {
        BeginDrawing();
        ClearBackground(bkgColor);
        BeginMode2D(cam);

        drawScene();

        EndMode2D();
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
    const int screenWidth = 1080;
    const int screenHeight = 720;
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
