#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

//window dimensions
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

struct FramedPicture {
    SDL_Texture* texture;
    int srcW, srcH;
};

int main(int argc, char* argv[]) {
    // initialising SDL3 and SDL_image
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

    SDL_Texture* wallTexture = IMG_LoadTexture(renderer, "assets/wall.jpg"); 
    SDL_Texture* scene1Tex = IMG_LoadTexture(renderer, "assets/scene1.jpeg"); 
    SDL_Texture* scene2Tex = IMG_LoadTexture(renderer, "assets/scene2.jpeg"); 
    SDL_Texture* scene3Tex = IMG_LoadTexture(renderer, "assets/scene3.jpeg");

    if (!wallTexture || !scene1Tex || !scene2Tex || !scene3Tex) {
        std::cerr << "Failed to load one or more textures. Check asset paths!" << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    //error handling

    float s1W, s1H, s2W, s2H, s3W, s3H;
    SDL_GetTextureSize(scene1Tex, &s1W, &s1H);
    SDL_GetTextureSize(scene2Tex, &s2W, &s2H);
    SDL_GetTextureSize(scene3Tex, &s3W, &s3H);

    int frameThickness = 12; 

    SDL_FRect pic1Rect = { 40.0f, 170.0f, 400.0f, 260.0f };
    SDL_FRect frame1Rect = { pic1Rect.x - frameThickness, pic1Rect.y - frameThickness,
                             pic1Rect.w + (frameThickness * 2), pic1Rect.h + (frameThickness * 2) };

    SDL_FRect pic2Rect = { 560.0f, 170.0f, 400.0f, 260.0f };
    SDL_FRect frame2Rect = { pic2Rect.x - frameThickness, pic2Rect.y - frameThickness,
                             pic2Rect.w + (frameThickness * 2), pic2Rect.h + (frameThickness * 2) };

    SDL_FRect pic3Rect = { 300.0f, 480.0f, 400.0f, 260.0f };
    SDL_FRect frame3Rect = { pic3Rect.x - frameThickness, pic3Rect.y - frameThickness,
                             pic3Rect.w + (frameThickness * 2), pic3Rect.h + (frameThickness * 2) };

    //main Loop
    bool keepRunning = true;
    SDL_Event event;

    while (keepRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                keepRunning = false;
            }
        }

        SDL_RenderClear(renderer);

        SDL_RenderTexture(renderer, wallTexture, NULL, NULL);

        SDL_SetRenderDrawColor(renderer, 197, 160, 89, 255);
        SDL_RenderFillRect(renderer, &frame1Rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDebugText(renderer, pic1Rect.x - 2, pic1Rect.y - 2, ""); 
        SDL_RenderTexture(renderer, scene1Tex, NULL, &pic1Rect);

    
        SDL_SetRenderDrawColor(renderer, 197, 160, 89, 255);
        SDL_RenderFillRect(renderer, &frame2Rect);
        SDL_RenderTexture(renderer, scene2Tex, NULL, &pic2Rect);

       
        SDL_SetRenderDrawColor(renderer, 197, 160, 89, 255);
        SDL_RenderFillRect(renderer, &frame3Rect);
        SDL_RenderTexture(renderer, scene3Tex, NULL, &pic3Rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(wallTexture);
    SDL_DestroyTexture(scene1Tex);
    SDL_DestroyTexture(scene2Tex);
    SDL_DestroyTexture(scene3Tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}