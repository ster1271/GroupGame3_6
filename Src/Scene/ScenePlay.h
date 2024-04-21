#pragma once


#define BG_HUNDLE_PATH			"Data/Playimage/background2.png"		//�w�i�摜
#define FEALD_HUNDLE_PATH		"Data/Playimage/background.png"			//�t�B�[���h�摜


#define GAUGE_FLAMEHUNDLE_PATH	"Data/Playimage/PowerBox.png"			//�Q�[�W(�O�g)�摜
#define GAUGE_HUNDLE_PATH		"Data/Playimage/gauge.png"				//�Q�[�W(�{��)�摜
#define GAUGE_HEIGHT		(200)										//�Q�[�W�̏c��

#define GAUGE2_HUNDLE_PATH		"Data/Playimage/Charge.png"				//�T�C�h�Q�[�W�摜
#define GAUGE2_1_HUNDLE_PATH	"Data/Playimage/Chargebox_arrow.png"	//���摜
#define SIDEGAUGE_WIDHT		(300)										//�T�C�h�Q�[�W�̉���

#define ANIME_MAX_NUM		(4)											//�A�j������
#define PLAYER_WAIT_PATH		"Data/Playimage/Player_wait1.png"		//�v���C���[�摜(�ҋ@)
#define PLAYER_MOVE_PATH		"Data/Playimage/player_move.png"		//�v���C���[�摜(���[�V����1)
#define PLAYER_MOVE_PATH2		"Data/Playimage/Player_move2.png"		//�v���C���[�摜(���[�V����2)
#define PLAYER_ATTACK_PATH		"Data/Playimage/Player_attack.png"		//�v���C���[�摜(�U��)


#define CPU_HUNDLE_PATH			"Data/Playimage/CPU_wait1.png"			//CPU�摜(�ҋ@)
#define CPU_MOVE_PATH			"Data/Playimage/CPU_move.png"			//CPU�摜(���[�V����1)
#define CPU_MOVE_PATH2			"Data/Playimage/CPU_move2.png"			//CPU�摜(���[�V����2)
#define CPU_ATTACK_PATH			"Data/Playimage/CPU_attack.png"			//CPU�摜(�U��)


#define TILE_HUNDLE_PATH		"Data/Playimage/kawara.png"				//�^�C���̉摜(�����O)
#define TILE_BREAK_HUNDLE_PATH	"Data/Playimage/broken_kawara.png"		//�^�C���̉摜(���ꂽ��)
#define TILE_MAX_NUM		(100)										//���̍ő吔

#define GOOD_PATH				"Data/Playimage/Good.png"				//Good�摜
#define GREAT_PAYH				"Data/Playimage/Greatpng.png"			//Great�摜
#define PERFECT_PATH			"Data/Playimage/Perfect.png"			//Perfect�摜



//�v���C�̏�ԊǗ�
enum PLAYSTATE
{
	State_SetPower = 0,		//�p���[�����߂���
	State_SetPoint,			//��������ʒu������
	State_Break,			//����������

	State_Num				//��Ԃ̐�
};

//�Q�[�W�̏�ԊǗ�
enum GAUGESTATE
{
	State_Good = 0,		//Good
	State_Great,		//Great
	State_Perfect,		//Perfect

	Stete_Judge_Num		//�Q�[�W�̏�Ԃ̐�
};

//�摜�\����
struct HUNDL
{
	int BgHndl;							//�w�i�摜�n���h��
	int FealdHndl;						//�t�B�[���h1�摜�n���h��
	int GaugeFlameHndl;					//�Q�[�W(�O�g)�摜�n���h��
	int GaugeHndl;						//�Q�[�W(�{��)�摜�n���h��
	int SideGaugeHndl;					//�T�C�h�Q�[�W�摜�Q�[�W
	int SideSelectHndl;					//���摜�n���h��	
	int JudgeHndl[Stete_Judge_Num];		//����摜�n���h��

	int TileHndl[TILE_MAX_NUM];			//��(�����O)�̉摜�n���h��
	int TileBreakHndl[TILE_MAX_NUM];	//��(���ꂽ��)�̉摜�n���h��
	int CPC_Hndl[ANIME_MAX_NUM];		//CPU�摜�n���h��
	int PlayerHndl[2][ANIME_MAX_NUM];	//�v���C���[�摜�n���h��

};

class Play
{
private:
	HUNDL Hndl;
	PLAYSTATE playState;
	GAUGESTATE GaugeState;

	int FlameCount;			//�t���[���J�E���g
	float Dely;				//�f�B���C�p�ϐ�


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
	bool IsRight;			//�E�ɓ�����
	bool IsLeft;			//���ɓ�����
	int i;					//�T�C�h�Q�[�W��swith���ϐ�
	/*======2�ڂ̃Q�[�W�Ɋւ���ϐ�========*/

	/*======�����󂷏��========*/
	bool IsBreak;
	bool IsAnimeFinish;
	/*======�����󂷏��========*/


	int PlayerAnimeNum;

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

	//�T�C�h�Q�[�W�����֐�
	void SideGaugeUpDown();

	//�T�C�h�Q�[�W�ړ��֐�
	void SideGauge();

	//�A�j���[�V�����Ǘ�
	void Anime();
};
