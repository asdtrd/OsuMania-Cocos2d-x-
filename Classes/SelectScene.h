#ifndef __SELECT_SCENE_H__
#define __SELECT_SCENE_H__
#define SONG_NUM 1

#include "GameResource.h"

class SelectScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    Osu* osu = ClassPtr::GetOsu();
    Sprite** songForm = new Sprite * [SONG_NUM];
    Sprite** backGround = new Sprite * [SONG_NUM];
    Sprite* Black;
    Sprite* cursor;
    void onMouseMove(Event* event);
    void onMouseDown(Event* event);
    Vec2 cursorPos;
    MusicInfo* musicInfoPtr = new MusicInfo;
    int currSelect = 0;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // Key
    void onKeyPressed(EventKeyboard::KeyCode Keycode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode Keycode, Event* event);
    
    // Song
    void SongLibray(Node* node, Sprite* Form[], Sprite** backGround, std::string _backGround, std::string _Form, Vec2 pos, int index);

    void update(float dt);
    void InitSongs();

    void LevelSelect(Node* node, Sprite* PopUp, Sprite* Wallpaper, Sprite* Start, Sprite** button, Label* info, int level, std::string _PopupWallpaper);





    // 
    int click[SONG_NUM] = { 0, };


    // implement the "static create()" method manually
    CREATE_FUNC(SelectScene);


};

#endif // __NEW_SCENE_H__
