#include "DxLib.h"
#include "../Scene.h"
#include "SceneResult.h"
#include "../Input/Input.h"

//�^�C�g��������
void Result::InitResult()
{


	//���U���g���[�v�V�[���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//�^�C�g���ʏ폈��
void Result::StepResult()
{

	//Enter�L�[������
	if (IsKeyPush(KEY_INPUT_RETURN))
	{
		//���U���g�㏈���V�[���ֈړ�
		g_CurrentSceneID = SCENE_ID_FIN_RESULT;
	}
}

//�^�C�g���`�揈��
void Result::DrawResult()
{
	DrawString(0, 0, "���U���g�V�[���ł�", GetColor(255, 255, 255));
}

//�^�C�g���㏈��
void Result::FinResult()
{


	//�^�C�g���������V�[���ֈړ�
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}