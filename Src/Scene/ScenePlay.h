#pragma once


#define BG_HUNDLE_PATH		"Data/Playimage/karibackground2.png"
#define GAUGE_HUNDLE_PATH	"Data/Playimage/�Q�[�W(��).png"

#define GAUGE_WIDHT		(600)

//�摜�\����
struct Hundl
{
	int BgHndl;		//�w�i�摜�n���h��
	int GaugeHndl;	//�Q�[�W�n���h��

};



class Play
{
private:
	Hundl Hndl;

	int GaugeFlg;		//�Q�[�W��swith���ϐ�
	float Gauge;		//�Q�[�W
	bool IsGauge;		//�Q�[�W���s���t���O

	float Power;		//���������

	int FlameCount;
	float GaugeUp;

public:
	//�v���C������
	void InitPlay();

	//�v���C�ʏ폈��
	void StepPlay();

	//�v���C�`�揈��
	void DrawPlay();

	//�v���C�㏈��
	void FinPlay();

	//�Q�[�W�����֐�
	void GaugeUpDown();
};
