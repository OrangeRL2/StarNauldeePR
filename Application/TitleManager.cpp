#include "TitleManager.h"
#include <math.h>
#include "WinApp.h"
#pragma warning(disable:4828)

ID3D12Device* TitleManager::device = nullptr;
Camera* TitleManager::camera = nullptr;
Input* TitleManager::input = nullptr;
DXInput* TitleManager::dxInput = nullptr;
void TitleManager::Initialize(FbxModel* model, FbxModel* model2, ID3D12Device* dev)
{
	ModelDraw(dev);
	TransitionPop(dev);
	arwingObject = new FbxObject3D;
	arwingObject->Initialize();
	arwingObject->SetModel(model);

	foxObject = new FbxObject3D;
	foxObject->Initialize();
	foxObject->SetModel(model2);

#pragma region Sprite
	spriteCommon = sprite->SpriteCommonCreate(dev, 1280, 720);
	sprite->SpriteCommonLoadTexture(spriteCommon, 0, L"Resources/titleScreen/pastelblue.png", dev);
	sprite->SpriteCommonLoadTexture(spriteCommon, 1, L"Resources/titleScreen/whiteLine.png", dev);

	sprite->SpriteCommonLoadTexture(spriteCommon, 2, L"Resources/titleScreen/S.png", dev);
	sprite->SpriteCommonLoadTexture(spriteCommon, 3, L"Resources/titleScreen/T.png", dev);
	sprite->SpriteCommonLoadTexture(spriteCommon, 4, L"Resources/titleScreen/A.png", dev);
	sprite->SpriteCommonLoadTexture(spriteCommon, 5, L"Resources/titleScreen/R.png", dev);
	sprite->SpriteCommonLoadTexture(spriteCommon, 6, L"Resources/titleScreen/T2.png", dev);

	sprite->SpriteCommonLoadTexture(spriteCommon, 7, L"Resources/titleScreen/handle2.png", dev);
	sprite->SpriteCommonLoadTexture(spriteCommon, 8, L"Resources/titleScreen/titleImage2.png", dev);
	sprite->SpriteCommonLoadTexture(spriteCommon, 9, L"Resources/titleScreen/pastelblue3.png", dev);
	sprite->SpriteCommonLoadTexture(spriteCommon, 10, L"Resources/titleScreen/Controls.png", dev);
	sprite->SpriteCommonLoadTexture(spriteCommon, 11, L"Resources/titleScreen/LEVEL1.png", dev);
	sprite->SpriteCommonLoadTexture(spriteCommon, 12, L"Resources/titleScreen/Start.png", dev);


	titleSprite.SpriteCreate(dev, 1280, 720);
	titleSprite.SetTexNumber(0);
	titleSprite.SetPosition(XMFLOAT3(0, 0, 0));
	titleSprite.SetScale(XMFLOAT2(1280, 730));

	titleSprite2.SpriteCreate(dev, 1280, 720);
	titleSprite2.SetTexNumber(0);
	titleSprite2.SetPosition(XMFLOAT3(0, 0, 0));
	titleSprite2.SetScale(XMFLOAT2(1280, 720));

	pressSpace.SpriteCreate(dev, 1280, 720);
	pressSpace.SetTexNumber(1);
	pressSpace.SetPosition(XMFLOAT3(1200, 650, 0));
	pressSpace.SetScale(XMFLOAT2(64, 64));

	static int time[4] = { 150,100,50,0 };
	static int timespd[4] = { 1,1,1,1 };
	S.SpriteCreate(dev, 1280, 720);
	S.SetTexNumber(2);
	S.SetPosition(XMFLOAT3(600 - 20,
		602 - 40 + cosf(MathFunc::DegreeConversionRad(time[0])) * 10.0f, 0));
	S.SetScale(XMFLOAT2(120.0f * 1.3f, 120.0f * 1.3f));

	T.SpriteCreate(dev, 1280, 720);
	T.SetTexNumber(3);
	T.SetPosition(XMFLOAT3(600 - 20, 602 - 40 + cosf(MathFunc::DegreeConversionRad(time[0])) * 10.0f, 0));
	T.SetScale(XMFLOAT2(120.0f * 1.3f, 120.0f * 1.3f));

	A.SpriteCreate(dev, 1280, 720);
	A.SetTexNumber(4);
	A.SetPosition(XMFLOAT3(600 - 20, 602 - 40 + cosf(MathFunc::DegreeConversionRad(time[0])) * 10.0f, 0));
	A.SetScale(XMFLOAT2(120.0f * 1.3f, 120.0f * 1.3f));

	R.SpriteCreate(dev, 1280, 720);
	R.SetTexNumber(5);
	R.SetPosition(XMFLOAT3(600 - 20, 602 - 40 + cosf(MathFunc::DegreeConversionRad(time[0])) * 10.0f, 0));
	R.SetScale(XMFLOAT2(120.0f * 1.3f, 120.0f * 1.3f));

	T2.SpriteCreate(dev, 1280, 720);
	T2.SetTexNumber(6);
	T2.SetPosition(XMFLOAT3(600 - 20, 602 - 40 + cosf(MathFunc::DegreeConversionRad(time[0])) * 10.0f, 0));
	T2.SetScale(XMFLOAT2(120.0f * 1.3f, 120.0f * 1.3f));

	handle.SpriteCreate(dev, 1280, 720);
	handle.SetTexNumber(7);
	handle.SetPosition(XMFLOAT3(0, 0, 0));
	handle.SetScale({ 200 * 1.3f, 200 * 1.3f });

	titleImage.SpriteCreate(dev, 1280, 720);
	titleImage.SetTexNumber(8);
	titleImage.SetPosition(XMFLOAT3(0, 0, 0));
	titleImage.SetScale({ 300 * 1.3f, 300 * 1.3f });

	controlImage.SpriteCreate(dev, 1280, 720);
	controlImage.SetTexNumber(10);
	controlImage.SetPosition(XMFLOAT3(900, 400, 0));
	controlImage.SetScale({ 300 * 1.3f, 300 * 1.3f });

	level1.SpriteCreate(dev, 720, 720);
	level1.SetTexNumber(11);
	level1.SetPosition(XMFLOAT3(0, 0, 0));
	level1.SetScale(XMFLOAT2(720, 720));

	start.SpriteCreate(dev, 720, 720);
	start.SetTexNumber(12);
	start.SetPosition(XMFLOAT3(0, 0, 0));
	start.SetScale(XMFLOAT2(720, 720));

#pragma endregion
}

void TitleManager::Update(FbxModel* model, FbxModel* model2, ID3D12Device* dev)
{
	for (std::unique_ptr<SpritePop>& enemy : poppy)
	{
		enemy->PopUpdate();
	}
	for (std::unique_ptr<SpritePop>& enemy2 : transPop)
	{
		enemy2->revival();
	}
	static int time[4] = { 150,100,50,0 };
	static int timespd[4] = { 1,1,1,1 };
	for (int i = 0; i < 4; i++)
	{
		time[i] += timespd[i];
		if (time[i] >= 360 || time[i] <= 0)
		{
			timespd[i] = -timespd[i];
		}
	}

	switch (phase2_) {
	case Phase2::Approach:
	default://移動（ベクトルを加算）
		turning -= 0.01f;

		//規定の位置に到達したら離脱
		if (turning < -1.0f) {
			phase2_ = Phase2::Leave;
		}
		break;
	case Phase2::Leave://移動（ベクトルを加算）

		turning += 0.01f;
		if (turning > 1.0f) {
			phase2_ = Phase2::Approach;
		}
		break;
	}

	if (position.y >= 0) {
		position.y -= 10.0f;
	}

	titleSprite.SetPosition(position);
	S.SetPosition(XMFLOAT3(600 - 20, 602 - 40 + cosf(MathFunc::DegreeConversionRad(time[0])) * 10.0f + position.y, 0));
	T.SetPosition(XMFLOAT3(600 - 20, 602 - 40 + cosf(MathFunc::DegreeConversionRad(time[0])) * 10.0f + position.y, 0));
	A.SetPosition(XMFLOAT3(600 - 20, 602 - 40 + cosf(MathFunc::DegreeConversionRad(time[0])) * 10.0f + position.y, 0));
	R.SetPosition(XMFLOAT3(600 - 20, 602 - 40 + cosf(MathFunc::DegreeConversionRad(time[0])) * 10.0f + position.y, 0));
	T2.SetPosition(XMFLOAT3(600 - 20, 602 - 40 + cosf(MathFunc::DegreeConversionRad(time[0])) * 10.0f + position.y, 0));

	handle.SetPosition(XMFLOAT3(40, 30 + cosf(MathFunc::DegreeConversionRad(time[0])) * 15.0f + position.y, 0));
	titleImage.SetPosition(XMFLOAT3(40, -20 + cosf(MathFunc::DegreeConversionRad(time[0])) * 15.0f + position.y, 0));

	S.SetRotation(turning * 3);
	T.SetRotation(turning - 0.0003f * 1.5f);
	A.SetRotation(turning * 5);
	R.SetRotation(turning * 2.5f);
	T2.SetRotation(turning * 4);

	handle.SetRotation({ 5.4f - turning * 3 });
	titleImage.SetRotation({ 2.4f - turning * 3 });

	//titleSprite2.SetPosition(XMFLOAT3(0 + cosf(MathFunc::DegreeConversionRad(time[0])) * 850.0f,-20 + cosf(MathFunc::DegreeConversionRad(time[0])) * 3.0f,0.0f));
	//titleSprite2.SetRotation({ turning-2.0f * 15.0f });

	rotation.y = horizontalRotation + 3.1;
	rotation.x += verticalRotation + 0.002f;
	rotation.z += verticalRotation + 0.002f;

	titleSprite2.SetPosition(position);
	arwingObject->SetPosition(position);
	arwingObject->SetRotation(rotation);
	arwingObject->SetScale(scale);
	arwingObject->Update();

	/*poppy.remove_if([](std::unique_ptr<SpritePop>& enemy) {
		return enemy->IsDead();
		});*/
	/*transPop.remove_if([](std::unique_ptr<SpritePop>& enemy) {
		return enemy->IsDead();
		});*/
}
void TitleManager::Draw(ID3D12GraphicsCommandList* cmdList, ID3D12Device* dev)
{
	arwingObject->Draw(cmdList);

	titleSprite.SpriteTransferVertexBuffer(titleSprite);
	titleSprite.SpriteUpdate(titleSprite, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	titleSprite.SpriteDraw(cmdList, spriteCommon, dev, titleSprite.vbView);

	for (std::unique_ptr<SpritePop>& enemy : poppy)
	{
		enemy->PopDraw(cmdList, dev);
	}

	handle.SpriteTransferVertexBuffer(handle);
	handle.SpriteUpdate(handle, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	handle.SpriteDraw(cmdList, spriteCommon, dev, handle.vbView);

	titleImage.SpriteTransferVertexBuffer(titleImage);
	titleImage.SpriteUpdate(titleImage, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	titleImage.SpriteDraw(cmdList, spriteCommon, dev, titleImage.vbView);

	S.SpriteTransferVertexBuffer(S);
	S.SpriteUpdate(S, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	S.SpriteDraw(cmdList, spriteCommon, dev, S.vbView);

	T.SpriteTransferVertexBuffer(T);
	T.SpriteUpdate(T, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	T.SpriteDraw(cmdList, spriteCommon, dev, T.vbView);

	A.SpriteTransferVertexBuffer(A);
	A.SpriteUpdate(A, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	A.SpriteDraw(cmdList, spriteCommon, dev, A.vbView);

	R.SpriteTransferVertexBuffer(R);
	R.SpriteUpdate(R, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	R.SpriteDraw(cmdList, spriteCommon, dev, R.vbView);

	T2.SpriteTransferVertexBuffer(T2);
	T2.SpriteUpdate(T2, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	T2.SpriteDraw(cmdList, spriteCommon, dev, T2.vbView);

	arwingObject->Draw(cmdList);


	controlImage.SpriteTransferVertexBuffer(controlImage);
	controlImage.SpriteUpdate(controlImage, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	controlImage.SpriteDraw(cmdList, spriteCommon, dev, controlImage.vbView);
}
void TitleManager::GameDraw(ID3D12GraphicsCommandList* cmdList, ID3D12Device* dev)
{
	titleSprite2.SpriteTransferVertexBuffer(titleSprite2);
	titleSprite2.SpriteUpdate(titleSprite2, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	titleSprite2.SpriteDraw(cmdList, spriteCommon, dev, titleSprite2.vbView);

	for (std::unique_ptr<SpritePop>& enemy : poppy)
	{
		if (enemy->IsDead() == false) {
		enemy->PopDraw(cmdList, dev);
		}
	}
	for (std::unique_ptr<SpritePop>& enemy2 : transPop)
	{
		if (enemy2->IsDead() == false) {
		enemy2->PopDraw(cmdList, dev);
	}
	}
	handle.SpriteTransferVertexBuffer(handle);
	handle.SpriteUpdate(handle, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	handle.SpriteDraw(cmdList, spriteCommon, dev, handle.vbView);

	titleImage.SpriteTransferVertexBuffer(titleImage);
	titleImage.SpriteUpdate(titleImage, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	titleImage.SpriteDraw(cmdList, spriteCommon, dev, titleImage.vbView);

	S.SpriteTransferVertexBuffer(S);
	S.SpriteUpdate(S, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	S.SpriteDraw(cmdList, spriteCommon, dev, S.vbView);

	T.SpriteTransferVertexBuffer(T);
	T.SpriteUpdate(T, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	T.SpriteDraw(cmdList, spriteCommon, dev, T.vbView);

	A.SpriteTransferVertexBuffer(A);
	A.SpriteUpdate(A, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	A.SpriteDraw(cmdList, spriteCommon, dev, A.vbView);

	R.SpriteTransferVertexBuffer(R);
	R.SpriteUpdate(R, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	R.SpriteDraw(cmdList, spriteCommon, dev, R.vbView);

	T2.SpriteTransferVertexBuffer(T2);
	T2.SpriteUpdate(T2, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	T2.SpriteDraw(cmdList, spriteCommon, dev, T2.vbView);

	level1.SpriteTransferVertexBuffer(level1);
	level1.SpriteUpdate(level1, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	level1.SpriteDraw(cmdList, spriteCommon, dev, level1.vbView);

	start.SpriteTransferVertexBuffer(start);
	start.SpriteUpdate(start, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	start.SpriteDraw(cmdList, spriteCommon, dev, start.vbView);
}

void TitleManager::Transition(ID3D12Device* dev)
{ 
	static int time[4] = { 150,100,50,0 };
	static int timespd[4] = { 1,1,1,1 };
	for (int i = 0; i < 4; i++)
	{
		time[i] += timespd[i];
		if (time[i] >= 360 || time[i] <= 0)
		{
			timespd[i] = -timespd[i];
		}
	}

	if (position.y <= 1000) {
		position.y += 10.5f;
	}
	/*if (position.y >= 500) {
		position.y += 10.5f;
	}*/
	//position.y = cosf(MathFunc::DegreeConversionRad(time[0])) * 1.5f;
	/*if (position.x > 1400.0f) {
		position.x = -1205.0f;
	}*/
	titleSprite2.SetPosition(position);

	position0.y -= 2.5f;
	position1.y -= 10.5f;
	S.SetPosition(XMFLOAT3(600 - 20 - position0.x, 602 - 40 + cosf(MathFunc::DegreeConversionRad(time[0])) * 10.0f - position0.y, 0));
	T.SetPosition(XMFLOAT3(600 - 20 - position0.x, 602 - 40 + cosf(MathFunc::DegreeConversionRad(time[0])) * 10.0f - position0.y, 0));
	A.SetPosition(XMFLOAT3(600 - 20 - position0.x, 602 - 40 + cosf(MathFunc::DegreeConversionRad(time[0])) * 10.0f - position0.y, 0));
	R.SetPosition(XMFLOAT3(600 - 20 - position0.x, 602 - 40 + cosf(MathFunc::DegreeConversionRad(time[0])) * 10.0f - position0.y, 0));
	T2.SetPosition(XMFLOAT3(600 - 20 - position0.x, 602 - 40 + cosf(MathFunc::DegreeConversionRad(time[0])) * 10.0f - position0.y, 0));

	handle.SetPosition(XMFLOAT3(40 - position1.x, 30 + cosf(MathFunc::DegreeConversionRad(time[0])) * 15.0f + position.y, 0));
	titleImage.SetPosition(XMFLOAT3(40 - position1.x, -20 + cosf(MathFunc::DegreeConversionRad(time[0])) * 15.0f + position.y, 0));

	S.SetRotation(turning * 3);
	T.SetRotation(turning - 0.0003f * 1.5f);
	A.SetRotation(turning * 5);
	R.SetRotation(turning * 2.5f);
	T2.SetRotation(turning * 4);

	handle.SetRotation({ 5.4f - turning * 3 });
	titleImage.SetRotation({ 2.4f - turning * 3 });

	if (startPos.y <= 0) {
		startPos.y += 10.0f;
	}
	if (startPos.y >= 0) {
		startPos.y += 3.0f;
	}
	if (startPos.y >= 200) {
		startPos.y += 15.0f;
	}
	if (startPos.y >= 1000) {
		gameStartFlag = true;
	}
	if (levelPos.y <= 0) {
		levelPos.y += 10.0f;
	}
	if (levelPos.y >= 0) {
		levelPos.y += 3.0f;
	}
	if (levelPos.y >= 200) {
		levelPos.y += 15.0f;
	}
	
	start.SetPosition(XMFLOAT3(startPos));
	level1.SetPosition(XMFLOAT3(levelPos));

	for (std::unique_ptr<SpritePop>& enemy2 : transPop)
	{
		enemy2->PopTransition();
	}

	for (std::unique_ptr<SpritePop>& enemy : poppy)
	{
		enemy->PopCollision();
	}

	/*poppy.remove_if([](std::unique_ptr<SpritePop>& enemy) {
		return enemy->IsDead();
		});*/
	/*transPop.remove_if([](std::unique_ptr<SpritePop>& enemy) {
		return enemy->IsDead();
		});*/
}

void TitleManager::ModelDraw(ID3D12Device* dev)
{
	for(int i = 0; i < 50; i++) {
		PopInit(dev);
	}
}
void TitleManager::PopInit(ID3D12Device* dev)
{
	std::unique_ptr<SpritePop> newEnemy = std::make_unique<SpritePop>();
	//rotation += RNG(-0.04, 0.04);
	newEnemy->PopInit(dev);

	//敵を登録する
	poppy.push_back(std::move(newEnemy));
}

void TitleManager::PopTransInit(ID3D12Device* dev)
{
	std::unique_ptr<SpritePop> newEnemy2 = std::make_unique<SpritePop>();
	//rotation += RNG(-0.04, 0.04);
	newEnemy2->PopTransInit(dev);

	//敵を登録する
	transPop.push_back(std::move(newEnemy2));
}

void TitleManager::TransitionPop(ID3D12Device* dev)
{
	for(int i = 0; i <= 200; i++) {
		PopTransInit(dev);
	}
}
void TitleManager::TransitionReset()
{
		gameStartFlag = false;
		startPos = { 200.0f,-2600.0f + 500.0f,0.0f };
		levelPos = { 200.0f,-2000.0f + 500.0f,0.0f };
}