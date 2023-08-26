#pragma once
#include "GameNode.h"
class Title : public GameNode
{
private:
	HWND _hWndVideo;
	bool _nextScene;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();
};

