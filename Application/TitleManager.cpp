#include "TitleManager.h"
#include <math.h>
#include "WinApp.h"

void TitleManager::Initialize(FbxModel* model, FbxModel* model2, ID3D12Device* dev)
{
	arwingObject = new FbxObject3D;
	arwingObject->Initialize();
	arwingObject->SetModel(model);

	foxObject = new FbxObject3D;
	foxObject->Initialize();
	foxObject->SetModel(model2);

#pragma region Sprite
	//スプライト初期化処理
	spriteCommon = sprite->SpriteCommonCreate(dev, 1280, 720);
	sprite->SpriteCommonLoadTexture(spriteCommon, 0, L"Resources/starfoxTitle.png", dev);
	sprite->SpriteCommonLoadTexture(spriteCommon, 1, L"Resources/starfoxTitle.png", dev);
	titleSprite.SpriteCreate(dev, 1280, 720);
	titleSprite.SetTexNumber(0);
	titleSprite.SetPosition(XMFLOAT3(200, 100, 0));
	titleSprite.SetScale(XMFLOAT2(414 * 2.2, 54 * 2.2));

	pressSpace.SpriteCreate(dev, 1280, 720);
	pressSpace.SetTexNumber(1);
	pressSpace.SetPosition(XMFLOAT3(1200, 650, 0));
	pressSpace.SetScale(XMFLOAT2(64, 64));

	nintendoCopyright.SpriteCreate(dev, 1280, 720);
	nintendoCopyright.SetTexNumber(0);
	nintendoCopyright.SetPosition(XMFLOAT3(200, 500, 0));
	nintendoCopyright.SetScale(XMFLOAT2(414 * 2.2, 54 * 2.2));
#pragma endregion
}

void TitleManager::Update()
{

}
void TitleManager::Draw(ID3D12GraphicsCommandList* cmdList,ID3D12Device* dev)
{
	titleSprite.SpriteTransferVertexBuffer(titleSprite);
	titleSprite.SpriteUpdate(titleSprite, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	titleSprite.SpriteDraw(cmdList, spriteCommon, dev, titleSprite.vbView);

	nintendoCopyright.SpriteTransferVertexBuffer(nintendoCopyright);
	nintendoCopyright.SpriteUpdate(nintendoCopyright, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	nintendoCopyright.SpriteDraw(cmdList, spriteCommon, dev, nintendoCopyright.vbView);
}
void TitleManager::ModelDraw()
{

}
void TitleManager::BackDraw()
{
	
}

void TitleManager::TitleFrontDraw()
{

}
void TitleManager::WinDraw()
{

}
void TitleManager::FrontDraw()
{
	
}