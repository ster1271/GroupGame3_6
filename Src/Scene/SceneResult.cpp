#include "DxLib.h"
#include "../Scene.h"
#include "SceneResult.h"
#include "../Input/Input.h"

int R_Result_ScoreHandle;
int R_Result_Player1_WIN_Handle;
int R_Result_Player2_WIN_Handle;

bool R_Continue;	//コンテニューフラグ

bool R_BackTitle;	//タイトルフラグ

//タイトル初期化
void Result::InitResult()
{
	R_Result_ScoreHandle = LoadGraph(RISULT_SCORE);
	R_Result_Player1_WIN_Handle = LoadGraph(RISULT_PLAYER_1_WINS);
	R_Result_Player2_WIN_Handle = LoadGraph(RISULT_PLAYER_2_WINS);

	R_Continue = false;		//コンテニューフラグを折る

	R_BackTitle = false;	//タイトルフラグを折る

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
	DrawGraph(0, 0, R_Result_ScoreHandle, true);
}

//タイトル後処理
void Result::FinResult()
{


	//タイトル初期化シーンへ移動
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}