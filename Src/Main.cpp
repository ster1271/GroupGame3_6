//ウィンドウを表示するプログラム（ひな形）

#include "DxLib.h"	//DXライブラリのインクルード
#include "Scene.h"
#include "Common.h"
#include "Scene/SceneTitle.h"
#include "Scene/ScenePlay.h"
#include "Scene/SceneResult.h"
#include "Input/Input.h"

//設定フレームレート　(60FPS)
#define FRAME_RATE	(60)

//1フレームレートの時間(ミリ秒)
#define FRAME_TIME (1000 / FRAME_RATE)

struct FrameRateInfo
{
	int currentTime;	//現在の時間
	int LastFrameTime;	//前回のフレーム実行時の時間
	int g_count;			//フレームカウント用
	int calcFpsTime;	//FPSを計算した時間
	float fps;			//計算したFPS(表示用)
};

//フレームレート情報変数
FrameRateInfo frameRateInfo;

//FPS計算
void CalcFPS();

//FPS表示(デバック用）
void DrawFPS();

//シーン管理変数
SCENE_ID g_CurrentSceneID = SCENE_ID_INIT_TITLE;

//勝利状態管理変数
WIN_STATE Get_Win = EMPTY;

//瓦の割った枚数(出てくる人数分用意してる(player1, player2, cpu))
int TileBreakNum[3];

// Win32アプリケーションは WinMain関数 から始まる
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウの状態を設定する
	ChangeWindowMode(true);

	//DXライブラリの初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

	// 画面サイズを変更
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//描画するスクリーンを設定する
	SetDrawScreen(DX_SCREEN_BACK);
	
	//-----------------------------------------
	//一番最初に１回だけやる処理をここに書く

	//シーンクラスの宣言
	Title title;
	Play play;
	Result result;

	//-----------------------------------------

	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		Sleep(1);	//システム処理を返す

		//現在の時間を取得
		frameRateInfo.currentTime = GetNowCount();

		//最初のループなら
		//現在の時間を、FPSの計算をした時間に設定
		if (frameRateInfo.calcFpsTime == 0.0f)
		{
			frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
			frameRateInfo.fps = (float)FRAME_RATE;
		}

		//現在の時間が、前回のフレーム時より
		//1000/60ミリ秒（1/60）以上経過したいたら処理を実行する
		if (frameRateInfo.currentTime - frameRateInfo.LastFrameTime >= FRAME_TIME)
		{
			//フレーム実行時の時間を更新
			frameRateInfo.LastFrameTime = frameRateInfo.currentTime;

			//フレーム数をカウント
			frameRateInfo.g_count++;

			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				//エスケープキーが押されたら終了
				break;
			}

			//画面に表示されたものを初期化（１ループの１度だけ行う）
			ClearDrawScreen();

			//入力制御ステップ
			StepInput();

			switch (g_CurrentSceneID) 
			{
				/*==============タイトルシーン=============*/
				case SCENE_ID_INIT_TITLE:
				{
					//タイトル初期化
					title.InitTitle();

				}//SCENE_ID_INIT_TITLE終わりの括弧
				break;

				case SCENE_ID_LOOP_TITLE:
				{
					//タイトル通常処理
					title.StepTitle();

					//タイトル描画処理
					title.DrawTitle();

				}//SCENE_ID_LOOP_TITLE終わりの括弧
				break;

				case SCENE_ID_FIN_TITLE:
				{
					//タイトル後処理
					title.FinTitle();

				}//SCENE_ID_FIN_TITLE終わりの括弧
				break;

				
				/*==============プレイシーン=============*/
				case SCENE_ID_INIT_PLAY:
				{
					//プレイ初期化
					play.InitPlay();

				}//SCENE_ID_INIT_PLAY終わりの括弧
				break;
				case SCENE_ID_LOOP_PLAY:
				{
					//プレイ通常処理
					play.StepPlay();

					//プレイ描画処理
					play.DrawPlay();

				}//SCENE_ID_LOOP_RESULT終わりの括弧
				break;
				case SCENE_ID_FIN_PLAY:
				{
					//プレイ後処理
					play.FinPlay();
				}
				break;

				
				/*==============リザルトシーン=============*/
				case SCENE_ID_INIT_RESULT:
				{
					//リザルト初期化
					result.InitResult();

				}//SCENE_ID_INIT_RESULT終わりの括弧
				break;

				case SCENE_ID_LOOP_RESULT:
				{
					//リザルト通常処理
					result.StepResult();

					//リザルト描画処理
					result.DrawResult();

				}//SCENE_ID_LOOP_RESULT終わりの括弧
				break;

				case SCENE_ID_FIN_RESULT:
				{
					//リザルト後処理
					result.FinResult();
				}
				break;
				
			}

			
			//FPS計算
			CalcFPS();

			//FPS表示
			DrawFPS();

			//フリップ関数（ループの終わりに１度だけ行う）
			ScreenFlip();
			
			

		}//フレームレートのif分の終わり

	}//メインループの終わり

	//-----------------------------------------
	//最後に１回だけやる処理をここに書く


	//-----------------------------------------
	//DXライブラリの後処理
	DxLib_End();

	return 0;
}

void CalcFPS()
{
	//前回のFPSを計算した時間から経過時間を求める
	int difTime = frameRateInfo.currentTime - frameRateInfo.calcFpsTime;

	//前回のFPSを計算した時間から
	//１秒以上経過していたらFPSを計算する
	if (difTime > 1000)
	{
		//フレーム回数をミリ秒に合わせる
		//小数まで出したいのでfloatにキャスト
		float frameCount = (float)(frameRateInfo.g_count * 1000.0f);

		//FPSを求める
		//理想の数値は6000/1000で60となる
		frameRateInfo.fps = frameCount / difTime;

		//フレームカウントをクリア
		frameRateInfo.g_count = 0;

		//FPSを計算した時間を更新
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
	}
}

void DrawFPS()
{
	DrawFormatString(SCREEN_SIZE_X - 90, SCREEN_SIZE_Y - 20, GetColor(255, 30, 30), "FPS[%.2f]", frameRateInfo.fps);
}

