#include "DxLib.h"
#include <math.h>
#include "../Scene.h"
#include "ScenePlay.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"


//プレイ初期化
void Play::InitPlay()
{
	LoadHundl();

	Gauge = 0.0f;			//ゲージ
	GaugeUp = 0.2f;			//ゲージ増加量
	IsGauge = true;			//ゲージ増加フラグ
	GaugeFlg = 0;			//ゲージ関数swith文使用変数


	FlameCount = 0.0f;
	

	//シーンをプレイ通常処理のシーンへ移動
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//プレイ通常処理
void Play::StepPlay()
{
	
	//フラグがtrueの時に処理する
	if (IsGauge == true)
	{
		//ゲージ増減処理(時間経過で気持ち早くなる)
		GaugeUpDown();
		//スペースキーでゲージの増減フラグをおる
		if (IsKeyPush(KEY_INPUT_SPACE))
		{
			IsGauge = false;
		}
	}
	
	//仮のシーン移動
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
	//背景描画
	DrawGraph(0, 0, Hndl.FealdHndl, true);

	//ゲージの計算
	int a = 400 - (GAUGE_HEIGHT / 100) * (int)Gauge;	//描画する座標
	int b = 200 - (GAUGE_HEIGHT / 100) * (int)Gauge;	//矩形の表示座標
	int c = (GAUGE_HEIGHT / 100) * (int)Gauge;			//矩形
	//ゲージ(本体)の描画
	DrawRectGraph(0, a, 0, b, 200, c, Hndl.GaugeHndl, true, false);

	//ゲージ(外枠)の描画
	DrawGraph(0, 200, Hndl.GaugeFlameHndl, true);

	//プレイヤーの描画
	DrawGraph(300, 350, Hndl.PlayerHndl[0], true);

	//CPUの描画
	DrawGraph(700, 350, Hndl.CPC_Hndl, true);


	DrawString(0, 45, "スペースでゲージを止める", GetColor(0, 0, 255));
	DrawFormatString(0, 60, GetColor(0, 0, 255), "ゲージの量：%f", Gauge);

	DrawString(0, 0, "プレイシーンです", GetColor(255, 0, 0));
	DrawString(0, 15, "Enterで次のシーンにいく", GetColor(255, 0, 0));


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
	Hndl.FealdHndl = LoadGraph(FEALD_HUNDLE_PATH);				//フィールド画像読み込み
	Hndl.CPC_Hndl = LoadGraph(CPU_HUNDLE_PATH);					//CPU画像読み込み
	Hndl.PlayerHndl[0] = LoadGraph(PLAYER_HUNDLE_PATH);			//プレイヤー画像(1P)読み込み
	Hndl.PlayerHndl[1] = LoadGraph(PLAYER_HUNDLE_PATH);			//プレイヤー画像(2P)読み込み

}


//ゲージ増減関数
void Play::GaugeUpDown()
{
	//5フレームごとに増減量を変える
	if (FlameCount % 5 == 0)
	{
		if (GaugeFlg == 0)
		{
			GaugeUp += 0.15f;
		}
		else if (GaugeFlg == 1)
		{
			GaugeUp -= 0.15f;
		}
	}

	if (GaugeUp < 0.2f)
	{
		GaugeUp = 0.2f;
	}

	//ゲージの増減(仮置き)
	switch (GaugeFlg)
	{
	case 0:
		//ゲージを増やす
		Gauge += GaugeUp;
		//ゲージが最大になったらスイッチのフラグを変える(101.0fなのは少し判定を緩くするため)
		if (Gauge > 100.0f)
		{
			GaugeFlg = 1;
		}
		break;

	case 1:
		//ゲージを減らす
		Gauge -= GaugeUp;
		if (Gauge < 0.0f)
		{
			//ゲージが0より小さくになったらスイッチのフラグを変える
			GaugeFlg = 0;
		}
		break;

	default:
		break;
	}
}
