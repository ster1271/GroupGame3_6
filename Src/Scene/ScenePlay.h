#pragma once


#define BG_HUNDLE_PATH		"Data/Playimage/karibackground2.png"

//�摜�\����
struct Hundl
{
	int BgHndl;		//�w�i�摜�i�[�ϐ�

};

class Play
{
private:
	Hundl Hndl;

public:
	//�v���C������
	void InitPlay();

	//�v���C�ʏ폈��
	void StepPlay();

	//�v���C�`�揈��
	void DrawPlay();

	//�v���C�㏈��
	void FinPlay();


};
