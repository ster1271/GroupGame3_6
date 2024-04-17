#include "DxLib.h"
#include "../Scene.h"
#include "SceneResult.h"
#include "../Input/Input.h"

//タイトル初期化
void Result::InitResult()
{


	//リザルトループシーンへ移動
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//タイトル通常処理
void Result::StepResult()
{

	//Enterキーを押す
	if (IsKeyPush(KEY_INPUT_RETURN))
	{
		//リザルト後処理シーンへ移動
		g_CurrentSceneID = SCENE_ID_FIN_RESULT;
	}
}

//タイトル描画処理
void Result::DrawResult()
{
	DrawString(0, 0, "リザルトシーンです", GetColor(255, 255, 255));
}

//タイトル後処理
void Result::FinResult()
{


	//タイトル初期化シーンへ移動
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}