#pragma once

#define RISULT_WIN_SCORE "Data/ClearImage/Result01.png"
#define RISULT_SELECTION "Data/ClearImage/result_selection1.png"
#define RISULT_FRAME "Data/ClearImage/result_selection(3).png"
#define ROSILT_SUCOA "Data/ClearImage/number.png"
#define WIN_RLSULT 3
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
