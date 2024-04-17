#include "DxLib.h"
#include "../Scene.h"
#include "SceneResult.h"
#include "../Input/Input.h"

int R_Result_ScoreHandle;
int R_Result_Player1_WIN_Handle;
int R_Result_Player2_WIN_Handle;

bool R_Continue;	//�R���e�j���[�t���O

bool R_BackTitle;	//�^�C�g���t���O

//�^�C�g��������
void Result::InitResult()
{
	R_Result_ScoreHandle = LoadGraph(RISULT_SCORE);
	R_Result_Player1_WIN_Handle = LoadGraph(RISULT_PLAYER_1_WINS);
	R_Result_Player2_WIN_Handle = LoadGraph(RISULT_PLAYER_2_WINS);

	R_Continue = false;		//�R���e�j���[�t���O��܂�

	R_BackTitle = false;	//�^�C�g���t���O��܂�

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
	DrawGraph(0, 0, R_Result_ScoreHandle, true);
}

//�^�C�g���㏈��
void Result::FinResult()
{


	//�^�C�g���������V�[���ֈړ�
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}