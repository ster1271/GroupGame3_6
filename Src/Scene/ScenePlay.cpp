#include "DxLib.h"
#include <math.h>
#include "../Scene.h"
#include "ScenePlay.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"


//プレイ初期化
void Play::InitPlay()
{
	memset(&Hndl, 0, sizeof(Hundl));
	LoadHundl();
	playState = State_SetPower;

	//フレームカウント変数
	FlameCount = 0.0f;
	//ディレイ用変数
	Dely = 0.0f;

	test = 0;

	/*======1つ目のゲージに関する変数========*/
	GaugePower = 0.0f;		//ゲージ
	GaugeVolume = 0.2f;		//ゲージ増加量
	IsGauge = true;			//ゲージ増加フラグ
	SwitchGauge = 0;		//ゲージ関数swith文使用変数	
	/*======1つ目のゲージに関する変数========*/


	/*======2つ目のゲージに関する変数========*/
	SideGaugePower = 0.0f;
	SideGaugeVolume = 13.0f;
	IsSideGauge = true;
	PosX = GetRand(115) - 15;
	PosY = 365;
	i = 0;
	/*======2つ目のゲージに関する変数========*/

	//シーンをプレイ通常処理のシーンへ移動
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//プレイ通常処理
void Play::StepPlay()
{
	FlameCount++;
	//プレイ状態ですることを分ける
	switch (playState)
	{
	case State_SetPower:

		//フラグがtrueの時に処理する
		if (IsGauge == true)
		{
			//ゲージ増減処理(時間経過で気持ち早くなる)
			GaugeUpDown();
			//スペースキーでゲージの増減フラグをおる
			if (IsKeyPush(KEY_INPUT_SPACE))
			{
				IsGauge = false;
				playState = State_SetPoint;
			}
		}
		break;

	case State_SetPoint:
		SideGauge();
		
		break;

	case State_Break:
		//仮のシーン移動
		//Enterキーを押す
		if (IsKeyPush(KEY_INPUT_RETURN))
		{
			//シーンをプレイ通常処理のシーンへ移動
			g_CurrentSceneID = SCENE_ID_FIN_PLAY;
		}
		break;

	default:
		break;
	}
}

//プレイ描画処理
void Play::DrawPlay()
{
	//背景描画
	DrawGraph(0, 0, Hndl.FealdHndl, true);

	
	//CPUの描画
	DrawGraph(700, 350, Hndl.CPC_Hndl[0], true);

	//ゲージの計算
	int a = 400 - (GAUGE_HEIGHT / 100) * (int)GaugePower;	//描画する座標
	int b = 200 - (GAUGE_HEIGHT / 100) * (int)GaugePower;	//矩形の表示座標
	int c = (GAUGE_HEIGHT / 100) * (int)GaugePower;			//矩形
	switch (playState)
	{
	case State_SetPower:
		DrawString(0, 45, "State == State_SetPower", GetColor(0, 0, 255));
		DrawString(0, 60, "スペースでゲージを止める", GetColor(0, 0, 255));
		DrawFormatString(0, 75, GetColor(0, 0, 255), "ゲージの量：%f", GaugePower);

		
		//ゲージ(本体)の描画
		DrawRectGraph(0, a, 0, b, 200, c, Hndl.GaugeHndl, true, false);
		//ゲージ(外枠)の描画
		DrawGraph(0, 200, Hndl.GaugeFlameHndl, true);
		DrawGraph(300, 350, Hndl.PlayerHndl[0][0], true);

		break;

	case State_SetPoint:
		DrawString(0, 45, "State == State_SetPoint", GetColor(0, 0, 255));
		DrawString(0, 60, "スペースで状態遷移", GetColor(0, 0, 255));

		DrawGraph(0, 200, Hndl.SideGaugeHndl, true);		//サイドゲージ(本体)
		DrawGraph(PosX, PosY, Hndl.SideSelectHndl, true);	//矢印
		DrawGraph(300, 350, Hndl.PlayerHndl[0][0], true);
		break;

	case State_Break:
		DrawString(0, 45, "State == State_Break", GetColor(0, 0, 255));
		DrawString(0, 15, "Enterで次のシーンにいく", GetColor(255, 0, 0));

		//プレイヤーの描画
		if (FlameCount % 10 == 0)
		{
			test++;
			if (test > ANIME_MAX_NUM)
			{
				test = 0;
			}
		}
		DrawGraph(300, 350, Hndl.PlayerHndl[0][test], true);
		break;

	default:
		break;
	}

	DrawString(0, 0, "プレイシーンです", GetColor(255, 0, 0));

}

//プレイ後処理
void Play::FinPlay()
{
	//画像の削除


	//リザルトシーンへ移動
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}

//画像読み込み関数
void Play::LoadHundl()
{	
	Hndl.BgHndl = LoadGraph(BG_HUNDLE_PATH);					//背景画像読み込み
	Hndl.GaugeHndl = LoadGraph(GAUGE_HUNDLE_PATH);				//ゲージ(本体)画像読み込み	
	Hndl.GaugeFlameHndl = LoadGraph(GAUGE_FLAMEHUNDLE_PATH);	//ゲージ(外枠)画像読み込み
	Hndl.SideGaugeHndl = LoadGraph(GAUGE2_HUNDLE_PATH);
	Hndl.SideSelectHndl = LoadGraph(GAUGE2_1_HUNDLE_PATH);
	Hndl.FealdHndl = LoadGraph(FEALD_HUNDLE_PATH);				//フィールド画像読み込み
	Hndl.CPC_Hndl[0] = LoadGraph(CPU_HUNDLE_PATH);					//CPU画像読み込み
	Hndl.CPC_Hndl[1] = LoadGraph(CPU_HUNDLE_PATH);					//CPU画像読み込み
	Hndl.CPC_Hndl[2] = LoadGraph(CPU_HUNDLE_PATH);					//CPU画像読み込み

	
	Hndl.PlayerHndl[0][0] = LoadGraph(PLAYER_WAIT_PATH);			//プレイヤー画像(1P)読み込み
	Hndl.PlayerHndl[0][1] = LoadGraph(PLAYER_MOVE_PATH);			//プレイヤー画像(1P)読み込み
	Hndl.PlayerHndl[0][2] = LoadGraph(PLAYER_ATTACK_PATH);			//プレイヤー画像(1P)読み込み
	Hndl.PlayerHndl[1][0] = LoadGraph(PLAYER_WAIT_PATH);			//プレイヤー画像(2P)読み込み
	Hndl.PlayerHndl[1][1] = LoadGraph(PLAYER_WAIT_PATH);			//プレイヤー画像(2P)読み込み
	Hndl.PlayerHndl[1][2] = LoadGraph(PLAYER_WAIT_PATH);			//プレイヤー画像(2P)読み込み


}


//ゲージ増減関数
void Play::GaugeUpDown()
{
	//5フレームごとに増減量を変える
	
	if (SwitchGauge == 0)
	{
		GaugeVolume += 0.15f;
	}
	else if (SwitchGauge == 1)
	{
		GaugeVolume -= 0.15f;
	}
	

	if (GaugeVolume < 0.2f)
	{
		GaugeVolume = 0.2f;
	}

	//ゲージの増減(仮置き)
	switch (SwitchGauge)
	{
	case 0:
		//ゲージを増やす
		GaugePower += GaugeVolume;
		//ゲージが最大になったらスイッチのフラグを変える(101.0fなのは少し判定を緩くするため)
		if (GaugePower > 100.0f)
		{
			SwitchGauge = 1;
		}
		break;

	case 1:
		//ゲージを減らす
		GaugePower -= GaugeVolume;
		if (GaugePower < 0.0f)
		{
			//ゲージが0より小さくになったらスイッチのフラグを変える
			SwitchGauge = 0;
		}
		break;

	default:
		break;
	}
}

//サイドゲージ移動と増減関数
void Play::SideGauge()
{
	if (IsSideGauge == true)
	{
		switch (i)
		{
		case 0:
			PosX += SideGaugeVolume;
			if (PosX > 275)
			{
				i = 1;
			}
			break;

		case 1:
			PosX -= SideGaugeVolume;
			if (PosX < -15)
			{
				i = 0;
			}
			break;

		default:
			break;
		}
	}

	//スペースキーで次の状態へ
	if (IsKeyPush(KEY_INPUT_SPACE))
	{
		IsSideGauge == false;

		playState = State_Break;
	}
}