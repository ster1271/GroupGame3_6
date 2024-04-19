#pragma once


#define BG_HUNDLE_PATH			"Data/Playimage/karibackground2.png"	//背景画像
#define GAUGE_FLAMEHUNDLE_PATH	"Data/Playimage/PowerBox.png"			//ゲージ(外枠)画像
#define GAUGE_HUNDLE_PATH		"Data/Playimage/gauge.png"				//ゲージ(本体)画像

#define GAUGE2_HUNDLE_PATH		"Data/Playimage/Charge.png"				//ゲージ2つ目
#define GAUGE2_1_HUNDLE_PATH	"Data/Playimage/Chargebox_arrow.png"	//矢印

#define ANIME_MAX_NUM		(3)
#define PLAYER_WAIT_PATH		"Data/Playimage/Player_wait1.png"		//プレイヤー画像(待機)
#define PLAYER_MOVE_PATH		"Data/Playimage/player_move.png"		//プレイヤー画像(モーション)
#define PLAYER_ATTACK_PATH		"Data/Playimage/Player_attack.png"		//プレイヤー画像(攻撃)


#define CPU_HUNDLE_PATH			"Data/Playimage/CPU_wait1.png"			//CPU画像(待機)
#define CPU_MOVE_PATH			"Data/Playimage/CPU_wait1.png"			//CPU画像(モーション)
#define CPU_ATTACK_PATH			"Data/Playimage/CPU_wait1.png"			//CPU画像(攻撃)

#define FEALD_HUNDLE_PATH		"Data/Playimage/background.png"			//フィールド画像

#define GAUGE_HEIGHT		(200)

//画像構造体
struct Hundl
{
	int BgHndl;			//背景画像ハンドル
	int GaugeFlameHndl;	//ゲージ(外枠)ハンドル
	int GaugeHndl;		//ゲージ(本体)ハンドル
	int SideGaugeHndl;	//サイドのゲージ
	int SideSelectHndl;	//動かすほう	
	int FealdHndl;		//フィールドハンドル
	int CPC_Hndl[ANIME_MAX_NUM];		//CPUハンドル
	int PlayerHndl[2][ANIME_MAX_NUM];	//プレイヤーハンドル

	
};

//プレイの状態管理
enum PlayState
{
	State_SetPower = 0,		//パワーを決める状態
	State_SetPoint,		//瓦を割る位置決定状態
	State_Break,		//瓦を割る状態

	State_Num			//状態の数
};


class Play
{
private:
	Hundl Hndl;

	PlayState playState;

	int FlameCount;			//フレームカウント
	float Dely;				//ディレイ用変数
	float Power;			//瓦を割る力


	/*======1つ目のゲージに関する変数========*/
	int SwitchGauge;		//ゲージのswith文変数
	float GaugePower;		//ゲージの力格納変数
	float GaugeVolume;		//ゲージの増加量
	bool IsGauge;			//ゲージ実行中フラグ
	/*======1つ目のゲージに関する変数========*/

	/*======2つ目のゲージに関する変数========*/
	float SideGaugePower;	//サイドゲージの力格納変数
	float SideGaugeVolume;	//サイドゲージの増加量
	bool IsSideGauge;		//サイドゲージ実行中フラグ
	int PosX, PosY;			//動くゲージの座標格納変数
	int i;					//サイドゲージのswith分変数
	/*======2つ目のゲージに関する変数========*/




	int test;

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

	//

	//ゲージ増減関数
	void GaugeUpDown();

	//サイドゲージ移動と増減関数
	void SideGauge();
};
