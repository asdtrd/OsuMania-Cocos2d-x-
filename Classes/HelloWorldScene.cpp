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
int currTick = 0;
int prevTick = 0;
int tick = 0;

#include "HelloWorldScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    //CCVideoManager::Instance();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // video player test

    // action init
    KeyBoardInit();
    InitTitle();
    this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::Timer), 0.01f);
    scheduleUpdate();
    return true;
}

void HelloWorld::Timer(float dt)
{
    time += dt;
}
void HelloWorld::InitTitle()
{
CCLOG("%s", osu->musicInfo->FileName);

    osu->Label_Init(this, osu->musicinfo_Label);
    CCLOG("%s", osu->musicInfo->WallpaperFile);

    osu->Sprite_init(osu->Center,this, osu->Wallpaper, osu->musicInfo->WallpaperFile,1,35);
    osu->Sprite_init(Vec2(osu->Center.x - 250,osu->Center.y),this, osu->Map, "Map/Map.png",1,255);
    osu->KeySprite(this, osu->Key);
    osu->NoteSprite(this, osu->note1copyed, Key1);
    osu->NoteSprite(this, osu->note2copyed, Key2);
    osu->NoteSprite(this, osu->note3copyed, Key3);
    osu->NoteSprite(this, osu->note4copyed, Key4);
    osu->timingcheck(this, 1.0f);
    /*Test.setRect(0, 0, WINDOWWIDTH, 175);
    DrawRectBoundingBox(Test, 3);*/
}


void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{

    if (keycode == EventKeyboard::KeyCode::KEY_D || keycode == EventKeyboard::KeyCode::KEY_F || keycode == EventKeyboard::KeyCode::KEY_J || keycode == EventKeyboard::KeyCode::KEY_K)
    {
   
        osu->keySound = true;
    }
  
    // rect note 전부 검사 
    if (keycode ==EventKeyboard::KeyCode::KEY_D)
    {
        
        osu->onKey1 = true;

        osu->Key[0]->runAction(Show::create());
    }
    if(keycode==EventKeyboard::KeyCode::KEY_F)
    {
        osu->onKey2 = true;

        

        osu->Key[1]->runAction(Show::create());
    }
    if( keycode ==EventKeyboard::KeyCode::KEY_J)
    {
        osu->onKey3 = true;

        osu->Key[2]->runAction(Show::create());

    }
    if( keycode ==EventKeyboard::KeyCode::KEY_K)
    {
        osu->onKey4 = true;

        osu->Key[3]->runAction(Show::create()); 
    }
}
void HelloWorld::DrawRectBoundingBox(Rect A, int Color)
{
    if (boundingBox == nullptr)
    {
        boundingBox = DrawNode::create();
    }
     
        switch (Color)
        {
        case 1: { boundingBox->drawRect(A.origin, A.origin + A.size, Color4F::GREEN); break; }
        case 2: { boundingBox->drawRect(A.origin, A.origin + A.size, Color4F::RED); break; }
        case 3: { boundingBox->drawRect(A.origin, A.origin + A.size, Color4F::BLUE); break; }
        }
        this->addChild(boundingBox, 10);
    
}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    switch (keycode)
    {
    case EventKeyboard::KeyCode::KEY_D:
    {
        osu->onKey1 = false;
        
        osu->KeyReleased = true;
        osu->Key[0]->runAction(Hide::create());
        break;
    }
    case EventKeyboard::KeyCode::KEY_F:
    {
  
        osu->onKey2 = false;

        osu->KeyReleased = true;
        osu->Key[1]->runAction(Hide::create());

    
        break;
    }
    case EventKeyboard::KeyCode::KEY_J:
    {
        osu->onKey3 = false;


        osu->KeyReleased = true;

        osu->Key[2]->runAction(Hide::create());

        break;

    }
    case EventKeyboard::KeyCode::KEY_K:
    {
        osu->onKey4 = false;


        osu->KeyReleased = true;

        osu->Key[3]->runAction(Hide::create());

        break;

    }
    }
}
void HelloWorld::KeyBoardInit()
{
    auto Lis = EventListenerKeyboard::create();
    Lis->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    Lis->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Lis, this);
}

void HelloWorld::NoteCollision(Sprite** notecopyed, bool* onKey, int key)
{
    Vec2 currPos;
    for (int i = 0; i < NOTE_MAX; i++)
    {
        currPos = notecopyed[i]->getPosition();

        // Prefect Note
        if (currPos.y < 250 && currPos.y > 180)
        {
            if (*onKey == true)
            {
                osu->Keypressed1 = true;
                osu->perfectScore++;
                notecopyed[i]->runAction(Hide::create());
                osu->perfect->runAction(Show::create());
                *onKey = false;
                return;
            }
        }
    }   
}


void HelloWorld::ScoreUpdate()
{
    char temp[CHAR_MAX];
    sprintf(temp, "%d", osu->perfectScore);
    if (score_Label == nullptr)
    {
        score_Label = Label::createWithTTF(temp, "fonts/Aller_Bd.ttf", 50);
        score_Label->setPosition(Vec2(osu->timingPos.x, osu->timingPos.y));
        addChild(score_Label);
    }
    else
    {
        if (osu->perfectScore == 0)
        {
            score_Label->setVisible(0);
        }
        else
        {
            score_Label->setVisible(1);
            score_Label->setString(temp);

        }
    }
}

void HelloWorld::BackGroundMusic()
{
    if (osu->isPlaying == false)
    {
        
        
            SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
            SimpleAudioEngine::getInstance()->playBackgroundMusic(osu->musicInfo->soundFile, false);
            osu->musicStartTime = time;
            osu->isPlaying = true;


    }
    if (osu->keySound == true)
    {
        SimpleAudioEngine::getInstance()->setEffectsVolume(0.3f);
        SimpleAudioEngine::getInstance()->playEffect(osu->musicInfo->effectFile,false);
        osu->keySound = false;
    }
}
void HelloWorld::update(float dt)
{
    tick++;
    NoteCollision(osu->note1copyed, &osu->onKey1,1);
    NoteCollision(osu->note2copyed, &osu->onKey2,2);
    NoteCollision(osu->note3copyed, &osu->onKey3,3);
    NoteCollision(osu->note4copyed, &osu->onKey4,4);
    ScoreUpdate();
    BackGroundMusic();
    if (osu->KeyReleased == true)
    {
        osu->perfect->runAction(Hide::create());
        osu->good->runAction(Hide::create());
        osu->miss->runAction(Hide::create());
        osu->KeyReleased = false;
    }

    osu->result = time;
    osu->GameTime = osu->time1;

    if (osu->result > osu->GameTime)
    {

        osu->notespawn = true;

        // osu data init
        osu->OsuNoteReader(osu->musicInfo, osu->musicInfo->FileName, osu->mainNote, &osu->strcount);
        osu->OsuNoteReader(osu->musicInfo, osu->musicInfo->FileName, osu->note2Temp, &osu->strcount);
        osu->OsuNoteReader(osu->musicInfo, osu->musicInfo->FileName, osu->note3Temp, &osu->strcount);
        osu->OsuNoteReader(osu->musicInfo, osu->musicInfo->FileName, osu->note4Temp, &osu->strcount);
        
        // 노트 파싱 뿌리기
        CheckNote();
 
    }
    else
    {
        osu->notespawn = false;
    }
}
void HelloWorld::CheckNote()
{
    int num = 0;
    osu->timing = 0.5f;
    float _timing = osu->timing;

    osu->NoteSpeed = osu->timing + 0.21f;
    // Note
    osu->time1 = (osu->mainNote[2] * 0.001f) + osu->musicStartTime;
    osu->time2 = (osu->note2Temp[2] * 0.001f) + osu->musicStartTime;
    osu->time3 = (osu->note3Temp[2] * 0.001f) + osu->musicStartTime;
    osu->time4 = (osu->note4Temp[2] * 0.001f) + osu->musicStartTime;

    if (osu->time1 - _timing > 0 && osu->time2 - _timing > 0 && osu->time3 - _timing > 0 && osu->time4 - _timing > 0)
    {
        osu->time1 -= _timing;
        osu->time2 -= _timing;
        osu->time3 -= _timing;
        osu->time4 -= _timing; 
    }
  
    if (osu->time1 == osu->time2)
    {
        osu->withnote[num++] = osu->note2Temp[0];

    }
    else
    {
        osu->strcount--;
    }
    if (osu->time1 == osu->time3)
    {
        osu->withnote[num++] = osu->note3Temp[0];

    }
    else
    {
        osu->strcount--;
    }
    if (osu->time1 == osu->time4)
    {
        osu->withnote[num++] = osu->note4Temp[0];

    }
    else
    {
        osu->strcount--;
    }

    num = 0;
   

    // 단일 노트인 경우
    // 초 = ms *0.001;
       if (osu->withnote[0] == '\0')
    {
        switch ((int)osu->mainNote[0])
        {
        case Key1:
        {
            NoteAction(osu->key1pos, osu->moveto1, &osu->note1Index, &osu->m1, osu->note1copyed);
            break;
        }
        case Key2:
        {
            NoteAction(osu->key2pos, osu->moveto2, &osu->note2Index, &osu->m2, osu->note2copyed);
            break;
        }
        case Key3:
        {
            NoteAction(osu->key3pos, osu->moveto3, &osu->note3Index, &osu->m3, osu->note3copyed);
            break;

        }
        case Key4:
        {

            NoteAction(osu->key4pos, osu->moveto4, &osu->note4Index, &osu->m4, osu->note4copyed);
            break;
        }
        }

    }
    // 동시 노트인 경우
    else
    {
        while (osu->withnote[num] != '\0')
        {
            //CCLOG("%d", osu->withnote[num]);
            if (osu->notespawn == true)
            {

                // 기준 노트 실행
                switch ((int)osu->mainNote[0])
                {
                case Key1:
                {
                    NoteAction(osu->key1pos, osu->moveto1, &osu->note1Index, &osu->m1, osu->note1copyed);
                    break;
                }
                case Key2:
                {
                    NoteAction(osu->key2pos, osu->moveto2, &osu->note2Index, &osu->m2, osu->note2copyed);
                    break;
                }
                case Key3:
                {
                    NoteAction(osu->key3pos, osu->moveto3, &osu->note3Index, &osu->m3, osu->note3copyed);
                    break;

                }
                case Key4:
                {
                    NoteAction(osu->key4pos, osu->moveto4, &osu->note4Index, &osu->m4, osu->note4copyed);
                    break;
                }
                }

                // 동시 노트 실행
                if (osu->withnote[num] == Key1)
                {
                    NoteAction(osu->key1pos, osu->moveto1, &osu->note1Index, &osu->m1, osu->note1copyed);
                }
                if (osu->withnote[num] == Key2)
                {

                    NoteAction(osu->key2pos, osu->moveto2, &osu->note2Index, &osu->m2, osu->note2copyed);
                }
                if (osu->withnote[num] == Key3)
                {
                    NoteAction(osu->key3pos, osu->moveto3, &osu->note3Index, &osu->m3, osu->note3copyed);
                }
                if (osu->withnote[num] == Key4)
                {
                    NoteAction(osu->key4pos, osu->moveto4, &osu->note4Index, &osu->m4, osu->note4copyed);
                }

            }
            num++;
        }
        osu->notespawn = false;

        // Reset
        memset(osu->withnote, NULL, sizeof(osu->withnote));
    }
}
void HelloWorld::NoteAction(Vec2 keyPos, MoveTo* moveTo, int *index, int *currNote, Sprite ** note)
{
    moveTo = MoveTo::create(osu->NoteSpeed, Vec2(keyPos.x, osu->noteDel));
    note[*index]->setPosition(keyPos);
    note[*index]->setVisible(1);
    
    note[*index]->runAction(Sequence::create(NoteOpacity::create(0,0, note[*index]),Show::create(),moveTo,
        NoteOpacity::create(0,1,note[*index]),MoveBy::create(0.5f,Vec2(note[*index]->getPosition().x,-30)), // p 1
        MoveTo::create(0,Vec2(WINDOWWIDTH, WINDOWHEIGHT)),Hide::create(), nullptr));
    *index += 1;
    if (*index >= NOTE_MAX)
    {
       *index = 0;
    }
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
