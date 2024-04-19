#include "DxLib.h"
#include <math.h>
#include "../Scene.h"
#include "ScenePlay.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"


//�v���C������
void Play::InitPlay()
{
	memset(&Hndl, 0, sizeof(Hundl));
	LoadHundl();
	playState = State_SetPower;

	//�t���[���J�E���g�ϐ�
	FlameCount = 0.0f;
	//�f�B���C�p�ϐ�
	Dely = 0.0f;

	test = 0;

	/*======1�ڂ̃Q�[�W�Ɋւ���ϐ�========*/
	GaugePower = 0.0f;		//�Q�[�W
	GaugeVolume = 0.2f;		//�Q�[�W������
	IsGauge = true;			//�Q�[�W�����t���O
	SwitchGauge = 0;		//�Q�[�W�֐�swith���g�p�ϐ�	
	/*======1�ڂ̃Q�[�W�Ɋւ���ϐ�========*/


	/*======2�ڂ̃Q�[�W�Ɋւ���ϐ�========*/
	SideGaugePower = 0.0f;
	SideGaugeVolume = 13.0f;
	IsSideGauge = true;
	PosX = GetRand(115) - 15;
	PosY = 365;
	i = 0;
	/*======2�ڂ̃Q�[�W�Ɋւ���ϐ�========*/

	//�V�[�����v���C�ʏ폈���̃V�[���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�v���C�ʏ폈��
void Play::StepPlay()
{
	FlameCount++;
	//�v���C��Ԃł��邱�Ƃ𕪂���
	switch (playState)
	{
	case State_SetPower:

		//�t���O��true�̎��ɏ�������
		if (IsGauge == true)
		{
			//�Q�[�W��������(���Ԍo�߂ŋC���������Ȃ�)
			GaugeUpDown();
			//�X�y�[�X�L�[�ŃQ�[�W�̑����t���O������
			if (IsKeyPush(KEY_INPUT_SPACE))
			{
				IsGauge = false;
				playState = State_SetPoint;
			}
		}
		break;

	case State_SetPoint:
		SideGauge();
		
		break;

	case State_Break:
		//���̃V�[���ړ�
		//Enter�L�[������
		if (IsKeyPush(KEY_INPUT_RETURN))
		{
			//�V�[�����v���C�ʏ폈���̃V�[���ֈړ�
			g_CurrentSceneID = SCENE_ID_FIN_PLAY;
		}
		break;

	default:
		break;
	}
}

//�v���C�`�揈��
void Play::DrawPlay()
{
	//�w�i�`��
	DrawGraph(0, 0, Hndl.FealdHndl, true);

	
	//CPU�̕`��
	DrawGraph(700, 350, Hndl.CPC_Hndl[0], true);

	//�Q�[�W�̌v�Z
	int a = 400 - (GAUGE_HEIGHT / 100) * (int)GaugePower;	//�`�悷����W
	int b = 200 - (GAUGE_HEIGHT / 100) * (int)GaugePower;	//��`�̕\�����W
	int c = (GAUGE_HEIGHT / 100) * (int)GaugePower;			//��`
	switch (playState)
	{
	case State_SetPower:
		DrawString(0, 45, "State == State_SetPower", GetColor(0, 0, 255));
		DrawString(0, 60, "�X�y�[�X�ŃQ�[�W���~�߂�", GetColor(0, 0, 255));
		DrawFormatString(0, 75, GetColor(0, 0, 255), "�Q�[�W�̗ʁF%f", GaugePower);

		
		//�Q�[�W(�{��)�̕`��
		DrawRectGraph(0, a, 0, b, 200, c, Hndl.GaugeHndl, true, false);
		//�Q�[�W(�O�g)�̕`��
		DrawGraph(0, 200, Hndl.GaugeFlameHndl, true);
		DrawGraph(300, 350, Hndl.PlayerHndl[0][0], true);

		break;

	case State_SetPoint:
		DrawString(0, 45, "State == State_SetPoint", GetColor(0, 0, 255));
		DrawString(0, 60, "�X�y�[�X�ŏ�ԑJ��", GetColor(0, 0, 255));

		DrawGraph(0, 200, Hndl.SideGaugeHndl, true);		//�T�C�h�Q�[�W(�{��)
		DrawGraph(PosX, PosY, Hndl.SideSelectHndl, true);	//���
		DrawGraph(300, 350, Hndl.PlayerHndl[0][0], true);
		break;

	case State_Break:
		DrawString(0, 45, "State == State_Break", GetColor(0, 0, 255));
		DrawString(0, 15, "Enter�Ŏ��̃V�[���ɂ���", GetColor(255, 0, 0));

		//�v���C���[�̕`��
		if (FlameCount % 10 == 0)
		{
			test++;
			if (test > ANIME_MAX_NUM)
			{
				test = 0;
			}
		}
		DrawGraph(300, 350, Hndl.PlayerHndl[0][test], true);
		break;

	default:
		break;
	}

	DrawString(0, 0, "�v���C�V�[���ł�", GetColor(255, 0, 0));

}

//�v���C�㏈��
void Play::FinPlay()
{
	//�摜�̍폜


	//���U���g�V�[���ֈړ�
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}

//�摜�ǂݍ��݊֐�
void Play::LoadHundl()
{	
	Hndl.BgHndl = LoadGraph(BG_HUNDLE_PATH);					//�w�i�摜�ǂݍ���
	Hndl.GaugeHndl = LoadGraph(GAUGE_HUNDLE_PATH);				//�Q�[�W(�{��)�摜�ǂݍ���	
	Hndl.GaugeFlameHndl = LoadGraph(GAUGE_FLAMEHUNDLE_PATH);	//�Q�[�W(�O�g)�摜�ǂݍ���
	Hndl.SideGaugeHndl = LoadGraph(GAUGE2_HUNDLE_PATH);
	Hndl.SideSelectHndl = LoadGraph(GAUGE2_1_HUNDLE_PATH);
	Hndl.FealdHndl = LoadGraph(FEALD_HUNDLE_PATH);				//�t�B�[���h�摜�ǂݍ���
	Hndl.CPC_Hndl[0] = LoadGraph(CPU_HUNDLE_PATH);					//CPU�摜�ǂݍ���
	Hndl.CPC_Hndl[1] = LoadGraph(CPU_HUNDLE_PATH);					//CPU�摜�ǂݍ���
	Hndl.CPC_Hndl[2] = LoadGraph(CPU_HUNDLE_PATH);					//CPU�摜�ǂݍ���

	
	Hndl.PlayerHndl[0][0] = LoadGraph(PLAYER_WAIT_PATH);			//�v���C���[�摜(1P)�ǂݍ���
	Hndl.PlayerHndl[0][1] = LoadGraph(PLAYER_MOVE_PATH);			//�v���C���[�摜(1P)�ǂݍ���
	Hndl.PlayerHndl[0][2] = LoadGraph(PLAYER_ATTACK_PATH);			//�v���C���[�摜(1P)�ǂݍ���
	Hndl.PlayerHndl[1][0] = LoadGraph(PLAYER_WAIT_PATH);			//�v���C���[�摜(2P)�ǂݍ���
	Hndl.PlayerHndl[1][1] = LoadGraph(PLAYER_WAIT_PATH);			//�v���C���[�摜(2P)�ǂݍ���
	Hndl.PlayerHndl[1][2] = LoadGraph(PLAYER_WAIT_PATH);			//�v���C���[�摜(2P)�ǂݍ���


}


//�Q�[�W�����֐�
void Play::GaugeUpDown()
{
	//5�t���[�����Ƃɑ����ʂ�ς���
	
	if (SwitchGauge == 0)
	{
		GaugeVolume += 0.15f;
	}
	else if (SwitchGauge == 1)
	{
		GaugeVolume -= 0.15f;
	}
	

	if (GaugeVolume < 0.2f)
	{
		GaugeVolume = 0.2f;
	}

	//�Q�[�W�̑���(���u��)
	switch (SwitchGauge)
	{
	case 0:
		//�Q�[�W�𑝂₷
		GaugePower += GaugeVolume;
		//�Q�[�W���ő�ɂȂ�����X�C�b�`�̃t���O��ς���(101.0f�Ȃ̂͏���������ɂ����邽��)
		if (GaugePower > 100.0f)
		{
			SwitchGauge = 1;
		}
		break;

	case 1:
		//�Q�[�W�����炷
		GaugePower -= GaugeVolume;
		if (GaugePower < 0.0f)
		{
			//�Q�[�W��0��菬�����ɂȂ�����X�C�b�`�̃t���O��ς���
			SwitchGauge = 0;
		}
		break;

	default:
		break;
	}
}

//�T�C�h�Q�[�W�ړ��Ƒ����֐�
void Play::SideGauge()
{
	if (IsSideGauge == true)
	{
		switch (i)
		{
		case 0:
			PosX += SideGaugeVolume;
			if (PosX > 275)
			{
				i = 1;
			}
			break;

		case 1:
			PosX -= SideGaugeVolume;
			if (PosX < -15)
			{
				i = 0;
			}
			break;

		default:
			break;
		}
	}

	//�X�y�[�X�L�[�Ŏ��̏�Ԃ�
	if (IsKeyPush(KEY_INPUT_SPACE))
	{
		IsSideGauge == false;

		playState = State_Break;
	}
}