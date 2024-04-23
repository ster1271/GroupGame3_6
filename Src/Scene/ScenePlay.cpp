#include "DxLib.h"
#include <math.h>
#include "../Scene.h"
#include "ScenePlay.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"


//プレイ初期化
void Play::InitPlay()
{
	memset(&Hndl, 0, sizeof(HUNDL));
	LoadHundl();
	playState = State_SetPower;

	//フレームカウント変数
	FlameCount = 0.0f;
	//ディレイ用変数
	Dely = 0.0f;

	int Random = GetRand(5);
	if (Random == 1)
	{
		IsPlayer = false;
	}
	else
	{
		IsPlayer = true;
	}

	PlayerAnimeNum = 0;

	/*======1つ目のゲージに関する変数========*/
	GaugePower = 0.0f;		//ゲージ
	GaugeVolume = 0.2f;		//ゲージ増加量
	IsGauge = true;			//ゲージ増加フラグ
	SwitchGauge = 0;		//ゲージ関数swith文使用変数	
	/*======1つ目のゲージに関する変数========*/


	/*======2つ目のゲージに関する変数========*/
	SideGaugePower = 0.0f;
	SideGaugeVolume = 12.0f;
	IsSideGauge = false;
	PosX = 20;
	PosY = 365;
	InitPosX = PosX;
	i = 0;
	/*======2つ目のゲージに関する変数========*/

	/*======瓦を壊す状態========*/
	IsBreak = false;
	IsAnimeFinish = false;
	tileNum = 0;
	for (int i = 0; i < TILE_MAX_NUM; i++)
	{
		IsTileDraw[i] = false;
	}
	num = 0;
	TilePosY = 510;
	IsFinish = false;
	/*======瓦を壊す状態========*/



	//シーンをプレイ通常処理のシーンへ移動
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//プレイ通常処理
void Play::StepPlay()
{
	FlameCount++;
	

	Dely += 0.1f;
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
				PlaySoundMem(Hndl.Roulet02Hndl, DX_PLAYTYPE_NORMAL);
				IsGauge = false;
				Dely = 0.0f;
			}
		}

		if (Dely >= 15.0f && IsGauge == false)
		{
			//ディレイをかけてから状態遷移
			IsSideGauge = true;
			playState = State_SetPoint;
		}

		break;

	case State_SetPoint:

		
		SideGauge();

		//スペースキーで次の状態へ
		if (IsKeyPush(KEY_INPUT_SPACE))
		{
			PlaySoundMem(Hndl.Roulet02Hndl, DX_PLAYTYPE_NORMAL);
			SetSideGauge();
			IsSideGauge = false;
			Dely = 0.0f;
		}


		if (Dely >= 15.0f && IsSideGauge == false)
		{
			//ディレイをかけてから状態遷移
			IsBreak = true;
			playState = State_Break;
		}
		break;


	case State_Break:
		if (GaugePower > 90.0f)
		{
			GaugePower = 100.0f;
		}
		PlayerBreakTile = (GaugePower * SideGaugePower) / 100.0f;
		break;

	default:
		break;
	}
}

//プレイ描画処理
void Play::DrawPlay()
{
	//背景描画
	DrawGraph(0, 0, Hndl.BgHndl, true);
	
	//フィールド描画
	DrawGraph(0, 0, Hndl.FealdHndl, true);

	//ゲージの計算
	int a = 400 - (GAUGE_HEIGHT / 100) * (int)GaugePower;	//描画する座標
	int b = 200 - (GAUGE_HEIGHT / 100) * (int)GaugePower;	//矩形の表示座標
	int c = (GAUGE_HEIGHT / 100) * (int)GaugePower;			//矩形
	switch (playState)
	{

	//1つ目のゲージ
	case State_SetPower:
		////デバック用
		//DrawString(0, 45, "State == State_SetPower", GetColor(0, 0, 255));
		//DrawString(0, 60, "スペースでゲージを止める", GetColor(0, 0, 255));
		//DrawFormatString(0, 75, GetColor(0, 0, 255), "ゲージの量：%f", GaugePower);
		////デバック用
		
		//ゲージ(本体)の描画
		DrawRectGraph(0, a, 0, b, 200, c, Hndl.GaugeHndl, true, false);
		//ゲージ(外枠)の描画
		DrawGraph(0, 200, Hndl.GaugeFlameHndl, true);
		if (IsPlayer == true)
		{
			DrawGraph(510, 350, Hndl.PlayerHndl[0], true);		//プレイヤーの描画(待機)
		}
		else
		{
			DrawGraph(510, 350, Hndl.CPC_Hndl[0], true);		//CPUの描画(待機)
		}

		for (int i = 0; i < TILE_MAX_NUM; i++)
		{
			DrawGraph(510, 570 + i * 55, Hndl.TileHndl[i], true);		//タイルの描画(割れてない)
		}

		break;

	//2つ目のゲージ
	case State_SetPoint:
		////デバック用
		//DrawString(0, 45, "State == State_SetPoint", GetColor(0, 0, 255));
		//DrawString(0, 60, "スペースで状態遷移", GetColor(0, 0, 255));
		//DrawFormatString(0, 75, GetColor(0, 0, 255), "サイドゲージの量：%f", SideGaugePower);
		////デバック用

		DrawGraph(20, 200, Hndl.SideGaugeHndl, true);		//サイドゲージ(本体)
		DrawGraph(PosX, PosY, Hndl.SideSelectHndl, true);	//矢印
		if (IsPlayer == true)
		{
			DrawGraph(510, 350, Hndl.PlayerHndl[0], true);		//プレイヤーの描画(待機)
		}
		else
		{
			DrawGraph(510, 350, Hndl.CPC_Hndl[0], true);		//CPUの描画(待機)
		}

		for (int i = 0; i < TILE_MAX_NUM; i++)
		{
			DrawGraph(510, 570 + i * 55, Hndl.TileHndl[i], true);		//タイルの描画(割れてない)
		}
		break;


	//瓦を壊す
	case State_Break:

		////デバック用
		//DrawString(0, 45, "State == State_Break", GetColor(0, 0, 255));
		//DrawFormatString(0, 30, GetColor(0, 0, 255), "壊れる瓦の数：%d", PlayerBreakTile);
		//DrawString(0, 15, "Enterで次のシーンにいく", GetColor(255, 0, 0));
		////デバック用


		Anime();
		if (IsPlayer == true)
		{
			DrawGraph(510, 350, Hndl.PlayerHndl[PlayerAnimeNum], true);		//プレイヤーの描画(アニメーション)
		}
		else
		{
			DrawGraph(510, 350, Hndl.CPC_Hndl[PlayerAnimeNum], true);		//CPUの描画(アニメーション)
		}

		//アニメーションが終わったら
		if (IsAnimeFinish == true)
		{
			Dely = 0.0f;
			g_CurrentSceneID = SCENE_ID_TILEDROW;
		}
		else
		{
			for (int i = 0; i < TILE_MAX_NUM; i++)
			{
				DrawGraph(510, 570 + i * 55, Hndl.TileHndl[i], true);		//タイルの描画(割れてない)
			}
		}

		break;

	default:
		break;
	}

	//DrawString(0, 0, "プレイシーンです", GetColor(255, 0, 0));
}

//プレイ後処理
void Play::FinPlay()
{
	//画像の削除
	DeleteGraph(Hndl.BgHndl);
	DeleteGraph(Hndl.FealdHndl);
	DeleteGraph(Hndl.GaugeFlameHndl);
	DeleteGraph(Hndl.GaugeHndl);
	DeleteGraph(Hndl.SideGaugeHndl);
	DeleteGraph(Hndl.SideSelectHndl);

	//CPU画像の削除
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(Hndl.CPC_Hndl[i]);
	}

	//プレイヤー画像の削除
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(Hndl.PlayerHndl[i]);
	}

	for (int i = 0; i < TILE_MAX_NUM; i++)
	{
		DeleteGraph(Hndl.TileHndl[i]);				//瓦の画像(割れる前)読み込み
		DeleteGraph(Hndl.TileBreakHndl[i]);			//瓦の画像(割れた後)読み込み
	}

	//リザルトシーンへ移動
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}

//画像読み込み関数
void Play::LoadHundl()
{	
	Hndl.BgHndl = LoadGraph(BG_HUNDLE_PATH);						//背景画像読み込み
	Hndl.Bg1Hndl = LoadGraph(BG_HUNDLE1_PATH);
	Hndl.GaugeHndl = LoadGraph(GAUGE_HUNDLE_PATH);					//ゲージ(本体)画像読み込み	
	Hndl.GaugeFlameHndl = LoadGraph(GAUGE_FLAMEHUNDLE_PATH);		//ゲージ(外枠)画像読み込み
	Hndl.SideGaugeHndl = LoadGraph(GAUGE2_HUNDLE_PATH);				//サイドゲージ画像読み込み
	Hndl.SideSelectHndl = LoadGraph(GAUGE2_1_HUNDLE_PATH);			//サイドゲージ決定画像読み込み
	Hndl.FealdHndl = LoadGraph(FEALD_HUNDLE_PATH);					//フィールド画像読み込み

	Hndl.JudgeHndl[State_Good] = LoadGraph(GOOD_PATH);				//Good画像読み込み
	Hndl.JudgeHndl[State_Great] = LoadGraph(GREAT_PAYH);			//Great画像読み込み
	Hndl.JudgeHndl[State_Perfect] = LoadGraph(PERFECT_PATH);		//Perfect画像読み込み

	Hndl.CPC_Hndl[0] = LoadGraph(CPU_HUNDLE_PATH);					//CPU画像読み込み
	Hndl.CPC_Hndl[1] = LoadGraph(CPU_MOVE_PATH);					//CPU画像読み込み
	Hndl.CPC_Hndl[2] = LoadGraph(CPU_MOVE_PATH2);					//CPU画像読み込み
	Hndl.CPC_Hndl[3] = LoadGraph(CPU_ATTACK_PATH);					//CPU画像読み込み

	Hndl.PlayerHndl[0] = LoadGraph(PLAYER_WAIT_PATH);			//プレイヤー画像(1P)読み込み
	Hndl.PlayerHndl[1] = LoadGraph(PLAYER_MOVE_PATH);			//プレイヤー画像(1P)読み込み
	Hndl.PlayerHndl[2] = LoadGraph(PLAYER_MOVE_PATH2);			//プレイヤー画像(1P)読み込み
	Hndl.PlayerHndl[3] = LoadGraph(PLAYER_ATTACK_PATH);			//プレイヤー画像(1P)読み込み

	for (int i = 0; i < TILE_MAX_NUM; i++)
	{
		Hndl.TileHndl[i] = LoadGraph(TILE_HUNDLE_PATH);				//瓦の画像(割れる前)読み込み
		Hndl.TileBreakHndl[i] = LoadGraph(TILE_BREAK_HUNDLE_PATH);	//瓦の画像(割れた後)読み込み
	}

	Hndl.Roulet01Hndl = LoadSoundMem("Data/Sound/電子ルーレット回転中.mp3");
	Hndl.Roulet02Hndl = LoadSoundMem("Data/Sound/電子ルーレット停止ボタンを押す.mp3");
	Hndl.PunchSoundHndl = LoadSoundMem("Data/Sound/大パンチ.mp3");

}


//ゲージ増減関数
void Play::GaugeUpDown()
{
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

	//ゲージの増減(完成)
	switch (SwitchGauge)
	{
	case 0:
		//ゲージを増やす
		GaugePower += GaugeVolume;
		//ゲージが最大になったらスイッチのフラグを変える(101.0fなのは少し判定を緩くするため)
		if (GaugePower >= 100.0f)
		{
			SwitchGauge = 1;
		}
		break;

	case 1:
		//ゲージを減らす
		GaugePower -= GaugeVolume;
		if (GaugePower <= 0.0f)
		{
			//ゲージが0より小さくになったらスイッチのフラグを変える
			SwitchGauge = 0;
		}
		break;

	default:
		break;
	}
}

//サイドゲージ移動関数
void Play::SideGauge()
{
	if (IsSideGauge == true)
	{
		switch (i)
		{
		case 0:
			PosX += 15;
			if (PosX + 30 >= InitPosX + SIDEGAUGE_WIDHT)
			{
				i = 1;
			}
			break;

		case 1:
			PosX -= 15;
			if (PosX <= InitPosX)
			{
				i = 0;
			}
			break;

		default:
			break;
		}
	}
}

//サイドゲージパワー増減関数
void Play::SetSideGauge()
{
   	int vol = abs((PosX - InitPosX) - (SIDEGAUGE_WIDHT / 2));

	//判定処理
	if (vol <= 5)
	{
		SideGaugePower = 100;
	}
	else if (vol > 5 && vol <= 20)
	{
		SideGaugePower = 80;
	}
	else if (vol > 20 && vol <= 55)
	{
		SideGaugePower = 60;
	}
	else if (vol > 55 && vol <= 105)
	{
		SideGaugePower = 40;
	}
	else
	{
		SideGaugePower = 20;
	}
}

//アニメーション管理
void Play::Anime()
{
	if (FlameCount % 5 == 0)
	{
		if (PlayerAnimeNum == ANIME_MAX_NUM - 1)
		{
			PlayerAnimeNum = ANIME_MAX_NUM - 1;
			IsAnimeFinish = true;
		}
		else
		{
			PlayerAnimeNum++;
		}
	}
}

//瓦の描画処理
void Play::TileDraw()
{
	TilePosY -= 5.0f;
	for (int i = 0; i < TILE_MAX_NUM; i++)
	{
		if (IsTileDraw[i] == true)
		{
			DrawGraph(510, TilePosY + (float)(i * 50), Hndl.TileBreakHndl[i], true);	//壊れた瓦

			if (TilePosY + (float)(PlayerBreakTile / 2 * 50) < -10.0f)
			{
				IsFinish = true;
			}
		}
		else
		{
			DrawGraph(510, TilePosY + (float)(i * 50) + 10, Hndl.TileHndl[i], true);	//壊れてない瓦
		}
		
	}
}

//自動スクロール
void Play::Auto()
{
	DrawGraph(0, 0, Hndl.Bg1Hndl, true);

	if (IsFinish == false)
	{
		FlameCount++;
		if (FlameCount % 10 == 0)
		{
			if (num < PlayerBreakTile)
			{
				IsTileDraw[num] = true;
				num++;
			}
		}
	}
	
	TileDraw();
	
	if (IsFinish == true)
	{
		Dely += 0.1f;
		if (Dely >= 8.0f)
		{
			g_CurrentSceneID = SCENE_ID_FIN_PLAY;
		}
	}	
}