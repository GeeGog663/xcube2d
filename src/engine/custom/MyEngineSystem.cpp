#include "MyEngineSystem.h"
using namespace std;

//MyEngineSystem
MyEngineSystem::MyEngineSystem() {}

SDL_Rect MyEngineSystem::getCurrentFrameRect(string id)
{
    SDL_Rect* rect = nullptr;
    for (AnimatedSprite animation : loadedAnimations) {
        if (animation.id == id)
        {
            rect = &animation.getCurrentRect();
            break;
        }
    }

    if (rect != nullptr)
    {
        return *rect;
    }
    else
    {
        debug("No animation found");
        return SDL_Rect{0,0,0,0};
    }
}

void MyEngineSystem::updateAnimations()
{
    for (AnimatedSprite& animation : loadedAnimations) {

        if (animation.updateCooldown > 60 / animation.getFramerate())
        {
            animation.updateFrame();
            animation.updateCooldown = 0;
        }
        else animation.updateCooldown++;
    }
}

AnimatedSprite MyEngineSystem::createAnimation(string id, int width, int height, float frameRate, int frameCount)
{
    AnimatedSprite* sprite = new AnimatedSprite(id, width, height, frameRate, frameCount);

    loadedAnimations.push_back(*sprite);

    return *sprite;
}

//AnimatedSprite
AnimatedSprite::AnimatedSprite(string givenid, int givenWidth, int givenHeight, float givenFrameRate, int givenFrameCount)
{
    id = givenid;
    width = givenWidth;
    height = givenHeight;
    frameRate = givenFrameRate;
    frameCount = givenFrameCount;

    updateCooldown = 0;

    generateFrames();
}

void AnimatedSprite::generateFrames()
{
    for (int i = 0; i < frameCount; i++) {
        frames.push_back(SDL_Rect{
            width * i,
            0,
            width,
            height
            });
    }

    frame = 0;
    currentSprite = frames[0];
}

void AnimatedSprite::updateFrame()
{
    currentSprite = frames[frame];
    frame++;

    if (frame > frameCount - 1) frame = 0;
}
