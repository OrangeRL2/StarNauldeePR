#include "GameScene.h"
#include "FbxLoader.h"
#include<fstream>
#include "sstream"
#include "stdio.h"
#include "string.h"
#include "vector"
#include "imgui.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	this->dxCommon_ = dxCommon;
	this->input_ = input;

#pragma region Camera Initialization

	//Camera Initialization
	Camera::SetInput(input_);
	Camera::SetDXInput(dxInput);
	Camera* newCamera = new Camera();
	newCamera->Initialize();
	camera_.reset(newCamera);
	camera_->SetTarget({ 0,0,0 });
	camera_->SetEye({ 0, 0, -50 });

#pragma endregion

#pragma region FBX Load
	//FBX load
	FbxLoader::GetInstance()->Initialize(dxCommon_->GetDevice());

	model1 = FbxLoader::GetInstance()->LoadModelFromFile("Arwing", "Resources/titleScreen/pastelorange.png");
	model2 = FbxLoader::GetInstance()->LoadModelFromFile("Idle", "Resources/white1x1.png");
	stoneModel = FbxLoader::GetInstance()->LoadModelFromFile("stone", "Resources/white1x1.png");
	goalModel = FbxLoader::GetInstance()->LoadModelFromFile("goal", "Resources/portal.png");
	keyModel = FbxLoader::GetInstance()->LoadModelFromFile("key", "Resources/key.png");
	titleModel = FbxLoader::GetInstance()->LoadModelFromFile("title", "Resources/red.png");

	models.emplace_back(FbxLoader::GetInstance()->LoadModelFromFile("rumbaDancing", "Resources/white1x1.png"));
	models.emplace_back(FbxLoader::GetInstance()->LoadModelFromFile("boneTest", "Resources/white1x1.png"));
	models.emplace_back(FbxLoader::GetInstance()->LoadModelFromFile("fbxTest", "Resources/Corneria/GrdCorneriaBuilde1.png"));
	models.emplace_back(FbxLoader::GetInstance()->LoadModelFromFile("fbxObjectTest", "Resources/Corneria/GrdCorneriaWall4asp.png"));
	models.emplace_back(FbxLoader::GetInstance()->LoadModelFromFile("ground", "Resources/Corneria/GrdCorneriaGcst2.png"));
	models.emplace_back(FbxLoader::GetInstance()->LoadModelFromFile("skybox", "Resources/skybox/clouds.jpg"));
	models.emplace_back(FbxLoader::GetInstance()->LoadModelFromFile("stone", "Resources/white1x1.png"));
#pragma endregion

#pragma region Setting Devices to Objects

	//Setting Devices
	FbxObject3D::SetDevice(dxCommon_->GetDevice());
	FbxObject3D::SetCamera(camera_.get());
	FbxObject3D::CreateGraphicsPipeline();

#pragma endregion

#pragma region Player Initialization


	Player::SetDevice(dxCommon_->GetDevice());
	Player::SetCamera(camera_.get());
	Player::SetInput(input_);


	Player* newPlayer = new Player();
	newPlayer->Initialize(model1);
	player.reset(newPlayer);


	//PlayerBullet* newPlayerBullet = new PlayerBullet();
	//newPlayerBullet->Initialize(model1, player->GetFinalPos());
	//playerBullet.reset(newPlayerBullet);
#pragma endregion

#pragma region Sprite
	//Sprite Load
	spriteCommon = sprite->SpriteCommonCreate(dxCommon_->GetDevice(), 1280, 720);
	sprite->SpriteCommonLoadTexture(spriteCommon, 0, L"Resources/title.png", dxCommon_->GetDevice());
	sprite->SpriteCommonLoadTexture(spriteCommon, 1, L"Resources/key.png", dxCommon_->GetDevice());
	titleSprite.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);
	titleSprite.SetTexNumber(0);
	titleSprite.SetPosition(XMFLOAT3(200, 100, 0));
	titleSprite.SetScale(XMFLOAT2(414.0f * 2.2f, 54.0f * 2.2f));
	keySprite.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);
	keySprite.SetTexNumber(1);
	keySprite.SetPosition(XMFLOAT3(1200, 650, 0));
	keySprite.SetScale(XMFLOAT2(64, 64));

	TitleManager* newTitle = new TitleManager();
	newTitle->Initialize(model1, model1, dxCommon_->GetDevice());
	title.reset(newTitle);
#pragma endregion

#pragma region Level Loader
	//Level Editor
	jsonLoader = new JsonLoader();
	jsonLoader->LoadFile("Resources/levels/test12.json");
	for (int i = 0; i < jsonLoader->GetObjectDatas(); i++)
	{
		std::unique_ptr<FbxObject3D>newObject = std::make_unique<FbxObject3D>();

		newObject->Initialize();
		/*newObject->SetModel(model1);
		newObject->PlayAnimation();*/
		for (std::unique_ptr<FbxModel>& model : models)
		{
			if (jsonLoader->GetFileName(i) == model->GetFileName())
			{
				newObject->SetModel(model.get());
			}
		}
		newObject->SetPosition(jsonLoader->GetPosition(i));
		newObject->SetScale(jsonLoader->GetScale(i));
		newObject->SetRotation(jsonLoader->GetRotation(i));

		start = { jsonLoader->GetPoint1(0) };
		p2 = { jsonLoader->GetPoint2(0) };
		p3 = { jsonLoader->GetPoint3(0) };
		p4 = { jsonLoader->GetPoint4(0) };
		end = { jsonLoader->GetPoint5(0) };

		objects.push_back(std::move(newObject));
	}

	points = { start,start,p2,p3,p4,end,end };
#pragma endregion

	SetTitle();
}

void GameScene::Update()
{
	(this->*Scene_[scene_])();

	//For debugging Change stage by key input
	if (input_->TriggerKey(DIK_SPACE))stage = Stage::Tutorial;
	if (input_->TriggerKey(DIK_0))stage = Stage::Tutorial;
	if (input_->TriggerKey(DIK_1))stage = Stage::Stage1;
	if (input_->TriggerKey(DIK_2))stage = Stage::Stage2;
	if (input_->TriggerKey(DIK_3))stage = Stage::Stage3;
	if (input_->TriggerKey(DIK_4))stage = Stage::Stage4;
	if (input_->TriggerKey(DIK_5))stage = Stage::Stage5;
	if (input_->TriggerKey(DIK_9))stage = Stage::Title;

	//Reset process if the previous scene and current scene are different
	if (scene_ != preScene_)
	{
		//set title
		if (scene_ == static_cast<size_t>(Scene::Title))SetTitle();
	}

	//Reset process if the previous stage and current stage are different
	if (stage != preStage)
	{
		if (stage == Stage::Tutorial)	SetTutorial();
		if (stage == Stage::Stage1)		SetStage1();
		if (stage == Stage::Stage2)		SetStage2();
		if (stage == Stage::Stage3)		SetStage3();
		if (stage == Stage::Stage4)		SetStage4();
		if (stage == Stage::Stage5)		SetStage5();
		if (stage == Stage::Title)		SetTitle();
	}

	preScene_ = scene_;
	preStage = stage;

	player->Update(cameraPosition);

}

void GameScene::Draw()
{
	(this->*SceneDraw_[sceneDraw_])();
	//ImGui::Text("Timer %f", title->GetTurning());
}

void GameScene::TitleUpdate()
{
	//Update for title
	title->Update(model1, model1, dxCommon_->GetDevice());
	if (input_->TriggerKey(DIK_0))stage = Stage::Tutorial;
	if (input_->TriggerKey(DIK_1))stage = Stage::Stage1;
	if (input_->TriggerKey(DIK_2))stage = Stage::Stage2;
	if (input_->TriggerKey(DIK_3))stage = Stage::Stage3;
	if (input_->TriggerKey(DIK_4))stage = Stage::Stage4;
	if (input_->TriggerKey(DIK_5))stage = Stage::Stage5;
	if (input_->TriggerKey(DIK_9))stage = Stage::Title;
	camera_->DebugUpdate();
	
	if (stage == Stage::Tutorial) {
		scene_ = static_cast<size_t>(Scene::Game);
		sceneDraw_ = static_cast<size_t>(SceneDraw::GameDraw);
		stage = Stage::Tutorial;
	}
}

void GameScene::TitleDraw()
{
	//drawing for title screen
	for (std::unique_ptr<FbxObject3D>& object0 : objects)
	{
		object0->Draw(dxCommon_->GetCommandList());
	}

	title->Draw(dxCommon_->GetCommandList(), dxCommon_->GetDevice());
	player->Draw(dxCommon_->GetCommandList());
}

void GameScene::GameUpdate()
{
	//update for game scene
	title->Transition(dxCommon_->GetDevice());
	for (std::unique_ptr<FbxObject3D>& object0 : objects)
	{
		object0->Update();
	}
	if (title->GetStartFlag() == false) {
		camera_->DebugUpdate();
		eye_ = spline_.Update(points, timeRate);
		cameraPosition.x -= 0.5f;
		cameraPosition.y = 30.0f;
		camera_->SetTarget(XMFLOAT3{ -100,-100, -100 });
		camera_->SetEye(XMFLOAT3{ player->GetFinalPos().x + 20,player->GetFinalPos().y + 5.0f, player->GetFinalPos().z });
		camera_->Update();
	}
	
	if (title->GetStartFlag() == true && player->GetIsDead() == false) {
		
		eye_ = spline_.Update(points, timeRate);
		cameraPosition.x -= 1.0f;
		cameraPosition.y = 30.0f;
		camera_->SetTarget(XMFLOAT3{ player->GetPosition0().x + cameraPosition.x, player->GetPosition0().y + cameraPosition.y, player->GetPosition0().z + cameraPosition.z });
		camera_->SetEye(XMFLOAT3{ player->GetPosition0().x + cameraPosition.x + 20,player->GetPosition0().y + cameraPosition.y + 5.0f, player->GetPosition0().z + cameraPosition.z });
		camera_->Update();
	}
	if (cameraPosition.x <= end.x) {
		player->IsDead();
	}
	if (stage == Stage::Title) {
		scene_ = static_cast<size_t>(Scene::Title);
		sceneDraw_ = static_cast<size_t>(SceneDraw::TitleDraw);
		stage = Stage::Title;
	}
	if (input_->TriggerKey(DIK_0)) {
		player->IsDead();

	}
}

void GameScene::GameDraw()
{
	//drawing for title screen
	for (std::unique_ptr<FbxObject3D>& object0 : objects)
	{
		object0->Draw(dxCommon_->GetCommandList());
	}
	player->Draw(dxCommon_->GetCommandList());
	title->GameDraw(dxCommon_->GetCommandList(), dxCommon_->GetDevice());
	if (player->GetIsDead() == true) {
		title->OverDraw(dxCommon_->GetCommandList(), dxCommon_->GetDevice());
	}
}

void GameScene::SetTitle()
{
	//sets title screen
	camera_->SetTarget({ 0,0,0 });
	camera_->SetEye({ 0, 0, -70 });
	timeRate = 0;
	//title->ModelDraw(dxCommon_->GetDevice());
	//title->TransitionPop(dxCommon_->GetDevice());
	title->TransitionReset();
	//points = { start,start,p2,p3,p4,end,end };
	
}

void GameScene::SetTutorial()
{
	//sets tutorial

	player->revive();

	//start = { 0,0,0 };
	timeRate = 0;

	cameraPosition.x = -100.0f;
	cameraPosition.y = 30.0f;
	/*points = { start,start,p2,p3,p4,end,end };
	spline_.Reset(points, timeRate);*/
	/*eye_ = spline_.Update(points, timeRate);
	cameraPosition = spline_.Update(points, timeRate);*/
	//title->TransitionPop(dxCommon_->GetDevice());
	//timeRate = 0;
	////player->SetTutorial();

	//jsonLoader = new JsonLoader();
	//jsonLoader->LoadFile("Resources/levels/test12.json");
	//
	//for (int i = 0; i < jsonLoader->GetObjectDatas(); i++)
	//{
	//	std::unique_ptr<FbxObject3D>newObject = std::make_unique<FbxObject3D>();
	//	
	//	newObject->Initialize();
	//	/*newObject->SetModel(model1);
	//	newObject->PlayAnimation();*/
	//	for (std::unique_ptr<FbxModel>& model : models)
	//	{
	//		if (jsonLoader->GetFileName(i) == model->GetFileName())
	//		{
	//			newObject->SetModel(model.get());
	//		}
	//	}
	//	newObject->SetPosition(jsonLoader->GetPosition(i));
	//	newObject->SetScale(jsonLoader->GetScale(i));
	//	newObject->SetRotation(jsonLoader->GetRotation(i));

	//	start = { jsonLoader->GetPoint1(0) };
	//	p2 = { jsonLoader->GetPoint2(0) };
	//	p3 = { jsonLoader->GetPoint3(0) };
	//	p4 = { jsonLoader->GetPoint4(0) };
	//	end = { jsonLoader->GetPoint5(0) };

	//	objects.push_back(std::move(newObject));
	//}

	//points = { start,start,p2,p3,p4,end,end };

	//spline_.Update(points, timeRate);
}

void GameScene::SetStage1()
{

}

void GameScene::SetStage2()
{


}

void GameScene::SetStage3()
{



}

void GameScene::SetStage4()
{

}

void GameScene::SetStage5()
{

}

void GameScene::LoadCsv(const wchar_t* fileName, int obstacleVal)
{

}

void GameScene::DebugLoadCsv(const wchar_t* fileName, int obstacleVal)
{

}

void (GameScene::* GameScene::Scene_[])() =
{
	&GameScene::TitleUpdate,
	&GameScene::GameUpdate,
};

void (GameScene::* GameScene::SceneDraw_[])() =
{
	&GameScene::TitleDraw,
	&GameScene::GameDraw,
};
