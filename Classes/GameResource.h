#pragma once
#include "CustomAction.h"
#define WINDOWWIDTH 1920
#define WINDOWHEIGHT 1080
#define NOTE_MAX 100
#include "cocos/editor-support/cocostudio/SimpleAudioEngine.h"
using namespace CocosDenshion; 
using namespace cocos2d;

class MusicInfo
{
public:
    char title[CHAR_MAX];
    char unicode[CHAR_MAX];
    char artist[CHAR_MAX];
    char soundFile[CHAR_MAX];
    char effectFile[CHAR_MAX] = "C:\\Users\\USER\\Desktop\\Osu!mania\\OsuManiaCocos\\Resources\\Library\\effect.mp3";
    char WallpaperFile[CHAR_MAX];
    char* FileName = new char[CHAR_MAX];
};

class Osu
{
public:
    MusicInfo* musicInfo = new MusicInfo;
    Vec2 Center = Vec2(WINDOWWIDTH / 2, WINDOWHEIGHT / 2);
    Vec2 key1pos, key2pos, key3pos, key4pos, timingPos;
    Label* musicinfo_Label;
    Label* score_Label;
    Sprite* Wallpaper;
    Sprite* Map;
    Sprite** Key = new Sprite * [4];
    Sprite** Note = new Sprite*[4];
    
    // Note Copyed
    Sprite** note1copyed = new Sprite*[NOTE_MAX];
    Sprite** note2copyed = new Sprite*[NOTE_MAX];
    Sprite** note3copyed = new Sprite*[NOTE_MAX];
    Sprite** note4copyed = new Sprite*[NOTE_MAX];

    // timing
    Sprite* perfect;
    Sprite* good;
    Sprite* miss;

    // action
    MoveTo* moveto1;
    MoveTo* moveto2;
    MoveTo* moveto3;
    MoveTo* moveto4;

    // onkey
    bool onKey1 = false;
    bool onKey2 = false;
    bool onKey3 = false;
    bool onKey4 = false;

    // Keyboard Event
    bool Keypressed1 = false;
    bool Keypressed2 = false;
    bool KeyReleased = true;
  
    // Pos
    int x = Center.x - 406;
    int target = 90;

    // index
    int note1Index = 0;
    int note2Index = 0;
    int note3Index = 0;
    int note4Index = 0;

    // 현재 노트를 찾기 위한 경로 탐색용 변수
    int m1 = 0, m2 = 0, m3 = 0, m4 = 0;

    // Osu Data Save
    int strcount = 0;
    float noteinfo[10] = { 0, };
    float mainNote[10] = { 0, };
    float note2Temp[10] = { 0, };
    float note3Temp[10] = { 0, };
    float note4Temp[10] = { 0, };

    int withnote[10] = { 0, };

    // timer
    float time1 = 0, time2 = 0, time3 = 0, time4 = 0, GameTime = 0, result = 0;
    bool notespawn = false;

    // Score
    int perfectScore = 0;
    int missScore = 0;

    //  Sound 관리
    bool isPlaying = false;
    bool keySound = false;
    
    // Note 관리
    float NoteSpeed = 0;
    int noteDel = 200;
    int prevNoteIndex = 0;

    // time
    float timing = 1.0f;
    int tick = 0;
    float musicStartTime = 0;
 
    void OsuInformationReader(MusicInfo* musicInfo, char filename[]);


    void OsuNoteReader(MusicInfo* musicInfo, char filename[], float currData[], int* strcount);

    void Label_Init(Node* node, Label* _label);
    void Sprite_init(Vec2 pos, Node* node, Sprite* wallpaper, std::string WallpaperFile, float scale, int opacity);
    void KeySprite(Node* node, Sprite** key);
    void NoteSprite(Node* node, Sprite** note, int key, float scale = 0.38f);
    void timingcheck(Node* node, float scale);
    void autoposinit();
    void InitPath(MusicInfo* ptr, char* path1, char* path2, char* path3);
};

enum // File
{
    KeyX,
    KeyY,
    Time
};

enum // KeyPosition
{
    Key1 = 64,
    Key2 = 192,
    Key3 = 320,
    Key4 = 448,
};

namespace ClassPtr {
    Osu* GetOsu();
}