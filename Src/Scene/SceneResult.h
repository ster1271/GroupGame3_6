#pragma once

#define RISULT_SCORE "Data/ClearImage/kari_Draw.png"
#define RISULT_PLAYER_1_WIN "Data/ClearImage/kari_Player1win.png"
#define RISULT_PLAYER_2_WIN  "Data/ClearImage/kari_Player2win.png"
#define RISULT_WIN_SCORE "Data/ClearImage/kari_result.png"
#define RISULT_SELECTION "Data/ClearImage/result_selection.png"
#define RISULT_RIGHT "Data/ClearImage/result_selection(1).png"
#define RISULT_LEFT "Data/ClearImage/result_selection(2).png"
#define RISULT_FRAME "Data/ClearImage/result_selection(3).png"
#define WIN_RLSULT 3
class Result
{
private:


public:

	//�^�C�g��������
	void InitResult();

	//�^�C�g���ʏ폈��
	void StepResult();

	//�^�C�g���`�揈��
	void DrawResult();

	//�^�C�g���㏈��
	void FinResult();

};
