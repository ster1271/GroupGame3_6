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

	//�V�[�����v���C�ʏ폈���̃V�[���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�v���C�ʏ폈��
void Play::StepPlay()
{

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

	DrawString(0, 0, "�v���C�V�[���ł�", GetColor(255, 255, 255));
	DrawString(0, 15, "Enter�Ŏ��̃V�[���ɂ���", GetColor(255, 255, 255));

}

//�v���C�㏈��
void Play::FinPlay()
{
	
	//���U���g�V�[���ֈړ�
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}



