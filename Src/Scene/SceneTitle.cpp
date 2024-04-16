#include "DxLib.h"
#include "../Scene.h"
#include "SceneTitle.h"
#include "../Input/Input.h"



//タイトル初期化
void Title::InitTitle()
{
	//タイトルループシーンへ移動
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//タイトル通常処理
void Title::StepTitle()
{

	//Enterキーを押す
	if (IsKeyPush(KEY_INPUT_RETURN))
	{
		//タイトル後処理シーンへ移動
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;
	}
}

//タイトル描画処理
void Title::DrawTitle()
{
	DrawString(0,0, "タイトルシーンです", GetColor(255, 255, 255));
}

//タイトル後処理
void Title::FinTitle()
{

	//リザルト初期化シーンへ移動
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;

}