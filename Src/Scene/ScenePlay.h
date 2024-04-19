#pragma once


#define BG_HUNDLE_PATH			"Data/Playimage/karibackground2.png"	//�w�i�摜
#define GAUGE_FLAMEHUNDLE_PATH	"Data/Playimage/PowerBox.png"			//�Q�[�W(�O�g)�摜
#define GAUGE_HUNDLE_PATH		"Data/Playimage/gauge.png"				//�Q�[�W(�{��)�摜

#define GAUGE2_HUNDLE_PATH		"Data/Playimage/Charge.png"				//�Q�[�W2��
#define GAUGE2_1_HUNDLE_PATH	"Data/Playimage/Chargebox_arrow.png"	//���

#define ANIME_MAX_NUM		(3)
#define PLAYER_WAIT_PATH		"Data/Playimage/Player_wait1.png"		//�v���C���[�摜(�ҋ@)
#define PLAYER_MOVE_PATH		"Data/Playimage/player_move.png"		//�v���C���[�摜(���[�V����)
#define PLAYER_ATTACK_PATH		"Data/Playimage/Player_attack.png"		//�v���C���[�摜(�U��)


#define CPU_HUNDLE_PATH			"Data/Playimage/CPU_wait1.png"			//CPU�摜(�ҋ@)
#define CPU_MOVE_PATH			"Data/Playimage/CPU_wait1.png"			//CPU�摜(���[�V����)
#define CPU_ATTACK_PATH			"Data/Playimage/CPU_wait1.png"			//CPU�摜(�U��)

#define FEALD_HUNDLE_PATH		"Data/Playimage/background.png"			//�t�B�[���h�摜

#define GAUGE_HEIGHT		(200)

//�摜�\����
struct Hundl
{
	int BgHndl;			//�w�i�摜�n���h��
	int GaugeFlameHndl;	//�Q�[�W(�O�g)�n���h��
	int GaugeHndl;		//�Q�[�W(�{��)�n���h��
	int SideGaugeHndl;	//�T�C�h�̃Q�[�W
	int SideSelectHndl;	//�������ق�	
	int FealdHndl;		//�t�B�[���h�n���h��
	int CPC_Hndl[ANIME_MAX_NUM];		//CPU�n���h��
	int PlayerHndl[2][ANIME_MAX_NUM];	//�v���C���[�n���h��

	
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

	int FlameCount;			//�t���[���J�E���g
	float Dely;				//�f�B���C�p�ϐ�
	float Power;			//���������


	/*======1�ڂ̃Q�[�W�Ɋւ���ϐ�========*/
	int SwitchGauge;		//�Q�[�W��swith���ϐ�
	float GaugePower;		//�Q�[�W�̗͊i�[�ϐ�
	float GaugeVolume;		//�Q�[�W�̑�����
	bool IsGauge;			//�Q�[�W���s���t���O
	/*======1�ڂ̃Q�[�W�Ɋւ���ϐ�========*/

	/*======2�ڂ̃Q�[�W�Ɋւ���ϐ�========*/
	float SideGaugePower;	//�T�C�h�Q�[�W�̗͊i�[�ϐ�
	float SideGaugeVolume;	//�T�C�h�Q�[�W�̑�����
	bool IsSideGauge;		//�T�C�h�Q�[�W���s���t���O
	int PosX, PosY;			//�����Q�[�W�̍��W�i�[�ϐ�
	int i;					//�T�C�h�Q�[�W��swith���ϐ�
	/*======2�ڂ̃Q�[�W�Ɋւ���ϐ�========*/




	int test;

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

	//

	//�Q�[�W�����֐�
	void GaugeUpDown();

	//�T�C�h�Q�[�W�ړ��Ƒ����֐�
	void SideGauge();
};
