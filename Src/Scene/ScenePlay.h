#pragma once


#define BG_HUNDLE_PATH			"Data/Playimage/background2.png"		//背景画像
#define FEALD_HUNDLE_PATH		"Data/Playimage/background.png"			//フィールド画像


#define GAUGE_FLAMEHUNDLE_PATH	"Data/Playimage/PowerBox.png"			//ゲージ(外枠)画像
#define GAUGE_HUNDLE_PATH		"Data/Playimage/gauge.png"				//ゲージ(本体)画像
#define GAUGE_HEIGHT		(200)										//ゲージの縦幅

#define GAUGE2_HUNDLE_PATH		"Data/Playimage/Charge.png"				//サイドゲージ画像
#define GAUGE2_1_HUNDLE_PATH	"Data/Playimage/Chargebox_arrow.png"	//矢印画像
#define SIDEGAUGE_WIDHT		(300)										//サイドゲージの横幅

#define ANIME_MAX_NUM		(4)											//アニメ枚数
#define PLAYER_WAIT_PATH		"Data/Playimage/Player_wait1.png"		//プレイヤー画像(待機)
#define PLAYER_MOVE_PATH		"Data/Playimage/player_move.png"		//プレイヤー画像(モーション1)
#define PLAYER_MOVE_PATH2		"Data/Playimage/Player_move2.png"		//プレイヤー画像(モーション2)
#define PLAYER_ATTACK_PATH		"Data/Playimage/Player_attack.png"		//プレイヤー画像(攻撃)


#define CPU_HUNDLE_PATH			"Data/Playimage/CPU_wait1.png"			//CPU画像(待機)
#define CPU_MOVE_PATH			"Data/Playimage/CPU_move.png"			//CPU画像(モーション1)
#define CPU_MOVE_PATH2			"Data/Playimage/CPU_move2.png"			//CPU画像(モーション2)
#define CPU_ATTACK_PATH			"Data/Playimage/CPU_attack.png"			//CPU画像(攻撃)


#define TILE_HUNDLE_PATH		"Data/Playimage/kawara.png"				//タイルの画像(割れる前)
#define TILE_BREAK_HUNDLE_PATH	"Data/Playimage/broken_kawara.png"		//タイルの画像(割れた後)
#define TILE_MAX_NUM		(100)										//瓦の最大数

#define GOOD_PATH				"Data/Playimage/Good.png"				//Good画像
#define GREAT_PAYH				"Data/Playimage/Greatpng.png"			//Great画像
#define PERFECT_PATH			"Data/Playimage/Perfect.png"			//Perfect画像



//プレイの状態管理
enum PLAYSTATE
{
	State_SetPower = 0,		//パワーを決める状態
	State_SetPoint,			//瓦を割る位置決定状態
	State_Break,			//瓦を割る状態

	State_Num				//状態の数
};

//ゲージの状態管理
enum GAUGESTATE
{
	State_Good = 0,		//Good
	State_Great,		//Great
	State_Perfect,		//Perfect

	Stete_Judge_Num		//ゲージの状態の数
};

//画像構造体
struct HUNDL
{
	int BgHndl;							//背景画像ハンドル
	int FealdHndl;						//フィールド1画像ハンドル
	int GaugeFlameHndl;					//ゲージ(外枠)画像ハンドル
	int GaugeHndl;						//ゲージ(本体)画像ハンドル
	int SideGaugeHndl;					//サイドゲージ画像ゲージ
	int SideSelectHndl;					//矢印画像ハンドル	
	int JudgeHndl[Stete_Judge_Num];		//判定画像ハンドル

	int TileHndl[TILE_MAX_NUM];			//瓦(割れる前)の画像ハンドル
	int TileBreakHndl[TILE_MAX_NUM];	//瓦(割れた後)の画像ハンドル
	int CPC_Hndl[ANIME_MAX_NUM];		//CPU画像ハンドル
	int PlayerHndl[2][ANIME_MAX_NUM];	//プレイヤー画像ハンドル

};

class Play
{
private:
	HUNDL Hndl;
	PLAYSTATE playState;
	GAUGESTATE GaugeState;

	int FlameCount;			//フレームカウント
	float Dely;				//ディレイ用変数


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
	bool IsRight;			//右に動くか
	bool IsLeft;			//左に動くか
	int i;					//サイドゲージのswith分変数
	/*======2つ目のゲージに関する変数========*/

	/*======瓦を壊す状態========*/
	bool IsBreak;
	bool IsAnimeFinish;
	/*======瓦を壊す状態========*/


	int PlayerAnimeNum;

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

	//サイドゲージ増減関数
	void SideGaugeUpDown();

	//サイドゲージ移動関数
	void SideGauge();

	//アニメーション管理
	void Anime();
};
