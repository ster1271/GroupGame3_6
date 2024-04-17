#include "DxLib.h"
#include <math.h>
#include "../Scene.h"
#include "ScenePlay.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"


//�v���C������
void Play::InitPlay()
{
	Hndl.BgHndl = LoadGraph(BG_HUNDLE_PATH);
	Gauge = 0.0f;			//�Q�[�W
	GaugeFlg = 0;
	IsGauge = true;

	FlameCount = 0.0f;
	GaugeUp = 0.1f;

	//�V�[�����v���C�ʏ폈���̃V�[���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�v���C�ʏ폈��
void Play::StepPlay()
{
	
	//�Q�[�W����
	if (IsGauge == true)
	{
		GaugeUpDown();
	}

	//�X�y�[�X�L�[�ŃQ�[�W�̑����t���O������
	if (IsKeyPush(KEY_INPUT_SPACE))
	{
		IsGauge = false;
	}
	

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
	DrawGraph(0, 0, Hndl.BgHndl, true);

	DrawString(0, 0, "�v���C�V�[���ł�", GetColor(255, 0, 0));
	DrawString(0, 15, "Enter�Ŏ��̃V�[���ɂ���", GetColor(255, 0, 0));

	DrawFormatString(0, 45, GetColor(0, 0, 255), "�Q�[�W�̗ʁF%f", Gauge);

}

//�v���C�㏈��
void Play::FinPlay()
{
	
	//���U���g�V�[���ֈړ�
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}


//�Q�[�W�����֐�
void Play::GaugeUpDown()
{
	if (FlameCount % 5 == 0)
	{
		if (GaugeFlg == 0)
		{
			GaugeUp += 0.02f;
		}
		else if (GaugeFlg == 1)
		{
			GaugeUp -= 0.02f;
		}
	}

	if (GaugeUp < 0.1f)
	{
		GaugeUp = 0.1f;
	}

	//�Q�[�W�̑���(���u��)
	switch (GaugeFlg)
	{
	case 0:
		Gauge += GaugeUp;
		if (Gauge > 101.0f)
		{
			GaugeFlg = 1;
		}
		break;

	case 1:
		Gauge -= GaugeUp;
		if (Gauge < 0.0f)
		{
			GaugeFlg = 0;
		}
		break;

	default:
		break;
	}
}
