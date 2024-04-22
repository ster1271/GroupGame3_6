#include "DxLib.h"
#include <math.h>
#include "../Scene.h"
#include "ScenePlay.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"


//�v���C������
void Play::InitPlay()
{
	memset(&Hndl, 0, sizeof(HUNDL));
	LoadHundl();
	playState = State_SetPower;

	//�t���[���J�E���g�ϐ�
	FlameCount = 0.0f;
	//�f�B���C�p�ϐ�
	Dely = 0.0f;

	PlayerAnimeNum = 0;

	/*======1�ڂ̃Q�[�W�Ɋւ���ϐ�========*/
	GaugePower = 0.0f;		//�Q�[�W
	GaugeVolume = 0.2f;		//�Q�[�W������
	IsGauge = true;			//�Q�[�W�����t���O
	SwitchGauge = 0;		//�Q�[�W�֐�swith���g�p�ϐ�	
	/*======1�ڂ̃Q�[�W�Ɋւ���ϐ�========*/


	/*======2�ڂ̃Q�[�W�Ɋւ���ϐ�========*/
	SideGaugePower = 0.0f;
	SideGaugeVolume = 11.5f;
	IsSideGauge = false;
	PosX = GetRand(115) - 15;
	PosY = 365;
	IsRight = false;	//�E�ɓ�����
	IsLeft = false;		//���ɓ�����
	i = 0;
	/*======2�ڂ̃Q�[�W�Ɋւ���ϐ�========*/

	/*======�����󂷏��========*/
	IsBreak = false;
	IsAnimeFinish = false;
	tileNum = 0;
	/*======�����󂷏��========*/

	//�V�[�����v���C�ʏ폈���̃V�[���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�v���C�ʏ폈��
void Play::StepPlay()
{
	FlameCount++;
	Dely += 0.1f;
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
				Dely = 0.0f;
			}
		}

		if (Dely >= 15.0f && IsGauge == false)
		{
			//�f�B���C�������Ă����ԑJ��
			IsSideGauge = true;
			playState = State_SetPoint;
		}

		break;

	case State_SetPoint:
		SideGauge();
		SideGaugeUpDown();
		
		//�X�y�[�X�L�[�Ŏ��̏�Ԃ�
		if (IsKeyPush(KEY_INPUT_SPACE))
		{
			IsSideGauge = false;
			Dely = 0.0f;
		}

		if (Dely >= 15.0f && IsSideGauge == false)
		{
			//�f�B���C�������Ă����ԑJ��
			IsBreak = true;
			playState = State_Break;
		}
		break;


	case State_Break:
		//���̃V�[���ړ�
		TileBreakNum[0] = 10/*(GaugePower * SideGaugePower) / 100.0f*/;
		

		//�����X�N���[��������


		if (IsBreak == true)
		{
			//Enter�L�[������
			if (IsKeyPush(KEY_INPUT_RETURN))
			{
				//�V�[�����v���C�ʏ폈���̃V�[���ֈړ�
				Dely = 0.0f;
				IsBreak = false;
			}
		}

		if (Dely >= 15.0f && IsBreak == false)
		{
			//�f�B���C�������Ă���V�[���J��
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
	DrawGraph(0, 0, Hndl.BgHndl, true);
	
	//�t�B�[���h�`��
	DrawGraph(0, 0, Hndl.FealdHndl, true);

	//�Q�[�W�̌v�Z
	int a = 400 - (GAUGE_HEIGHT / 100) * (int)GaugePower;	//�`�悷����W
	int b = 200 - (GAUGE_HEIGHT / 100) * (int)GaugePower;	//��`�̕\�����W
	int c = (GAUGE_HEIGHT / 100) * (int)GaugePower;			//��`
	switch (playState)
	{

	//1�ڂ̃Q�[�W
	case State_SetPower:
		DrawString(0, 45, "State == State_SetPower", GetColor(0, 0, 255));
		DrawString(0, 60, "�X�y�[�X�ŃQ�[�W���~�߂�", GetColor(0, 0, 255));
		DrawFormatString(0, 75, GetColor(0, 0, 255), "�Q�[�W�̗ʁF%f", GaugePower);

		
		//�Q�[�W(�{��)�̕`��
		DrawRectGraph(0, a, 0, b, 200, c, Hndl.GaugeHndl, true, false);
		//�Q�[�W(�O�g)�̕`��
		DrawGraph(0, 200, Hndl.GaugeFlameHndl, true);
		DrawGraph(300, 350, Hndl.PlayerHndl[0][0], true);		//�v���C���[�̕`��(�ҋ@)
		DrawGraph(700, 350, Hndl.CPC_Hndl[0], true);			//CPU�̕`��

		break;

	//2�ڂ̃Q�[�W
	case State_SetPoint:
		DrawString(0, 45, "State == State_SetPoint", GetColor(0, 0, 255));
		DrawString(0, 60, "�X�y�[�X�ŏ�ԑJ��", GetColor(0, 0, 255));
		DrawFormatString(0, 75, GetColor(0, 0, 255), "�T�C�h�Q�[�W�̗ʁF%f", SideGaugePower);

		DrawGraph(0, 200, Hndl.SideGaugeHndl, true);		//�T�C�h�Q�[�W(�{��)
		DrawGraph(PosX, PosY, Hndl.SideSelectHndl, true);	//���
		DrawGraph(300, 350, Hndl.PlayerHndl[0][0], true);	//�v���C���[�̕`��(�ҋ@)
		DrawGraph(700, 350, Hndl.CPC_Hndl[0], true);		//CPU�̕`��(�ҋ@)
		break;


	//������
	case State_Break:
		DrawString(0, 45, "State == State_Break", GetColor(0, 0, 255));
		DrawString(0, 15, "Enter�Ŏ��̃V�[���ɂ���", GetColor(255, 0, 0));

		Anime();
		DrawGraph(300, 350, Hndl.PlayerHndl[0][PlayerAnimeNum], true);		//�v���C���[�̕`��(�A�j���[�V����)
		DrawGraph(700, 350, Hndl.CPC_Hndl[PlayerAnimeNum], true);			//CPU�̕`��(�A�j���[�V����)

		//�A�j���[�V�������I�������
		if (IsAnimeFinish == true)
		{
			TileDraw();		//���̕`��
		}

		break;

	default:
		break;
	}

	DrawString(0, 0, "�v���C�V�[���ł�", GetColor(255, 0, 0));

	DrawRotaGraph(500, 100, 1.0f, 0.0f, Hndl.JudgeHndl[State_Good], true, false, false);
	DrawRotaGraph(500, 300, 1.0f, 0.0f,Hndl.JudgeHndl[State_Great], true, false, false);
	DrawRotaGraph(500, 500, 1.0f, 0.0f, Hndl.JudgeHndl[State_Perfect], true, false, false);

}

//�v���C�㏈��
void Play::FinPlay()
{
	//�摜�̍폜
	DeleteGraph(Hndl.BgHndl);
	DeleteGraph(Hndl.FealdHndl);
	DeleteGraph(Hndl.GaugeFlameHndl);
	DeleteGraph(Hndl.GaugeHndl);
	DeleteGraph(Hndl.SideGaugeHndl);
	DeleteGraph(Hndl.SideSelectHndl);

	//CPU�摜�̍폜
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(Hndl.CPC_Hndl[i]);
	}

	//�v���C���[�摜�̍폜
	for (int i = 0; i < 2; i++)
	{
		for (int a = 0; a < ANIME_MAX_NUM; a++)
		{
			DeleteGraph(Hndl.PlayerHndl[i][a]);
		}
	}

	for (int i = 0; i < TILE_MAX_NUM; i++)
	{
		DeleteGraph(Hndl.TileHndl[i]);				//���̉摜(�����O)�ǂݍ���
		DeleteGraph(Hndl.TileBreakHndl[i]);			//���̉摜(���ꂽ��)�ǂݍ���
	}

	//���U���g�V�[���ֈړ�
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}

//�摜�ǂݍ��݊֐�
void Play::LoadHundl()
{	
	Hndl.BgHndl = LoadGraph(BG_HUNDLE_PATH);						//�w�i�摜�ǂݍ���
	Hndl.GaugeHndl = LoadGraph(GAUGE_HUNDLE_PATH);					//�Q�[�W(�{��)�摜�ǂݍ���	
	Hndl.GaugeFlameHndl = LoadGraph(GAUGE_FLAMEHUNDLE_PATH);		//�Q�[�W(�O�g)�摜�ǂݍ���
	Hndl.SideGaugeHndl = LoadGraph(GAUGE2_HUNDLE_PATH);				//�T�C�h�Q�[�W�摜�ǂݍ���
	Hndl.SideSelectHndl = LoadGraph(GAUGE2_1_HUNDLE_PATH);			//�T�C�h�Q�[�W����摜�ǂݍ���
	Hndl.FealdHndl = LoadGraph(FEALD_HUNDLE_PATH);					//�t�B�[���h�摜�ǂݍ���

	Hndl.JudgeHndl[State_Good] = LoadGraph(GOOD_PATH);				//Good�摜�ǂݍ���
	Hndl.JudgeHndl[State_Great] = LoadGraph(GREAT_PAYH);			//Great�摜�ǂݍ���
	Hndl.JudgeHndl[State_Perfect] = LoadGraph(PERFECT_PATH);		//Perfect�摜�ǂݍ���

	Hndl.CPC_Hndl[0] = LoadGraph(CPU_HUNDLE_PATH);					//CPU�摜�ǂݍ���
	Hndl.CPC_Hndl[1] = LoadGraph(CPU_MOVE_PATH);					//CPU�摜�ǂݍ���
	Hndl.CPC_Hndl[2] = LoadGraph(CPU_MOVE_PATH2);					//CPU�摜�ǂݍ���
	Hndl.CPC_Hndl[3] = LoadGraph(CPU_ATTACK_PATH);					//CPU�摜�ǂݍ���

	Hndl.PlayerHndl[0][0] = LoadGraph(PLAYER_WAIT_PATH);			//�v���C���[�摜(1P)�ǂݍ���
	Hndl.PlayerHndl[0][1] = LoadGraph(PLAYER_MOVE_PATH);			//�v���C���[�摜(1P)�ǂݍ���
	Hndl.PlayerHndl[0][2] = LoadGraph(PLAYER_MOVE_PATH2);			//�v���C���[�摜(1P)�ǂݍ���
	Hndl.PlayerHndl[0][3] = LoadGraph(PLAYER_ATTACK_PATH);			//�v���C���[�摜(1P)�ǂݍ���
	Hndl.PlayerHndl[1][0] = LoadGraph(PLAYER_WAIT_PATH);			//�v���C���[�摜(2P)�ǂݍ���
	Hndl.PlayerHndl[1][1] = LoadGraph(PLAYER_WAIT_PATH);			//�v���C���[�摜(2P)�ǂݍ���
	Hndl.PlayerHndl[1][2] = LoadGraph(PLAYER_WAIT_PATH);			//�v���C���[�摜(2P)�ǂݍ���
	Hndl.PlayerHndl[1][3] = LoadGraph(PLAYER_WAIT_PATH);			//�v���C���[�摜(2P)�ǂݍ���

	for (int i = 0; i < TILE_MAX_NUM; i++)
	{
		Hndl.TileHndl[i] = LoadGraph(TILE_HUNDLE_PATH);				//���̉摜(�����O)�ǂݍ���
		Hndl.TileBreakHndl[i] = LoadGraph(TILE_BREAK_HUNDLE_PATH);	//���̉摜(���ꂽ��)�ǂݍ���
	}
}


//�Q�[�W�����֐�
void Play::GaugeUpDown()
{
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

	//�Q�[�W�̑���(����)
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

//�T�C�h�Q�[�W�ړ��֐�
void Play::SideGauge()
{
	if (IsSideGauge == true)
	{
		switch (i)
		{
		case 0:
			PosX += 13;
			if (PosX > 275)
			{
				i = 1;
				IsRight = false;
				IsLeft = true;
			}
			break;

		case 1:
			PosX -= 13;
			if (PosX < -15)
			{
				i = 0;
				IsLeft = false;
				IsRight = true;
			}
			break;

		default:
			break;
		}
	}
}

//�T�C�h�Q�[�W�p���[�����֐�
void Play::SideGaugeUpDown()
{
	if (IsSideGauge == true)
	{
		if (IsRight == true && PosX < 150)
		{
			SideGaugePower += SideGaugeVolume;
		}
		else if (IsRight == true && PosX > 150)
		{
			SideGaugePower -= SideGaugeVolume;
		}
		else if (IsLeft == true && PosX > 150)
		{
			SideGaugePower += SideGaugeVolume;
		}
		else if (IsLeft == true && PosX < 150)
		{
			SideGaugePower -= SideGaugeVolume;
		}
	}
}

//�A�j���[�V�����Ǘ�
void Play::Anime()
{
	if (FlameCount % 10 == 0)
	{
		if (PlayerAnimeNum == ANIME_MAX_NUM - 1)
		{
			PlayerAnimeNum = ANIME_MAX_NUM - 1;
			IsAnimeFinish = true;
		}
		else
		{
			PlayerAnimeNum++;
		}
	}
}

//���̕`�揈��
void Play::TileDraw()
{
	//���̕`��
	for (int i = 0; i < TILE_MAX_NUM; i++)
	{
		if (i < TileBreakNum[0])
		{
			DrawGraph(0, i * 50, Hndl.TileBreakHndl[i], true);	//��ꂽ��	
		}
		else
		{
			DrawGraph(0, i * 55, Hndl.TileHndl[i], true);		//���ĂȂ���
		}
	}
}