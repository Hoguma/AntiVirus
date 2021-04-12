#include "DXUT.h"
#include "cTitle.h"

void cTitle::Init()
{
	RENDER->StopAll();
	RENDER->Play("Intro", {800,450}, true);
	GAME->Score = 0;
	GAME->nLife = 5;
	GAME->Stage = 0;
	menu = 0;
	pos = { 2000, 150 };
	fAlpha = 0;
	isRank = false;
	isCredit = false;
}

void cTitle::Update()
{
	if (pos.x > 801)
	{
		Lerp(&pos, pos, Vec2(800, 150), 5 * Delta);
	}
	else if (fAlpha < 254)
	{
		Lerp(&fAlpha, fAlpha, 255.f, 4 * Delta);
	}
	if (fAlpha > 254)
	{
		if (KeyDown(VK_DOWN) && menu < 5) { 
			menu++; 
			isRank = false; 
			isCredit = false;
			RENDER->Play("Button");
		}
		if (KeyDown(VK_UP) && menu > 0) {
			menu--; 
			isRank = false; 
			isCredit = false;
			RENDER->Play("Button");
		}
	}
	if (KeyDown(VK_SPACE))
	{
		switch (menu)
		{
		case 0:
			break;
		case 1:
			SCENE->ChangeScene("InGame");
			break;
		case 2:
			isRank = true;
			break;
		case 3:
			isCredit = true;
			break;
		case 4:
			exit(0);
			break;
		case 5:
			break;
		default:
			break;
		}
	}
}

void cTitle::Render()
{
	RENDER->Render(RENDER->GetTexture("Title"), Vec2(800,450));
	RENDER->Render(RENDER->GetTexture("Title_name"), pos);
	float size[6];
	for (int i = 0; i < 6; i++) size[i] = 0.8f;
	size[menu] = 1;

	RENDER->Render(RENDER->GetTexture("Start"), Vec2(200, 350), 0, size[1], D3DCOLOR_ARGB((int)fAlpha, 255, 255, 255));
	RENDER->Render(RENDER->GetTexture("Rank"), Vec2(220, 500), 0, size[2], D3DCOLOR_ARGB((int)fAlpha, 255, 255, 255));
	RENDER->Render(RENDER->GetTexture("Credit"), Vec2(240, 650), 0, size[3], D3DCOLOR_ARGB((int)fAlpha, 255, 255, 255));
	RENDER->Render(RENDER->GetTexture("Exit"), Vec2(260, 800), 0, size[4], D3DCOLOR_ARGB((int)fAlpha, 255, 255, 255));

	if (isRank)
	{
		RENDER->Render(RENDER->GetTexture("window1"), Vec2(1000, 550), 0, 2);
		int i = 0;
		for (auto iter : GAME->rank)
		{
			if (i > 280) break;
			RENDER->Render(iter.second, Vec2(750, 380 + i), 60);
			RENDER->Render(to_string(iter.first), Vec2(1050, 380 + i), 60);
			i += 70;
		}

	}
	if (isCredit)
	{
		RENDER->Render(RENDER->GetTexture("Credit_1"), Vec2(1000, 550), 0, 0.8);
	}
}

void cTitle::Release()
{
}
