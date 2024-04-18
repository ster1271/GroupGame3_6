#include "DxLib.h"
#include <math.h>
#include "../Scene.h"
#include "ScenePlay.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"


//�v���C������
void Play::InitPlay()
{
	LoadHundl();

	Gauge = 0.0f;			//�Q�[�W
	GaugeUp = 0.2f;			//�Q�[�W������
	IsGauge = true;			//�Q�[�W�����t���O
	GaugeFlg = 0;			//�Q�[�W�֐�swith���g�p�ϐ�


	FlameCount = 0.0f;
	

	//�V�[�����v���C�ʏ폈���̃V�[���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�v���C�ʏ폈��
void Play::StepPlay()
{
	
	//�t���O��true�̎��ɏ�������
	if (IsGauge == true)
	{
		//�Q�[�W��������(���Ԍo�߂ŋC���������Ȃ�)
		GaugeUpDown();
		//�X�y�[�X�L�[�ŃQ�[�W�̑����t���O������
		if (IsKeyPush(KEY_INPUT_SPACE))
		{
			IsGauge = false;
		}
	}
	
	//���̃V�[���ړ�
	//Enter�L�[������
	if (IsKeyPush(KEY_INPUT_RETURN))
	{
		//�V�[�����v���C�ʏ폈���̃V�[���ֈړ�
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	}
}

//�v���C�`�揈��
void Play::DrawPlay()
{
	//�w�i�`��
	DrawGraph(0, 0, Hndl.FealdHndl, true);

	//�Q�[�W�̌v�Z
	int a = 400 - (GAUGE_HEIGHT / 100) * (int)Gauge;	//�`�悷����W
	int b = 200 - (GAUGE_HEIGHT / 100) * (int)Gauge;	//��`�̕\�����W
	int c = (GAUGE_HEIGHT / 100) * (int)Gauge;			//��`
	//�Q�[�W(�{��)�̕`��
	DrawRectGraph(0, a, 0, b, 200, c, Hndl.GaugeHndl, true, false);

	//�Q�[�W(�O�g)�̕`��
	DrawGraph(0, 200, Hndl.GaugeFlameHndl, true);

	//�v���C���[�̕`��
	DrawGraph(300, 350, Hndl.PlayerHndl[0], true);

	//CPU�̕`��
	DrawGraph(700, 350, Hndl.CPC_Hndl, true);


	DrawString(0, 45, "�X�y�[�X�ŃQ�[�W���~�߂�", GetColor(0, 0, 255));
	DrawFormatString(0, 60, GetColor(0, 0, 255), "�Q�[�W�̗ʁF%f", Gauge);

	DrawString(0, 0, "�v���C�V�[���ł�", GetColor(255, 0, 0));
	DrawString(0, 15, "Enter�Ŏ��̃V�[���ɂ���", GetColor(255, 0, 0));


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
	Hndl.FealdHndl = LoadGraph(FEALD_HUNDLE_PATH);				//�t�B�[���h�摜�ǂݍ���
	Hndl.CPC_Hndl = LoadGraph(CPU_HUNDLE_PATH);					//CPU�摜�ǂݍ���
	Hndl.PlayerHndl[0] = LoadGraph(PLAYER_HUNDLE_PATH);			//�v���C���[�摜(1P)�ǂݍ���
	Hndl.PlayerHndl[1] = LoadGraph(PLAYER_HUNDLE_PATH);			//�v���C���[�摜(2P)�ǂݍ���

}


//�Q�[�W�����֐�
void Play::GaugeUpDown()
{
	//5�t���[�����Ƃɑ����ʂ�ς���
	if (FlameCount % 5 == 0)
	{
		if (GaugeFlg == 0)
		{
			GaugeUp += 0.15f;
		}
		else if (GaugeFlg == 1)
		{
			GaugeUp -= 0.15f;
		}
	}

	if (GaugeUp < 0.2f)
	{
		GaugeUp = 0.2f;
	}

	//�Q�[�W�̑���(���u��)
	switch (GaugeFlg)
	{
	case 0:
		//�Q�[�W�𑝂₷
		Gauge += GaugeUp;
		//�Q�[�W���ő�ɂȂ�����X�C�b�`�̃t���O��ς���(101.0f�Ȃ̂͏���������ɂ����邽��)
		if (Gauge > 100.0f)
		{
			GaugeFlg = 1;
		}
		break;

	case 1:
		//�Q�[�W�����炷
		Gauge -= GaugeUp;
		if (Gauge < 0.0f)
		{
			//�Q�[�W��0��菬�����ɂȂ�����X�C�b�`�̃t���O��ς���
			GaugeFlg = 0;
		}
		break;

	default:
		break;
	}
}
