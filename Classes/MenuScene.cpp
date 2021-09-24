#include "MenuScene.h"
#include "SelectScene.h"


#define FILE_MAX 20
USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
   /* memset(musicInfo->WallpaperFile, NULL, sizeof(musicInfo->WallpaperFile));
    memset(musicInfo->soundFile, NULL, sizeof(musicInfo->soundFile));
    memset(musicInfo->FileName, NULL, sizeof(musicInfo->FileName));
    memset(musicInfo->artist, NULL, sizeof(musicInfo->artist));
    memset(musicInfo->title, NULL, sizeof(musicInfo->title));*/

    char* temp = new char[FILE_MAX];
    video = Sprite::create("Menu/Frame (1).jpg");
    video->setPosition(Vec2(WINDOWWIDTH / 2, WINDOWHEIGHT / 2));
    this->addChild(video);
    Animation *anime = Animation::create();
    InitAnime(anime, temp);

    // cursor 
    cursor = Sprite::create("UI/Cursor.png");
    cursor->setScale(0.75);
    cursor->setPosition(Vec2(WINDOWWIDTH / 2, WINDOWHEIGHT / 2));
    this->addChild(cursor);
    
    
    
    Animate* animate = Animate::create(anime);
    video->runAction(RepeatForever::create(animate));
    
    auto mouseEvent = EventListenerMouse::create(); 
    mouseEvent->onMouseMove = CC_CALLBACK_1(MenuScene::onMouseMove, this);
    mouseEvent->onMouseDown = CC_CALLBACK_1(MenuScene::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseEvent, this);
    
    scheduleUpdate();
    return true;
}

void MenuScene::onMouseMove(Event * event)
{ 
    auto mouseEvent = static_cast<EventMouse *>(event);
    cursorPos = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY()); // 1256, 257, 1390-1256, 474 - 257
    CCLOG("%f %f", cursorPos.x, cursorPos.y);
}

void MenuScene::onMouseDown(Event* event)
{
    
    auto mouseEvent = static_cast<EventMouse*>(event);
    Rect cursorRect = cursor->getBoundingBox();
    Rect playRect;
    playRect.setRect(1256,257,134,217);
   
    if (cursorRect.intersectsRect(playRect))
    {
        auto scene = SelectScene::createScene();
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        Director::getInstance()->replaceScene(scene);
    }
}

void MenuScene::InitAnime(Animation* anime, char* temp)
{

    anime->setDelayPerUnit(0.1f);
    for (int i = 1; i <= 30; i++)
    {
        sprintf(temp, "Menu/Frame (%d).jpg", i);
        anime->addSpriteFrameWithFile(temp);
    }
    SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/BGM.mp3", true);
}



void MenuScene::update(float dt)
{
    cursor->setPosition(cursorPos);  
}

void MenuScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}