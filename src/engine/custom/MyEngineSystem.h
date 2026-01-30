#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include <SDL_mixer.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <vector>

#include "../EngineCommon.h"
#include "../GraphicsEngine.h"

class MyEngineSystem;
class AnimatedSprite;

class MyEngineSystem {
	friend class XCube2Engine;
private:
	std::vector<AnimatedSprite> loadedAnimations;

	MyEngineSystem();
public:
	AnimatedSprite createAnimation(std::string id, int width, int height, float frameRate, int frameCount);
	void updateAnimations();
	SDL_Rect getCurrentFrameRect(std::string id);
};

class AnimatedSprite {
	friend class MyEngineSystem;
private:
	int width, height, frameCount, frame;
	float frameRate;
	std::string id;
	std::vector<SDL_Rect> frames;

	SDL_Rect currentSprite;
	SDL_Texture* spritesheet;

	void generateFrames();
protected:
	int updateCooldown;

	void updateFrame();
	SDL_Rect getCurrentRect() const { return currentSprite; }
	float getFramerate() const { return frameRate; }
public:
	AnimatedSprite(std::string, int, int, float, int);
};
#endif
