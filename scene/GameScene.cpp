#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() { delete model_; }

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//画面読み込み
	texureHandle_ = TextureManager ::Load("ps.png");
	//3Dモデル生成
	model_ = Model ::Create();
	// XYZのスケーリング
	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};
	worldTransform_.rotation_ = {XM_PI/4.0f,XM_PI/4.0f,4.0f};
	// 	
	worldTransform_.translation_ = {10.0f, 10.0f, 10.0f};
	//ワールドトランス初期化
	worldTransform_.Initialize();
	//ビュープロジェクション初期化
	viewProjection_.Initialize();
	

	}

void GameScene::Update() 
{ char str[100];
	sprintf_s(str, "translation %f" ,123.33f);
	debugText_->Print(str, 100, 10, 1);

	sprintf_s(str, "rotation %f", 123.33f);
	debugText_->Print(str, 100, 30, 1);

	sprintf_s(str, "scale %f", 123.33f);
	debugText_->Print(str, 100, 50, 1);

}

    void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	model_->Draw(worldTransform_, viewProjection_, texureHandle_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
