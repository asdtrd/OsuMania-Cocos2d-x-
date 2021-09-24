#pragma once
#include "GameResource.h"
#define WINDOWWIDTH 1920
#define WINDOWHEIGHT 1080
using namespace ClassPtr;

void Osu::OsuInformationReader(MusicInfo* musicInfo, char filename[])
{
    FILE* fp;
    char str[CHAR_MAX];
    char ans[CHAR_MAX] = "Title";
    char* ptr = str;

    fp = fopen(filename, "r");


    while (!(feof(fp)))
    {
        fgets(str, 100, fp);
        if (strstr(str, ans))
        {
            ptr = strtok(str, ":");
            ptr = strtok(NULL, "");
            strcpy(musicInfo->title, ptr);
            break;
        }
    }

    strcpy(ans, "TitleUnicode");
    while (!(feof(fp)))
    {
        fgets(str, 100, fp);
        if (strstr(str, ans))
        {
            ptr = strtok(str, ":");
            ptr = strtok(NULL, "");
            strcpy(musicInfo->unicode, ptr);
            break;
        }
    }

    strcpy(ans, "Artist");
    while (!(feof(fp)))
    {
        fgets(str, 100, fp);
        if (strstr(str, ans))
        {
            ptr = strtok(str, ":");
            ptr = strtok(NULL, "");
            strcpy(musicInfo->artist, ptr);
            break;
        }
    }
    fclose(fp);
}

void Osu::OsuNoteReader(MusicInfo* musicInfo, char filename[], float currData[], int* strcount)
{
    FILE* test;
    test = fopen("test.txt", "wt");
    FILE* fp;
    int index = 0;
    char str[CHAR_MAX];
    char* ptr = str;
    bool join = false;
    char ans[CHAR_MAX] = "[HitObjects]";
    fp = fopen(filename, "r");

    while (!(feof(fp)))
    {

        fgets(str, 100, fp);

        if (join == true)
        {
            for (int i = 0; i < *strcount; i++)
            {
                fgets(str, 100, fp);
            }
            // Data Init
            ptr = strtok(str, ",");
            currData[KeyX] = atoi(ptr);

            ptr = strtok(NULL, ",");
            currData[KeyY] = atoi(ptr);

            ptr = strtok(NULL, ",");
            currData[Time] = atoi(ptr);

            *strcount += 1;

            //// 64,192,614,5,0,0:0:0:70:G#6_ssl.wav
            fclose(test);
            fclose(fp);
            return;
        }

        if (strstr(str, ans))
        {
            join = true;
            ptr = strtok(str, ",");
            ptr = strtok(NULL, "");

        }
    }
    return;
}
void Osu::autoposinit()
{

    key1pos = Vec2(x, WINDOWHEIGHT);
    key2pos = Vec2(x + target, WINDOWHEIGHT);
    key3pos = Vec2(x + target * 2, WINDOWHEIGHT);
    key4pos = Vec2(x + target * 3, WINDOWHEIGHT);
    timingPos = Vec2(700, Center.y + 100);

}

void Osu::NoteSprite(Node* node, Sprite** note, int key, float scale)
{
    Sprite* t1 = Sprite::create("Note/Note1.png");
    Sprite* t2 = Sprite::create("Note/Note2.png");
    Texture2D* texture1 = t1->getTexture();
    Texture2D* texture2 = t2->getTexture();
    autoposinit();
    switch (key)
    {
    case Key1:
    {
        for (int i = 0; i < NOTE_MAX; i++)
        {
            note[i] = Sprite::createWithTexture(texture1);
            note[i]->setVisible(0);
            note[i]->setScale(scale);
            note[i]->setPosition(key1pos);
            node->addChild(note[i]);
        }
        break;
    }
    case Key2:
    {
        for (int i = 0; i < NOTE_MAX; i++)
        {
            note[i] = Sprite::createWithTexture(texture2);
            note[i]->setVisible(0);
            note[i]->setScale(scale);
            note[i]->setPosition(key2pos);

            node->addChild(note[i]);
        }
        break;

    }
    case Key3:
    {
        for (int i = 0; i < NOTE_MAX; i++)
        {
            note[i] = Sprite::createWithTexture(texture2);
            note[i]->setVisible(0);
            note[i]->setScale(scale);
            note[i]->setPosition(key3pos);

            node->addChild(note[i]);
        }
        break;

    }
    case Key4:
    {
        for (int i = 0; i < NOTE_MAX; i++)
        {
            note[i] = Sprite::createWithTexture(texture1);
            note[i]->setVisible(0);
            note[i]->setScale(scale);
            note[i]->setPosition(key4pos);
            node->addChild(note[i]);
        }
        break;

    }
    }
}

void Osu::Label_Init(Node* node, Label* _label)
{

    OsuInformationReader(musicInfo, musicInfo->FileName);
    char temp[CHAR_MAX];
    sprintf(temp, "SongTitle : %s\nArtist : %s\n", musicInfo->title, musicInfo->artist);
    _label = Label::createWithTTF(temp, "fonts/Aller_Bd.ttf", 30);
    _label->setPosition(Vec2(WINDOWWIDTH - 500, WINDOWHEIGHT - (WINDOWHEIGHT / 2)));
    node->addChild(_label);
}


void Osu::Sprite_init(Vec2 pos,Node* node, Sprite* wallpaper, std::string WallpaperFile, float scale, int opacity)
{
    wallpaper = Sprite::create(WallpaperFile);
    wallpaper->setPosition(pos);
    wallpaper->setOpacity(opacity);
    wallpaper->setScale(scale);
    node->addChild(wallpaper);
}

void Osu::KeySprite(Node * node, Sprite ** Key)
{
    for (int i = 0; i < 4; i++)
    {
        switch (i)
        {
        case 0:
        {
            Key[i] = Sprite::create("HitEffect/Y.png");
            break;
        }
        case 1:
        {
            Key[i] = Sprite::create("HitEffect/R.png");
            break;
        }
        case 2:
        {
            Key[i] = Sprite::create("HitEffect/G.png");
            break;
        }
        case 3:
        {
            Key[i] = Sprite::create("HitEffect/B.png");
            break;
        }
        }  
        Key[i]->setVisible(0);
        Key[i]->setScale(1.5f);
        node->addChild(Key[i]);
    }
  
    int y = 120;
    
    Key[0]->setPosition(Vec2(x, y));
    Key[1]->setPosition(Vec2(x+target, y));
    Key[2]->setPosition(Vec2(x+target*2, y));
    Key[3]->setPosition(Vec2(x+target*3, y));
}


void Osu::timingcheck(Node* node, float scale)
{
    Vec2 _Pos = Vec2(timingPos.x, timingPos.y - 100);

    perfect = Sprite::create("Judgment/Perfect.png");
    perfect->setPosition(_Pos);
    perfect->setVisible(0);
    perfect->setScale(scale);
    

    good = Sprite::create("Judgment/Good.png");
    good->setPosition(_Pos);
    good->setVisible(0);
    good->setScale(scale);

    miss = Sprite::create("Judgment/Miss.png");
    miss->setPosition(_Pos);
    miss->setVisible(0);
    miss->setScale(scale);

    node->addChild(perfect);
    node->addChild(good);
    node->addChild(miss);
}




void Osu::InitPath(MusicInfo* ptr, char * path1, char * path2, char * path3)
{

    sprintf(ptr->FileName, path1);
    sprintf(ptr->soundFile, path2);
    sprintf(ptr->WallpaperFile, path3);
}   


namespace ClassPtr
{
    Osu* osu = new Osu;
    Osu* GetOsu() {
        return osu;
    }
}