#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__
#define WINDOWWIDTH 1920
#define WINDOWHEIGHT 1080
#include "HelloWorldScene.h"

class MenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void InitAnime(Animation* anime, char* temp);
    void update(float dt);
    void onMouseMove(Event* event);
    void onMouseDown(Event* event);
    Vec2 cursorPos;
    Sprite* video;
    Sprite* cursor;

    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);

};

#endif // __NEW_SCENE_H__
