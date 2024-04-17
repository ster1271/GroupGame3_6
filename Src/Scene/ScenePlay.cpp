#include "DxLib.h"
#include <math.h>
#include "../Scene.h"
#include "ScenePlay.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"


//プレイ初期化
void Play::InitPlay()
{
	Hndl.BgHndl = LoadGraph(BG_HUNDLE_PATH);		//背景画像読み込み
	Hndl.GaugeHndl = LoadGraph(GAUGE_HUNDLE_PATH);	//ゲージ画像読み込み			

	Gauge = 0.0f;			//ゲージ
	GaugeFlg = 0;
	IsGauge = true;

	FlameCount = 0.0f;
	GaugeUp = 0.2f;

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
	DrawGraph(0, 0, Hndl.BgHndl, true);

	//ゲージの描画
	DrawRectGraph(0, 75, 0, 0, GAUGE_WIDHT / 100 * (int)Gauge, 50, Hndl.GaugeHndl, true, false);
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
