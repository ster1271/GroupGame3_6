#include "DxLib.h"
#include "../Scene.h"
#include "SceneResult.h"
#include "../Input/Input.h"

int R_Result_Score_Handle;
int R_Result_Player1_WIN_Handle;
int R_Result_Player2_WIN_Handle;
int R_Result_Selectino_Handle[2];
int R_Result_Right_Handle;
int R_Result_Left_Handle;
int R_Result_Frame_Handle;


int R_ResultPoxX; //���W

bool R_Continue;	//�R���e�j���[�t���O

bool R_BackTitle;	//�^�C�g���t���O

bool R_Wins_Score; //�摜�؂�ւ�

int images[WIN_RLSULT]; // �摜���i�[����z��
int currentImageIndex = 0; // ���݂̉摜�̃C���f�b�N�X

//�^�C�g��������
void Result::InitResult()
{
	R_Result_Score_Handle = LoadGraph(RISULT_SCORE);
	R_Result_Player1_WIN_Handle = LoadGraph(RISULT_PLAYER_1_WIN);
	R_Result_Player2_WIN_Handle = LoadGraph(RISULT_PLAYER_2_WIN);
	R_Result_Selectino_Handle[0] = LoadGraph(RISULT_WIN_SCORE);
	R_Result_Selectino_Handle[1] = LoadGraph(RISULT_SELECTION);;
	R_Result_Right_Handle = LoadGraph(RISULT_RIGHT);;
    R_Result_Left_Handle = LoadGraph(RISULT_LEFT);;
	R_Result_Frame_Handle = LoadGraph(RISULT_FRAME);;
	
	const char* image_paths[WIN_RLSULT] = {
		RISULT_PLAYER_1_WIN,
		RISULT_PLAYER_2_WIN,
		RISULT_SCORE
	};
	R_ResultPoxX = 150;

	R_Wins_Score = false;//�摜�؂�ւ�

	R_Continue = false;		//�R���e�j���[�t���O��܂�

	R_BackTitle = false;	//�^�C�g���t���O��܂�


	//���U���g���[�v�V�[���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//�^�C�g���ʏ폈��
void Result::StepResult()
{
	
		if (IsKeyPush(KEY_INPUT_A) || IsKeyPush(KEY_INPUT_LEFT))	//A�L�[�܂��͍����L�[�������ꂽ��
		{
			if (R_ResultPoxX == 650)
			{
				R_ResultPoxX = 150;	//�ׂɈړ�����
			}
		}

		else if (IsKeyPush(KEY_INPUT_D) || IsKeyPush(KEY_INPUT_RIGHT))	//D�L�[�܂��͉E���L�[�������ꂽ��
		{
			if (R_ResultPoxX == 150)
			{
				R_ResultPoxX = 650;	//�ׂɈړ�����
			}
		}

		else if (IsKeyPush(KEY_INPUT_RETURN))	//�G���^�[�L�[��������
		{
			if (R_ResultPoxX == 150)
			{
				R_Continue = true;	//�R���e�j���[�t���O�𗧂Ă�
			}

			else if (R_ResultPoxX == 650)
			{
				R_BackTitle = true;	//�^�C�g���t���O��܂�
			}

			//���U���g�㏈���V�[���ֈړ�
			g_CurrentSceneID = SCENE_ID_FIN_RESULT;

		}
	
}

//�^�C�g���`�揈��
	void Result::DrawResult()
{
	DrawGraph(0, 0, R_Result_Selectino_Handle[0], true);
	DrawGraph(0, 0, R_Result_Score_Handle, true);
	DrawString(0, 0, "���U���g�V�[���ł�", GetColor(255, 255, 255));
	
}

//�^�C�g���㏈��
void Result::FinResult()
{

	if (R_Continue)	//�R���e�j���[�t���O��true�Ȃ�
	{
		g_CurrentSceneID = SCENE_ID_INIT_PLAY;	//�v���C�V�[���ɖ߂�
	}

	else if (R_BackTitle)	//�^�C�g���t���O��true�Ȃ�
	{
		g_CurrentSceneID = SCENE_ID_INIT_TITLE;	//�^�C�g���V�[���ɖ߂�
	}
	
}