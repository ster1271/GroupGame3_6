#pragma once


#define BG_HUNDLE_PATH		"Data/Playimage/karibackground2.png"

//画像構造体
struct Hundl
{
	int BgHndl;		//背景画像格納変数

};

class Play
{
private:
	Hundl Hndl;

public:
	//プレイ初期化
	void InitPlay();

	//プレイ通常処理
	void StepPlay();

	//プレイ描画処理
	void DrawPlay();

	//プレイ後処理
	void FinPlay();


};
