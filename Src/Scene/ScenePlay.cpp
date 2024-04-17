#include "DxLib.h"
#include <math.h>
#include "../Scene.h"
#include "ScenePlay.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"


//�v���C������
void Play::InitPlay()
{
	Hndl.BgHndl = LoadGraph(BG_HUNDLE_PATH);		//�w�i�摜�ǂݍ���
	Hndl.GaugeHndl = LoadGraph(GAUGE_HUNDLE_PATH);	//�Q�[�W�摜�ǂݍ���			

	Gauge = 0.0f;			//�Q�[�W
	GaugeFlg = 0;
	IsGauge = true;

	FlameCount = 0.0f;
	GaugeUp = 0.2f;

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
	DrawGraph(0, 0, Hndl.BgHndl, true);

	//�Q�[�W�̕`��
	DrawRectGraph(0, 75, 0, 0, GAUGE_WIDHT / 100 * (int)Gauge, 50, Hndl.GaugeHndl, true, false);
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
