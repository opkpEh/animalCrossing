#include <raylib.h>

class Game {
public:
    Game() {
        screenWidth = 1000;
        screenHeight = 480;

        InitWindow(screenWidth, screenHeight, "Animal Crossing");
        SetWindowState(FLAG_VSYNC_HINT);
        SetExitKey(0);
    }

    void drawScene() {}

    void input() {}

    void update() {
        running = !WindowShouldClose();
    }

    void render() {
        BeginDrawing();
        ClearBackground(bkgColor);

        drawScene();

        EndDrawing();
    }

    void quit() {
        CloseWindow();
    }   

    bool isRunning() const {
        return running;
    }

private:
    int screenWidth;
    int screenHeight;
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
