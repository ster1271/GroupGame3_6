#pragma once


#define BG_HUNDLE_PATH			"Data/Playimage/karibackground2.png"
#define GAUGE_FLAMEHUNDLE_PATH	"Data/Playimage/PowerBox.png"			//ゲージ(外枠)画像
#define GAUGE_HUNDLE_PATH		"Data/Playimage/PowerBox_Shadow.png"	//ゲージ(本体)画像

#define GAUGE_HEIGHT		(200)

//画像構造体
struct Hundl
{
	int BgHndl;			//背景画像ハンドル
	int GaugeFlameHndl;	//ゲージ(外枠)ハンドル
	int GaugeHndl;		//ゲージ(本体)ハンドル

	int Player[2];		//
};



class Play
{
private:
	Hundl Hndl;

	int GaugeFlg;		//ゲージのswith文変数
	float Gauge;		//ゲージ
	bool IsGauge;		//ゲージ実行中フラグ

	float Power;		//瓦を割る力

	int FlameCount;
	float GaugeUp;

public:
	//プレイ初期化
	void InitPlay();

	//プレイ通常処理
	void StepPlay();

	//プレイ描画処理
	void DrawPlay();

	//プレイ後処理
	void FinPlay();

	//画像読み込み関数
	void LoadHundl();

	//ゲージ増減関数
	void GaugeUpDown();
};
