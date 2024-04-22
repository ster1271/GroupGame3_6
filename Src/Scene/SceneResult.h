#pragma once

#define RISULT_SCORE "Data/ClearImage/Draw.png"
#define RISULT_PLAYER_1_WIN "Data/ClearImage/player1win.png"
#define RISULT_PLAYER_2_WIN  "Data/ClearImage/player2win.png"
#define RISULT_WIN_SCORE "Data/ClearImage/result.png"
#define RISULT_SELECTION "Data/ClearImage/result_selection1.png"
#define RISULT_RIGHT "Data/ClearImage/result_selection(1).png"
#define RISULT_LEFT "Data/ClearImage/result_selection(2).png"
#define RISULT_FRAME "Data/ClearImage/result_selection(3).png"
#define WIN_RLSULT 3
class Result
{
private:


public:

	//タイトル初期化
	void InitResult();

	void TitlResult();

	//タイトル通常処理
	void StepResult();

	//タイトル描画処理
	void DrawResult();

	//タイトル後処理
	void FinResult();

};
