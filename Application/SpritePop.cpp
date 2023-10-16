#include "SpritePop.h"

void SpritePop::PopTransInit(ID3D12Device* dev)
{
	scale = { 200.0f,200.0f };
	spriteCommon = sprite->SpriteCommonCreate(dev, 1280, 720);
	sprite->SpriteCommonLoadTexture(spriteCommon, 0, L"Resources/titleScreen/star.png", dev);

	star.SpriteCreate(dev, 1280, 720);
	star.SetTexNumber(0);
	star.SetPosition(XMFLOAT3(1200, MathFunc::RNG(-200, 200), 0));
	star.SetScale(XMFLOAT2(64, 64));

	position.y += MathFunc::RNG(-700, 720);
	position.x += MathFunc::RNG(-700, 1280);
}
void SpritePop::PopInit(ID3D12Device* dev)
{
	scale = { 64.0f,64.0f };
	spriteCommon = sprite->SpriteCommonCreate(dev, 1280, 720);
	sprite->SpriteCommonLoadTexture(spriteCommon, 0, L"Resources/titleScreen/star.png", dev);

	star.SpriteCreate(dev, 1280, 720);
	star.SetTexNumber(0);
	star.SetPosition(XMFLOAT3(1200, MathFunc::RNG(-200, 200), 0));
	star.SetScale(XMFLOAT2(64, 64));

	position.y += MathFunc::RNG(0, 720);
	position.x += MathFunc::RNG(0, 1280);
}
void SpritePop::PopUpdate()
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

	if (scale.x <= 64.0f) {
		scale.x += 1.0f;
		scale.y += 1.0f;
	}

	position.y += 0.5f;
	position.x -= 0.5f;
	rotation -= 0.3f;
	star.SetPosition(position);
	star.SetRotation(rotation);
	star.SetScale(scale);

	if (position.y >= 800) {
		scale.x = 0.0f;
		scale.y = 0.0f;
		position.y = -700;
		position.x = 500;
		position.y += MathFunc::RNG(0, 1000);
		position.x += MathFunc::RNG(-1000, 1000);
		rotation += MathFunc::RNG(-1000, 1000);
	}
}

void SpritePop::PopTransition()
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

	if (scale.x <= 250.0f) {
		scale.x += 10.0f;
		scale.y += 10.0f;
	}

	position.y += 20.5f;
	position.x -= 20.5f;
	rotation -= 1.0f;
	star.SetPosition(position);
	star.SetRotation(rotation);
	star.SetScale(scale);

	if (position.y >= 1500) {
		position = { 1800.0f,-200.5f,0.0f };
		position.y += MathFunc::RNG(-700, 720);
		position.x += MathFunc::RNG(-700, 1280);
		isDead = true;
	}
}

void SpritePop::PopDraw(ID3D12GraphicsCommandList* cmdList, ID3D12Device* dev)
{
	star.SpriteTransferVertexBuffer(star);
	star.SpriteUpdate(star, spriteCommon);
	sprite->SpriteCommonBeginDraw(cmdList, spriteCommon);
	star.SpriteDraw(cmdList, spriteCommon, dev, star.vbView);
}
void SpritePop::PopCollision()
{
	if (scale.x >= -0.0f) {
		scale.x -= 1.0f;
		scale.y -= 1.0f;
	}
	if (scale.x == 0.0f) {
		isDead = true;
	}
	//isDead = true;
	star.SetScale(scale);
}