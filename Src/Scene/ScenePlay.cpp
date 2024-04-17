#include "DxLib.h"
#include <math.h>
#include "../Scene.h"
#include "ScenePlay.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"


//プレイ初期化
void Play::InitPlay()
{
	Hndl.BgHndl = LoadGraph(BG_HUNDLE_PATH);
	Gauge = 0.0f;			//ゲージ
	GaugeFlg = 0;
	IsGauge = true;

	FlameCount = 0.0f;
	GaugeUp = 0.1f;

	//シーンをプレイ通常処理のシーンへ移動
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//プレイ通常処理
void Play::StepPlay()
{
	
	//ゲージ処理
	if (IsGauge == true)
	{
		GaugeUpDown();
	}

	//スペースキーでゲージの増加フラグをおる
	if (IsKeyPush(KEY_INPUT_SPACE))
	{
		IsGauge = false;
	}
	

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
	DrawGraph(0, 0, Hndl.BgHndl, true);

	DrawString(0, 0, "プレイシーンです", GetColor(255, 0, 0));
	DrawString(0, 15, "Enterで次のシーンにいく", GetColor(255, 0, 0));

	DrawFormatString(0, 45, GetColor(0, 0, 255), "ゲージの量：%f", Gauge);

}

//プレイ後処理
void Play::FinPlay()
{
	
	//リザルトシーンへ移動
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}


//ゲージ増減関数
void Play::GaugeUpDown()
{
	if (FlameCount % 5 == 0)
	{
		if (GaugeFlg == 0)
		{
			GaugeUp += 0.02f;
		}
		else if (GaugeFlg == 1)
		{
			GaugeUp -= 0.02f;
		}
	}

	if (GaugeUp < 0.1f)
	{
		GaugeUp = 0.1f;
	}

	//ゲージの増減(仮置き)
	switch (GaugeFlg)
	{
	case 0:
		Gauge += GaugeUp;
		if (Gauge > 101.0f)
		{
			GaugeFlg = 1;
		}
		break;

	case 1:
		Gauge -= GaugeUp;
		if (Gauge < 0.0f)
		{
			GaugeFlg = 0;
		}
		break;

	default:
		break;
	}
}
