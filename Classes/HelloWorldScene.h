/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#define WINDOWWIDTH 1920
#define WINDOWHEIGHT 1080
#include "GameResource.h"
#include "cocos/editor-support/cocostudio/SimpleAudioEngine.h"
using namespace ClassPtr;
class HelloWorld : public cocos2d::Scene
{
public:
    Osu* osu = GetOsu();
    static cocos2d::Scene* createScene();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void InitTitle();
    void update(float dt);
    virtual bool init();
    void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
    void KeyBoardInit();
    void Timer(float dt);
    void CheckNote();
    void DrawRectBoundingBox(Rect A, int Color);
    void ScoreUpdate();
    void BackGroundMusic();
    void NoteCollision(Sprite** notecopyed, bool* onKey, int key);

    // note Action
    void NoteAction(Vec2 keyPos, MoveTo* moveTo, int* index, int* currNote, Sprite** note);

    // Sprite
    Sprite* test;

    // Label 
    Label* score_Label;
    Rect Test;
   
    // collision
    float time;
    DrawNode* boundingBox;
    DrawNode* perfectdraw;
    

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
