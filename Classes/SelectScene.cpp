#include "SelectScene.h"
#include "HelloWorldScene.h"


USING_NS_CC;
Scene* SelectScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = SelectScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SelectScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    Black = Sprite::create("UI/Black.png");
    

    // cursor 
    cursor = Sprite::create("UI/Cursor.png");
    cursor->setScale(0.75f);
    cursor->setPosition(Vec2(WINDOWWIDTH / 2, WINDOWHEIGHT / 2));
    this->addChild(cursor,3);


    // lis
    auto mouseEvent = EventListenerMouse::create();
    mouseEvent->onMouseMove = CC_CALLBACK_1(SelectScene::onMouseMove, this);
    mouseEvent->onMouseDown = CC_CALLBACK_1(SelectScene::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseEvent, this);

    EventListenerKeyboard* lis = EventListenerKeyboard::create();
    lis->onKeyPressed = CC_CALLBACK_2(SelectScene::onKeyPressed, this);
    lis->onKeyReleased = CC_CALLBACK_2(SelectScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    InitSongs();
    scheduleUpdate();
    return true;
}

enum
{
    Ghost,
    Hitorigoto,
    BadApple
};

void SelectScene::onMouseMove(Event* event)
{

    auto mouseEvent = static_cast<EventMouse*>(event);
    cursorPos = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY()); // 1256, 257, 1390-1256, 474 - 257'

    for (int i = 0; i < SONG_NUM; i++)
    {
        Rect song;
        if (songForm[i] != nullptr)
        {
            song = songForm[i]->getBoundingBox();
            if (song.containsPoint(cursorPos))
            {
                songForm[i]->runAction(ScaleTo::create(0.1f, 1.1f));
            }
            else
            {
                songForm[i]->runAction(ScaleTo::create(0.1f, 1.0f));
            }
        }
    }
}

void SelectScene::InitSongs()
{
    int index = 0;
    // 수정 
    SongLibray(this, songForm, backGround, "Library/Ghost/form.png", "Library/Ghost/Ghost.jpg", Vec2(osu->Center), index++);
    //SongLibray(this, songForm, backGround, "Library/Ghost/form.png", "Library/Hitorigoto/Hitorigoto.jpg",Vec2(osu->Center.x, osu->Center.y-400),1);
}

void SelectScene::onMouseDown(Event* event)
{

    auto mouseEvent = static_cast<EventMouse*>(event);
    Rect cursorRect = cursor->getBoundingBox();
    for (int i = 0; i < SONG_NUM; i++)
    {
        Rect song;
        if (songForm[i] != nullptr)
        {
            song = songForm[i]->getBoundingBox();
            if (song.containsPoint(cursorPos))
            {
                if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() == true)
                {
                    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
                }
                switch (i)
                {

                case Ghost:
                {
                    currSelect = Ghost;
                    click[i]++;
                    for (int i = 0; i < SONG_NUM; i++)
                    {
                        
                        if (i == currSelect)
                        {
                            continue;
                        }
                        else
                        {
                            click[i] = 0;
                        }
                    }
                    if (click[i] == 2)
                    {
                        osu->InitPath(osu->musicInfo, "C:\\Users\\USER\\Desktop\\Osu!mania\\OsuManiaCocos\\Resources\\Library\\Ghost\\Easy.osu", "C:\\Users\\USER\\Desktop\\Osu!mania\\OsuManiaCocos\\Resources\\Library\\Ghost\\Ghost.mp3", "C:\\Users\\USER\\Desktop\\Osu!mania\\OsuManiaCocos\\Resources\\Library\\Ghost\\Ghost.jpg");
                      
                  

                        CCLOG("%s", osu->musicInfo->FileName);
                        CCLOG("%s", osu->musicInfo->soundFile);
                        CCLOG("%s", osu->musicInfo->WallpaperFile);
                        
                        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
                        osu->OsuInformationReader(osu->musicInfo, osu->musicInfo->FileName);
                        CCLOG("%s", osu->musicInfo->title);


                        Scene* scene2 = HelloWorld::createScene();
                        Director::getInstance()->replaceScene(scene2);

                    }
                    backGround[Ghost]->setOpacity(100);
                    SimpleAudioEngine::getInstance()->playBackgroundMusic("Library/Ghost/Ghost.mp3");
                    break;
                }

                /*case Hitorigoto:
                {
                    currSelect = Hitorigoto;
                    click[i]++;
                    for (int i = 0; i < SONG_NUM; i++)
                    {
                        if (i == currSelect)
                        {
                            continue;
                        }
                        else
                        {
                            click[i] = 0;
                        }
                    }
                    if (click[i] == 2)
                    {
                        wcscpy(musicInfo->FileName, L"C:\\Users\\USER\\Desktop\\Osu!mania\\OsuManiaCocos\\Resources\\Library\\Hitorigoto\\1.osu");
                        wcscpy(musicInfo->soundFile, L"C:\\Users\\USER\\Desktop\\Osu!mania\\OsuManiaCocos\\Resources\\Library\\Hitorigoto\\Hitorigoto.mp3");
                        wcscpy(musicInfo->WallpaperFile, L"C:\\Users\\USER\\Desktop\\Osu!mania\\OsuManiaCocos\\Resources\\Library\\Hitorigoto\\Hitorigoto.png");
                        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
                        osu->OsuInformationReader(musicInfo, musicInfo->FileName);
                    } 
                    SimpleAudioEngine::getInstance()->playBackgroundMusic("Library/Hitorigoto/Hitorigoto.mp3");
                    break;
                }*/

                }
            }
        }  
    }
}

void SelectScene::LevelSelect(Node * node, Sprite* PopUp, Sprite* Wallpaper, Sprite* Start, Sprite ** button,Label* info, int level, std::string _PopupWallpaper)
{

    // 화면 어둡게 
    PopUp->setPosition(osu->Center);
    PopUp->setOpacity(35);
    node->addChild(PopUp);

    // PopUp
    Wallpaper = Sprite::create(_PopupWallpaper);
    Wallpaper->setScale(0.3f);
    Wallpaper->setPosition(osu->Center);
    node->addChild(Wallpaper);
    char text[CHAR_MAX];
    sprintf(text, "SongTitle : %s\nArtist : %s\n", osu->musicInfo->title, osu->musicInfo->artist);
    info = Label::createWithTTF(text, "fonts/Aller_Bd.ttf", 30);


        button[0] = Sprite::create("UI/Left.png");
        button[0]->setPosition(Vec2());
        button[0]->setScale(0.25);
        node->addChild(button[0]);

        button[1] = Sprite::create("UI/Left.png");
        button[1]->setPosition(Vec2());
        button[1]->setScale(0.25);
        node->addChild(button[1]);
    


    
}

void SelectScene::update(float dt)
{
    cursor->setPosition(cursorPos);
}

void SelectScene::SongLibray(Node* node, Sprite* Form[], Sprite** backGround, std::string _backGround, std::string _Form, Vec2 pos, int index)
{
    // Form
    Form[index] = Sprite::create(_backGround);
    Form[index]->setPosition(pos);
    Form[index]->setContentSize(Size(600, 200));
    node->addChild(Form[index]);

    // BackGround
    backGround[index] = Sprite::create(_Form);
    backGround[index]->setPosition(Vec2(WINDOWWIDTH / 2, WINDOWHEIGHT / 2));
    backGround[index]->setOpacity(0);
    node->addChild(backGround[index]);
}


void SelectScene::onKeyPressed(EventKeyboard::KeyCode Keycode, Event* event)
{
    if (Keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        auto scene = HelloWorld::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}


void SelectScene::onKeyReleased(EventKeyboard::KeyCode Keycode, Event* event)
{

}
void SelectScene::menuCloseCallback(Ref* pSender)
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
