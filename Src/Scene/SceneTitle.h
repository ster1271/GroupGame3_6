#pragma once

#define T_TITLE_PATH "Data/Titleimage/Title.png"
#define T_TITLE_NAME_PATH  "Data/Titleimage/Titletext.png"
class Title
{
private:
	

public:

	//タイトル初期化
	void InitTitle();

	//タイトル通常処理
	void StepTitle();

	//タイトル描画処理
	void DrawTitle();

	//タイトル後処理
	void FinTitle();
	
};
