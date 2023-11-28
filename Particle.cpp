#include "Particle.h"
#include "FbxLoader.h"
#include <random>
#include "MathFunc.h"
using namespace DirectX::SimpleMath;

ID3D12Device* Particle::device = nullptr;
Camera*			Particle::camera = nullptr;
Input*			Particle::input = nullptr;
DXInput*		Particle::dxInput = nullptr;
const XMFLOAT3	Particle::rotLimit = { 0.5f, 0.5f, 0.5f };

//乱数シード生成器
std::random_device seed_gen3;
//メルセンヌ・ツイスターの乱数エンジン
std::mt19937_64 engine3(seed_gen3());
//乱数範囲の指定
std::uniform_real_distribution<float> distRot3(MathFunc::Utility::Deg2Rad(-60), MathFunc::Utility::Deg2Rad(60));

void Particle::Initialize(FbxModel* model, XMFLOAT3 parent)
{

	object0 = new FbxObject3D;
	object0->Initialize();
	object0->SetModel(model);

	finalPos = XMFLOAT3{ parent.x ,
						 parent.y  ,
						 parent.z };
	rotation0 = { distRot3(engine3) , distRot3(engine3) , distRot3(engine3) };

	velocity = { distRot3(engine3) , distRot3(engine3) , distRot3(engine3) };
}
void Particle::Update()
{
	rotation0.x -= velocity.x / 4.0f;;
	rotation0.y -= velocity.x / 4.0f;;
	rotation0.z -= velocity.x / 4.0f;;

	finalPos.x -= velocity.x/2.0f;
	finalPos.y -= velocity.y/2.0f;
	finalPos.z -= velocity.z/2.0f;
	if (scale0.x >= 0.0f) {
	scale0.x -= 0.0001f;
	scale0.y -= 0.0001f;
	scale0.z -= 0.0001f;
	}
	object0->SetPosition(finalPos);
	object0->SetScale({ scale0 });
	object0->SetRotation({ rotation0 });

	object0->Update();
}

void Particle::Draw(ID3D12GraphicsCommandList* cmdList)
{
	object0->Draw(cmdList);
}

void Particle::BulletShot()
{

}
