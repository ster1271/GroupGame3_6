#include "DxLib.h"
#include <math.h>
#include "../Scene.h"
#include "ScenePlay.h"
#include "../Input/Input.h"


//プレイ初期化
void Play::InitPlay()
{


	//シーンをプレイ通常処理のシーンへ移動
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//プレイ通常処理
void Play::StepPlay()
{

	//Enterキーを押す
	if (IsKeyPush(KEY_INPUT_RETURN))
	{
		//シーンをプレイ通常処理のシーンへ移動
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	}
}

//プレイ描画処理
void Play::DrawPlay()
{
	DrawString(0, 0, "プレイシーンです", GetColor(255, 255, 255));
}

//プレイ後処理
void Play::FinPlay()
{
	
	//リザルトシーンへ移動
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}



