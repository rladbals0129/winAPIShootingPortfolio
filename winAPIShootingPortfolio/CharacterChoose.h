#pragma once
#include "GameNode.h"
class CharacterChoose : public GameNode
{
private:

	GImage* _image;
	bool _goNextScene;
	int _curIdx;

public :
	HRESULT init();
	void release();
	void update();
	void render();

	inline bool getNextScene() { return _goNextScene; }
};

