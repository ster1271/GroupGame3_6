#include "DxLib.h"
#include "../Scene.h"
#include "SceneTitle.h"
#include "../Input/Input.h"

int T_TitlHandle[2];

int T_ChopHandle;

int T_TktlNameHandle;

bool T_Continue;	//コンテニューフラグ

bool T_BackTitle;	//タイトルフラグ

float titlex[2];

float handy;

float texty;

bool opentitle;

//タイトル初期化
void Title::InitTitle()
{
	//タイトル画像読み込み
	T_TitlHandle[0] = LoadGraph(T_TITLE_PATH1);
	T_TitlHandle[1] = LoadGraph(T_TITLE_PATH2);

	T_ChopHandle = LoadGraph(T_HAND_PATH);

	T_TktlNameHandle = LoadGraph(T_TITLE_NAME_PATH);

	handy = -600;
	titlex[0] = 0;
	titlex[1] = 640;
	texty = 0.0f;
	opentitle = false;
	//タイトルループシーンへ移動
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//タイトル通常処理
void Title::StepTitle()
{

	//Enterキーを押す
	if (texty >= 5000.0f)
	{
		//タイトル後処理シーンへ移動
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;
	}
}

//タイトル描画処理
void Title::DrawTitle()
{
	
	DrawGraph(titlex[0], 0, T_TitlHandle[0], true);
	DrawGraph(titlex[1], 0, T_TitlHandle[1], true);
	DrawGraph(100, texty, T_TktlNameHandle, true);

	DrawGraph(340, handy, T_ChopHandle, true);
	if (IsKeyPush(KEY_INPUT_RETURN))
	{
		opentitle = true;
		
	}
	if (opentitle == true)
	{
		handy+=100.0f;
		
	}
	if (handy >= 2000)
	{
		titlex[0] -= 3.0f;
		titlex[1] += 3.0f;
	}
	if (handy >= 5000)
	{
		titlex[0] -= 60.0f;
		titlex[1] += 60.0f;
	}
	if (titlex[0] <= -1200.0f)
	{
		texty -= 1.0f;
	}if (titlex[0] <= -5000.0f)
	{
		texty += 130.0f;
	}
}

//タイトル後処理
void Title::FinTitle()
{

	//リザルト初期化シーンへ移動
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;

}