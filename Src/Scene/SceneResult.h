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

	//�^�C�g��������
	void InitResult();

	//�^�C�g���ʏ폈��
	void StepResult();

	//�^�C�g���`�揈��
	void DrawResult();

	//�^�C�g���㏈��
	void FinResult();

};
