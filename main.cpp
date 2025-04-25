#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "def.h"
#include <vector>
using namespace std;
int score = 0;
int best_score = 0;
struct Box;
struct Platform;
bool checkCollision(Box &box, const Platform& platform);

struct Platform {
    int x, y, w, h;
    SDL_Texture *texture = NULL;
    Platform(int _x, int _y, int _w, int _h) {
        x = _x; y = _y; w = _w; h = _h;
    }

    void setTexture (SDL_Texture* _texture) {
        texture = _texture;
    }

    void render(SDL_Renderer* renderer) {
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        if(texture) {
            SDL_RenderCopy(renderer, texture, NULL, &rect);
        }
    }

};

struct Box {
    int x, y, width, height;
    const int size = 60;
    float stepX = 6.5;
    bool isJumping = false;
    float velocityY = 0.0;
    float gravity = 0.3;
    float jumpStrength = -10.0;
    SDL_Texture *texture = NULL;

    Box(int _x, int _y) {
        x = _x;
        y = _y;
    }

    void render(SDL_Renderer* renderer) {
        SDL_Rect rect;
        rect.x = x;
        rect.y = y - size;
        rect.w = size;
        rect.h = size;
        if(texture) {
            SDL_RenderCopy(renderer, texture, NULL, &rect);
        }
    }

    void setTexture(SDL_Texture* _texture) {
        texture = _texture;
    }

    void move(const vector<Platform>& platforms) {
        if (isJumping) {
            velocityY += gravity;
            float remaining = velocityY;

            int steps = max(1, int(abs(remaining)));
            float dy = remaining / steps;

            for (int i = 0; i < steps; ++i) {
                y += dy;

                for (const Platform& p : platforms) {
                    if (checkCollision(*this, p)) {
                        y = p.y;
                        velocityY = 0;
                        isJumping = false;
                        return;
                    }
                }
            }
        }
    }

    void jumping() {
        if (!isJumping) {
            isJumping = true;
            velocityY = jumpStrength;
        }
    }

    void moveRight(const vector<Platform>& platforms) {
        x += stepX;
        if(x > SCREEN_WIDTH) x = -size;
    }

    void moveLeft(const vector<Platform>& platforms) {
        x -= stepX;
        if(x < -size) x = SCREEN_WIDTH;
    }
};

struct Sprite {
    SDL_Texture* texture;
    vector<SDL_Rect> clips;
    int currentFrame = 0;

    void init(SDL_Texture* _texture, int frames, const int _clips [][4]) {
        texture = _texture;
        SDL_Rect clip;
        for (int i = 0; i < frames; i++) {
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];
            clips.push_back(clip);
        }
    }
    void tick() {
        currentFrame = (currentFrame + 1) % clips.size();
    }

    const SDL_Rect* getCurrentClip() const {
        return &(clips[currentFrame]);
    }
};


bool checkCollision(Box& box, const Platform& platform) {
    // Chỉ kiểm tra phần chân
    const int footHeight = 6; // Chiều cao vùng chân
    SDL_Rect footRect = {
        box.x,
        box.y - footHeight, // phần đáy của box
        box.size,
        footHeight
    };

    SDL_Rect platRect = { platform.x, platform.y, platform.w, platform.h };

    if (SDL_HasIntersection(&footRect, &platRect) && box.velocityY >= 0) {
        box.y = platform.y;
        box.velocityY = 0;
        box.isJumping = false;
        return true;
    }
    return false;
}



bool isOverlapping(int x, int y, const vector<Platform>& platforms) {
    for (const auto& p : platforms) {
        int dx = abs(p.x - x);
        int dy = abs(p.y - y);
        if (dx < PLATFORM_WIDTH - MIN_X_GAP && dy < MIN_Y_GAP) {
            return true;
        }
    }
    return false;
}

void generatePlatforms(vector<Platform>& platforms, int count) {
    int prevY = SCREEN_HEIGHT;

    for (int i = 0; i < count; i++) {
        int y, x, tries = 0;
        do {
            int minGap = MAX_JUMP_HEIGHT / 2;
            int maxGap = MAX_JUMP_HEIGHT;
            int gap = minGap + rand() % (maxGap - minGap);
            y = prevY - gap;
            if (y < 0) y = 0;
            x = rand() % (SCREEN_WIDTH - PLATFORM_WIDTH);
            tries++;
        } while (isOverlapping(x, y, platforms) && tries < 20);

        platforms.push_back(Platform(x, y, PLATFORM_WIDTH, PLATFORM_HEIGHT));
        prevY = y;
    }
}

int main(int argc, char *argv[]) {
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);

    SDL_Event e;
    Box box(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    SDL_Texture *background = loadTexture("./images/background.png", renderer);
    SDL_Texture *boxTexture = loadTexture("./images/playerleft.png", renderer);
    SDL_Texture *platformTexture = loadTexture ("./images/platform.png", renderer);

    box.setTexture(boxTexture);

    vector<Platform> platforms;

    generatePlatforms(platforms, 10);

    const int CAMERA_THRESHOLD = 300;

    int max_height = box.y;

    while (box.y <= SCREEN_HEIGHT) {
        box.move(platforms);

        if (box.y < CAMERA_THRESHOLD) {
            int dy = CAMERA_THRESHOLD - box.y;
            box.y = CAMERA_THRESHOLD;

            for (Platform& p : platforms) {
                p.y += dy;
            }

            vector<Platform> newPlatforms;
            for (Platform& p : platforms) {
                if (p.y < SCREEN_HEIGHT)
                    newPlatforms.push_back(p);
            }

            int highestY = SCREEN_HEIGHT;
            for (const auto& p : newPlatforms) {
                if (p.y < highestY) highestY = p.y;
            }

            while (newPlatforms.size() < 25) {
                int minGap = MAX_JUMP_HEIGHT / 2;
                int maxGap = MAX_JUMP_HEIGHT;
                int gap = minGap + rand() % (maxGap - minGap);
                int newY = highestY - gap;
                int newX = rand() % (SCREEN_WIDTH - PLATFORM_WIDTH);

                if (!isOverlapping(newX, newY, newPlatforms)) {
                    newPlatforms.push_back(Platform(newX, newY, PLATFORM_WIDTH, PLATFORM_HEIGHT));
                    highestY = newY;
                }
            }

            platforms = newPlatforms;
            SDL_RenderCopy(renderer, platformTexture, NULL, NULL);
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);

        for (const Platform& p : platforms) {
            SDL_Rect rect = {p.x, p.y, p.w, p.h};
            SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
            SDL_RenderFillRect(renderer, &rect);
        }

        box.render(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(0);

        const Uint8* keystates = SDL_GetKeyboardState(NULL);

        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) break;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
        }

        if (!box.isJumping) {
            box.jumping();
        }
        if (keystates[SDL_SCANCODE_RIGHT]) box.moveRight(platforms);
        if (keystates[SDL_SCANCODE_LEFT]) box.moveLeft(platforms);



    }

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(boxTexture);
    SDL_Quit();
    return 0;
}
