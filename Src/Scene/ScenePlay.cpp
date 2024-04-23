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

	int Random = GetRand(5);
	if (Random == 1)
	{
		IsPlayer = false;
	}
	else
	{
		IsPlayer = true;
	}

	PlayerAnimeNum = 0;

	/*======1�ڂ̃Q�[�W�Ɋւ���ϐ�========*/
	GaugePower = 0.0f;		//�Q�[�W
	GaugeVolume = 0.2f;		//�Q�[�W������
	IsGauge = true;			//�Q�[�W�����t���O
	SwitchGauge = 0;		//�Q�[�W�֐�swith���g�p�ϐ�	
	/*======1�ڂ̃Q�[�W�Ɋւ���ϐ�========*/


	/*======2�ڂ̃Q�[�W�Ɋւ���ϐ�========*/
	SideGaugePower = 0.0f;
	SideGaugeVolume = 12.0f;
	IsSideGauge = false;
	PosX = 20;
	PosY = 365;
	InitPosX = PosX;
	i = 0;
	/*======2�ڂ̃Q�[�W�Ɋւ���ϐ�========*/

	/*======�����󂷏��========*/
	IsBreak = false;
	IsAnimeFinish = false;
	tileNum = 0;
	for (int i = 0; i < TILE_MAX_NUM; i++)
	{
		IsTileDraw[i] = false;
	}
	num = 0;
	TilePosY = 510;
	IsFinish = false;
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
				PlaySoundMem(Hndl.Roulet02Hndl, DX_PLAYTYPE_NORMAL);
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

		//�X�y�[�X�L�[�Ŏ��̏�Ԃ�
		if (IsKeyPush(KEY_INPUT_SPACE))
		{
			PlaySoundMem(Hndl.Roulet02Hndl, DX_PLAYTYPE_NORMAL);
			SetSideGauge();
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
		if (GaugePower > 90.0f)
		{
			GaugePower = 100.0f;
		}
		PlayerBreakTile = (GaugePower * SideGaugePower) / 100.0f;
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
		////�f�o�b�N�p
		//DrawString(0, 45, "State == State_SetPower", GetColor(0, 0, 255));
		//DrawString(0, 60, "�X�y�[�X�ŃQ�[�W���~�߂�", GetColor(0, 0, 255));
		//DrawFormatString(0, 75, GetColor(0, 0, 255), "�Q�[�W�̗ʁF%f", GaugePower);
		////�f�o�b�N�p
		
		//�Q�[�W(�{��)�̕`��
		DrawRectGraph(0, a, 0, b, 200, c, Hndl.GaugeHndl, true, false);
		//�Q�[�W(�O�g)�̕`��
		DrawGraph(0, 200, Hndl.GaugeFlameHndl, true);
		if (IsPlayer == true)
		{
			DrawGraph(510, 350, Hndl.PlayerHndl[0], true);		//�v���C���[�̕`��(�ҋ@)
		}
		else
		{
			DrawGraph(510, 350, Hndl.CPC_Hndl[0], true);		//CPU�̕`��(�ҋ@)
		}

		for (int i = 0; i < TILE_MAX_NUM; i++)
		{
			DrawGraph(510, 570 + i * 55, Hndl.TileHndl[i], true);		//�^�C���̕`��(����ĂȂ�)
		}

		break;

	//2�ڂ̃Q�[�W
	case State_SetPoint:
		////�f�o�b�N�p
		//DrawString(0, 45, "State == State_SetPoint", GetColor(0, 0, 255));
		//DrawString(0, 60, "�X�y�[�X�ŏ�ԑJ��", GetColor(0, 0, 255));
		//DrawFormatString(0, 75, GetColor(0, 0, 255), "�T�C�h�Q�[�W�̗ʁF%f", SideGaugePower);
		////�f�o�b�N�p

		DrawGraph(20, 200, Hndl.SideGaugeHndl, true);		//�T�C�h�Q�[�W(�{��)
		DrawGraph(PosX, PosY, Hndl.SideSelectHndl, true);	//���
		if (IsPlayer == true)
		{
			DrawGraph(510, 350, Hndl.PlayerHndl[0], true);		//�v���C���[�̕`��(�ҋ@)
		}
		else
		{
			DrawGraph(510, 350, Hndl.CPC_Hndl[0], true);		//CPU�̕`��(�ҋ@)
		}

		for (int i = 0; i < TILE_MAX_NUM; i++)
		{
			DrawGraph(510, 570 + i * 55, Hndl.TileHndl[i], true);		//�^�C���̕`��(����ĂȂ�)
		}
		break;


	//������
	case State_Break:

		////�f�o�b�N�p
		//DrawString(0, 45, "State == State_Break", GetColor(0, 0, 255));
		//DrawFormatString(0, 30, GetColor(0, 0, 255), "���銢�̐��F%d", PlayerBreakTile);
		//DrawString(0, 15, "Enter�Ŏ��̃V�[���ɂ���", GetColor(255, 0, 0));
		////�f�o�b�N�p


		Anime();
		if (IsPlayer == true)
		{
			DrawGraph(510, 350, Hndl.PlayerHndl[PlayerAnimeNum], true);		//�v���C���[�̕`��(�A�j���[�V����)
		}
		else
		{
			DrawGraph(510, 350, Hndl.CPC_Hndl[PlayerAnimeNum], true);		//CPU�̕`��(�A�j���[�V����)
		}

		//�A�j���[�V�������I�������
		if (IsAnimeFinish == true)
		{
			Dely = 0.0f;
			g_CurrentSceneID = SCENE_ID_TILEDROW;
		}
		else
		{
			for (int i = 0; i < TILE_MAX_NUM; i++)
			{
				DrawGraph(510, 570 + i * 55, Hndl.TileHndl[i], true);		//�^�C���̕`��(����ĂȂ�)
			}
		}

		break;

	default:
		break;
	}

	//DrawString(0, 0, "�v���C�V�[���ł�", GetColor(255, 0, 0));
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
		DeleteGraph(Hndl.PlayerHndl[i]);
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
	Hndl.Bg1Hndl = LoadGraph(BG_HUNDLE1_PATH);
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

	Hndl.PlayerHndl[0] = LoadGraph(PLAYER_WAIT_PATH);			//�v���C���[�摜(1P)�ǂݍ���
	Hndl.PlayerHndl[1] = LoadGraph(PLAYER_MOVE_PATH);			//�v���C���[�摜(1P)�ǂݍ���
	Hndl.PlayerHndl[2] = LoadGraph(PLAYER_MOVE_PATH2);			//�v���C���[�摜(1P)�ǂݍ���
	Hndl.PlayerHndl[3] = LoadGraph(PLAYER_ATTACK_PATH);			//�v���C���[�摜(1P)�ǂݍ���

	for (int i = 0; i < TILE_MAX_NUM; i++)
	{
		Hndl.TileHndl[i] = LoadGraph(TILE_HUNDLE_PATH);				//���̉摜(�����O)�ǂݍ���
		Hndl.TileBreakHndl[i] = LoadGraph(TILE_BREAK_HUNDLE_PATH);	//���̉摜(���ꂽ��)�ǂݍ���
	}

	Hndl.Roulet01Hndl = LoadSoundMem("Data/Sound/�d�q���[���b�g��]��.mp3");
	Hndl.Roulet02Hndl = LoadSoundMem("Data/Sound/�d�q���[���b�g��~�{�^��������.mp3");
	Hndl.PunchSoundHndl = LoadSoundMem("Data/Sound/��p���`.mp3");

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
		if (GaugePower >= 100.0f)
		{
			SwitchGauge = 1;
		}
		break;

	case 1:
		//�Q�[�W�����炷
		GaugePower -= GaugeVolume;
		if (GaugePower <= 0.0f)
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
			PosX += 15;
			if (PosX + 30 >= InitPosX + SIDEGAUGE_WIDHT)
			{
				i = 1;
			}
			break;

		case 1:
			PosX -= 15;
			if (PosX <= InitPosX)
			{
				i = 0;
			}
			break;

		default:
			break;
		}
	}
}

//�T�C�h�Q�[�W�p���[�����֐�
void Play::SetSideGauge()
{
   	int vol = abs((PosX - InitPosX) - (SIDEGAUGE_WIDHT / 2));

	//���菈��
	if (vol <= 5)
	{
		SideGaugePower = 100;
	}
	else if (vol > 5 && vol <= 20)
	{
		SideGaugePower = 80;
	}
	else if (vol > 20 && vol <= 55)
	{
		SideGaugePower = 60;
	}
	else if (vol > 55 && vol <= 105)
	{
		SideGaugePower = 40;
	}
	else
	{
		SideGaugePower = 20;
	}
}

//�A�j���[�V�����Ǘ�
void Play::Anime()
{
	if (FlameCount % 5 == 0)
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
	TilePosY -= 5.0f;
	for (int i = 0; i < TILE_MAX_NUM; i++)
	{
		if (IsTileDraw[i] == true)
		{
			DrawGraph(510, TilePosY + (float)(i * 50), Hndl.TileBreakHndl[i], true);	//��ꂽ��

			if (TilePosY + (float)(PlayerBreakTile / 2 * 50) < -10.0f)
			{
				IsFinish = true;
			}
		}
		else
		{
			DrawGraph(510, TilePosY + (float)(i * 50) + 10, Hndl.TileHndl[i], true);	//���ĂȂ���
		}
		
	}
}

//�����X�N���[��
void Play::Auto()
{
	DrawGraph(0, 0, Hndl.Bg1Hndl, true);

	if (IsFinish == false)
	{
		FlameCount++;
		if (FlameCount % 10 == 0)
		{
			if (num < PlayerBreakTile)
			{
				IsTileDraw[num] = true;
				num++;
			}
		}
	}
	
	TileDraw();
	
	if (IsFinish == true)
	{
		Dely += 0.1f;
		if (Dely >= 8.0f)
		{
			g_CurrentSceneID = SCENE_ID_FIN_PLAY;
		}
	}	
}