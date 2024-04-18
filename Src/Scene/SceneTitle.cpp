#include "DxLib.h"
#include "../Scene.h"
#include "SceneTitle.h"
#include "../Input/Input.h"

int T_TitlHandle;

bool T_Continue;	//�R���e�j���[�t���O

bool T_BackTitle;	//�^�C�g���t���O

//�^�C�g��������
void Title::InitTitle()
{
	//�^�C�g���摜�ǂݍ���
	T_TitlHandle = LoadGraph(T_TITLE_NAME_PATH);
	//�^�C�g�����[�v�V�[���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//�^�C�g���ʏ폈��
void Title::StepTitle()
{

	//Enter�L�[������
	if (IsKeyPush(KEY_INPUT_RETURN))
	{
		//�^�C�g���㏈���V�[���ֈړ�
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;
	}
}

//�^�C�g���`�揈��
void Title::DrawTitle()
{
	DrawGraph(0, 0, T_TitlHandle, true);
	DrawString(0,0, "�^�C�g���V�[���ł�", GetColor(255, 255, 255));
}

//�^�C�g���㏈��
void Title::FinTitle()
{

	//���U���g�������V�[���ֈړ�
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;

}