#pragma once
#include"cocos2d.h"
using namespace cocos2d;

class NoteOpacity : public ActionInterval
{
public:
	static NoteOpacity* create(float time, bool opacity, Sprite * target)
	{

		NoteOpacity* _noteOpacity = new NoteOpacity;
		_noteOpacity->initWithDuration(time, opacity, target);
		return _noteOpacity;
	}

	bool initWithDuration(float time, bool opacity, Sprite* target) {
		_opactity = opacity;
		_target = target;
		return ActionInterval::initWithDuration(time);
	}
	virtual void update(float time) override {
		if (_opactity == true)
		{
			_target->setOpacity(0);
		}
		else
		{
			_target->setOpacity(255);
		}
	}

private:
	Sprite* _target;
	bool _opactity;
};
