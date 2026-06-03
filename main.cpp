#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

// Window dimensions
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

// Helper structure for our framed pictures
struct FramedPicture {
    SDL_Texture* texture;
    int srcW, srcH;
};

int main(int argc, char* argv[]) {
    // 1. Initialize SDL3 and SDL_image
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("2D Rendering - Gallery Wall", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // 2. Load Textures from the assets folder
    SDL_Texture* wallTexture = IMG_LoadTexture(renderer, "assets/wall.jpg"); // assuming .jpg or .png
    SDL_Texture* scene1Tex = IMG_LoadTexture(renderer, "assets/scene1.jpeg"); // Garage
    SDL_Texture* scene2Tex = IMG_LoadTexture(renderer, "assets/scene2.jpeg"); // Bedroom
    SDL_Texture* scene3Tex = IMG_LoadTexture(renderer, "assets/scene3.jpeg"); // Tesseract/Cube

    if (!wallTexture || !scene1Tex || !scene2Tex || !scene3Tex) {
        std::cerr << "Failed to load one or more textures. Check asset paths!" << std::endl;
        // Cleanup and exit if assets are missing
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Query dimensions for positioning
    float s1W, s1H, s2W, s2H, s3W, s3H;
    SDL_GetTextureSize(scene1Tex, &s1W, &s1H);
    SDL_GetTextureSize(scene2Tex, &s2W, &s2H);
    SDL_GetTextureSize(scene3Tex, &s3W, &s3H);

    // 3. Define layout sizes and positions (Adjusted for a 1000x800 window)
    int frameThickness = 12; // Gold frame border thickness

    // Top Left Frame (Garage)
    SDL_FRect pic1Rect = { 40.0f, 170.0f, 400.0f, 260.0f };
    SDL_FRect frame1Rect = { pic1Rect.x - frameThickness, pic1Rect.y - frameThickness,
                             pic1Rect.w + (frameThickness * 2), pic1Rect.h + (frameThickness * 2) };

    // Top Right Frame (Bedroom)
    SDL_FRect pic2Rect = { 560.0f, 170.0f, 400.0f, 260.0f };
    SDL_FRect frame2Rect = { pic2Rect.x - frameThickness, pic2Rect.y - frameThickness,
                             pic2Rect.w + (frameThickness * 2), pic2Rect.h + (frameThickness * 2) };

    // Bottom Center Frame (Tesseract)
    SDL_FRect pic3Rect = { 300.0f, 480.0f, 400.0f, 260.0f };
    SDL_FRect frame3Rect = { pic3Rect.x - frameThickness, pic3Rect.y - frameThickness,
                             pic3Rect.w + (frameThickness * 2), pic3Rect.h + (frameThickness * 2) };

    // 4. Main Loop
    bool keepRunning = true;
    SDL_Event event;

    while (keepRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                keepRunning = false;
            }
        }

        // Clear Screen
        SDL_RenderClear(renderer);

        // Draw Background Wall (stretched to fit window)
        SDL_RenderTexture(renderer, wallTexture, NULL, NULL);

        // --- DRAW PICTURE 1 (Garage) ---
        // Gold Frame
        SDL_SetRenderDrawColor(renderer, 197, 160, 89, 255); // Gold color
        SDL_RenderFillRect(renderer, &frame1Rect);
        // Inner Black Border
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDebugText(renderer, pic1Rect.x - 2, pic1Rect.y - 2, ""); // Trick to get crisp inner lines if needed, or just fill slightly larger rect
        // Actual Scene
        SDL_RenderTexture(renderer, scene1Tex, NULL, &pic1Rect);

        // --- DRAW PICTURE 2 (Bedroom) ---
        // Gold Frame
        SDL_SetRenderDrawColor(renderer, 197, 160, 89, 255);
        SDL_RenderFillRect(renderer, &frame2Rect);
        // Actual Scene
        SDL_RenderTexture(renderer, scene2Tex, NULL, &pic2Rect);

        // --- DRAW PICTURE 3 (Tesseract) ---
        // Gold Frame
        SDL_SetRenderDrawColor(renderer, 197, 160, 89, 255);
        SDL_RenderFillRect(renderer, &frame3Rect);
        // Actual Scene
        SDL_RenderTexture(renderer, scene3Tex, NULL, &pic3Rect);

        // Present to screen
        SDL_RenderPresent(renderer);
    }

    // 5. Cleanup
    SDL_DestroyTexture(wallTexture);
    SDL_DestroyTexture(scene1Tex);
    SDL_DestroyTexture(scene2Tex);
    SDL_DestroyTexture(scene3Tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}