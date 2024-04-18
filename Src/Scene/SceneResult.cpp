#include "DxLib.h"
#include "../Scene.h"
#include "SceneResult.h"
#include "../Input/Input.h"

int R_Result_Score_Handle;
int R_Result_Player1_WIN_Handle;
int R_Result_Player2_WIN_Handle;
int R_Result_Win_Score_Handle;

int R_ResultPoxX; //座標

bool R_Continue;	//コンテニューフラグ

bool R_BackTitle;	//タイトルフラグ

bool R_Wins_Score;

int images[RLSULT]; // 画像を格納する配列
int currentImageIndex = 0; // 現在の画像のインデックス

//タイトル初期化
void Result::InitResult()
{
	R_Result_Score_Handle = LoadGraph(RISULT_SCORE);
	R_Result_Player1_WIN_Handle = LoadGraph(RISULT_PLAYER_1_WIN);
	R_Result_Player2_WIN_Handle = LoadGraph(RISULT_PLAYER_2_WIN);
	R_Result_Win_Score_Handle = LoadGraph(RISULT_WIN_SCORE);

	// すべての画像パスを配列にまとめる
	const char* image_paths[RLSULT] = {
		RISULT_PLAYER_1_WIN,
		RISULT_PLAYER_2_WIN,
		RISULT_WIN_SCORE,
		RISULT_SCORE
	};
	R_ResultPoxX = 150;

	R_Continue = false;		//コンテニューフラグを折る

	R_BackTitle = false;	//タイトルフラグを折る

	//リザルトループシーンへ移動
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//タイトル通常処理
void Result::StepResult()
{

	//Enterキーを押す
	if (IsKeyPush(KEY_INPUT_A) || IsKeyPush(KEY_INPUT_LEFT))	//Aキーまたは左矢印キーが押されたら
	{
		if (R_ResultPoxX == 650)
		{
			R_ResultPoxX = 150;	//隣に移動する
		}
	}

	else if (IsKeyPush(KEY_INPUT_D) || IsKeyPush(KEY_INPUT_RIGHT))	//Dキーまたは右矢印キーが押されたら
	{
		if (R_ResultPoxX == 150)
		{
			R_ResultPoxX = 650;	//隣に移動する
		}
	}

	else if (IsKeyPush(KEY_INPUT_RETURN))	//エンターキーを押すと
	{
		if (R_ResultPoxX == 150)
		{
			R_Continue = true;	//コンテニューフラグを立てる
		}

		else if (R_ResultPoxX == 650)
		{
			R_BackTitle = true;	//タイトルフラグを折る
		}
	
			//リザルト後処理シーンへ移動
			g_CurrentSceneID = SCENE_ID_FIN_RESULT;
		
	}
}

//タイトル描画処理
	void Result::DrawResult()
{
	DrawString(0, 0, "リザルトシーンです", GetColor(255, 255, 255));
	DrawGraph(0, 0, R_Result_Score_Handle, true);

}

//タイトル後処理
void Result::FinResult()
{

	if (R_Continue)	//コンテニューフラグがtrueなら
	{
		g_CurrentSceneID = SCENE_ID_INIT_PLAY;	//プレイシーンに戻る
	}

	else if (R_BackTitle)	//タイトルフラグがtrueなら
	{
		g_CurrentSceneID = SCENE_ID_INIT_TITLE;	//タイトルシーンに戻る
	}
	
}