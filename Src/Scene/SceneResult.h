#pragma once

#define RISULT_SCORE "Data/ClearImage/kari_Draw.png"
#define RISULT_PLAYER_1_WIN "Data/ClearImage/kari_Player1win.png"
#define RISULT_PLAYER_2_WIN  "Data/ClearImage/kari_Player2win.png"
#define RISULT_WIN_SCORE "Data/ClearImage/kari_result"

#define RLSULT 4
class Result
{
private:


public:

	//タイトル初期化
	void InitResult();

	//タイトル通常処理
	void StepResult();

	//タイトル描画処理
	void DrawResult();

	//タイトル後処理
	void FinResult();

};
