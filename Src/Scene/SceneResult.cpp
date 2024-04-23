#include "DxLib.h"
#include "../Scene.h"
#include "SceneResult.h"
#include "../Input/Input.h"

int R_Result_Selectino_Handle[2];
int R_Result_Frame_Handle;

int NumberFontHndle[10];

int R_ResultPoxX; //座標

bool R_Continue;	//コンテニューフラグ

bool R_BackTitle;	//タイトルフラグ

bool R_Wins_Score; //画像切り替え

int images[WIN_RLSULT]; // 画像を格納する配列
int currentImageIndex = 0; // 現在の画像のインデックス

//タイトル初期化
void Result::InitResult()
{
	R_Result_Selectino_Handle[0] = LoadGraph(RISULT_WIN_SCORE);
	R_Result_Selectino_Handle[1] = LoadGraph(RISULT_SELECTION);;
	R_Result_Frame_Handle = LoadGraph(RISULT_FRAME);;

	NumberFontHndle[10] = { 0 };

	LoadDivGraph("Data/ClearImage/number.png", 10, 10, 1, 200, 200, NumberFontHndle);
	
	
	R_ResultPoxX = 150;

	R_Wins_Score = false;//画像切り替え

	R_Continue = false;		//コンテニューフラグを折る

	R_BackTitle = false;	//タイトルフラグを折る


	//リザルトループシーンへ移動
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//タイトル通常処理
void Result::StepResult()
{
	if (IsKeyPush(KEY_INPUT_SPACE))	//エンターキーを押すと
	{
		{
			R_Wins_Score = true;	//コンテニューフラグを立て
			if (R_Wins_Score) {
				//リザルト後処理シーンへ移動
				DeleteGraph(currentImageIndex);	//クリア背景画像破棄
				R_Result_Selectino_Handle[0] = R_Result_Selectino_Handle[1] ;
			}
		}

}
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



	DrawGraph(0, 0, R_Result_Selectino_Handle[0], true);
	DrawString(0, 0, "シフトで次の画面です", GetColor(0, 255, 0));
	DrawString(0, 10, "エンターで決定です", GetColor(255, 0, 0));
	



}

//タイトル後処理
void Result::FinResult()
{
	DeleteGraph(R_Result_Selectino_Handle[1]);	//クリア背景画像破棄
	if (R_Continue)	//コンテニューフラグがtrueなら
	{
		g_CurrentSceneID = SCENE_ID_INIT_PLAY;	//プレイシーンに戻る
	}

	else if (R_BackTitle)	//タイトルフラグがtrueなら
	{
		g_CurrentSceneID = SCENE_ID_INIT_TITLE;	//タイトルシーンに戻る
	}
	
}