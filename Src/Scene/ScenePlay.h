#pragma once


#define BG_HUNDLE_PATH			"Data/Playimage/karibackground2.png"
#define GAUGE_FLAMEHUNDLE_PATH	"Data/Playimage/PowerBox.png"			//�Q�[�W(�O�g)�摜
#define GAUGE_HUNDLE_PATH		"Data/Playimage/gauge.png"				//�Q�[�W(�{��)�摜

#define PLAYER_HUNDLE_PATH		"Data/Playimage/Player_wait1.png"		//�v���C���[�摜
#define CPU_HUNDLE_PATH			"Data/Playimage/CPU_wait1.png"			//CPU�摜

#define FEALD_HUNDLE_PATH		"Data/Playimage/background.png"			//�t�B�[���h�摜

#define GAUGE_HEIGHT		(200)

//�摜�\����
struct Hundl
{
	int BgHndl;			//�w�i�摜�n���h��
	int GaugeFlameHndl;	//�Q�[�W(�O�g)�n���h��
	int GaugeHndl;		//�Q�[�W(�{��)�n���h��
	int FealdHndl;		//�t�B�[���h�n���h��
	int CPC_Hndl;		//CPU�n���h��
	int PlayerHndl[2];	//�v���C���[�n���h��
};

//�v���C�̏�ԊǗ�
enum PlayState
{
	State_SetPower = 0,		//�p���[�����߂���
	State_SetPoint,		//��������ʒu������
	State_Break,		//����������

	State_Num			//��Ԃ̐�
};


class Play
{
private:
	Hundl Hndl;

	PlayState playState;

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
