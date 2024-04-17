#pragma once


#define BG_HUNDLE_PATH		"Data/Playimage/karibackground2.png"
#define GAUGE_HUNDLE_PATH	"Data/Playimage/ゲージ(仮).png"

#define GAUGE_WIDHT		(600)

//画像構造体
struct Hundl
{
	int BgHndl;		//背景画像ハンドル
	int GaugeHndl;	//ゲージハンドル

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

	//ゲージ増減関数
	void GaugeUpDown();
};
