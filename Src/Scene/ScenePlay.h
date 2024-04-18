#pragma once


#define BG_HUNDLE_PATH			"Data/Playimage/karibackground2.png"
#define GAUGE_FLAMEHUNDLE_PATH	"Data/Playimage/PowerBox.png"			//�Q�[�W(�O�g)�摜
#define GAUGE_HUNDLE_PATH		"Data/Playimage/PowerBox_Shadow.png"	//�Q�[�W(�{��)�摜

#define GAUGE_HEIGHT		(200)

//�摜�\����
struct Hundl
{
	int BgHndl;			//�w�i�摜�n���h��
	int GaugeFlameHndl;	//�Q�[�W(�O�g)�n���h��
	int GaugeHndl;		//�Q�[�W(�{��)�n���h��

	int Player[2];		//
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

	//�摜�ǂݍ��݊֐�
	void LoadHundl();

	//�Q�[�W�����֐�
	void GaugeUpDown();
};
