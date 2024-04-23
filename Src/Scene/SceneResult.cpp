#include "DxLib.h"
#include "../Scene.h"
#include "SceneResult.h"
#include "../Input/Input.h"

int R_Result_Selectino_Handle[2];
int R_Result_Frame_Handle;

int NumberFontHndle[10];

int R_ResultPoxX; //���W

bool R_Continue;	//�R���e�j���[�t���O

bool R_BackTitle;	//�^�C�g���t���O

bool R_Wins_Score; //�摜�؂�ւ�

int images[WIN_RLSULT]; // �摜���i�[����z��
int currentImageIndex = 0; // ���݂̉摜�̃C���f�b�N�X

//�^�C�g��������
void Result::InitResult()
{
	R_Result_Selectino_Handle[0] = LoadGraph(RISULT_WIN_SCORE);
	R_Result_Selectino_Handle[1] = LoadGraph(RISULT_SELECTION);;
	R_Result_Frame_Handle = LoadGraph(RISULT_FRAME);;

	NumberFontHndle[10] = { 0 };

	LoadDivGraph("Data/ClearImage/number.png", 10, 10, 1, 200, 200, NumberFontHndle);
	
	
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
	if (IsKeyPush(KEY_INPUT_SPACE))	//�G���^�[�L�[��������
	{
		{
			R_Wins_Score = true;	//�R���e�j���[�t���O�𗧂�
			if (R_Wins_Score) {
				//���U���g�㏈���V�[���ֈړ�
				DeleteGraph(currentImageIndex);	//�N���A�w�i�摜�j��
				R_Result_Selectino_Handle[0] = R_Result_Selectino_Handle[1] ;
			}
		}

}
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
	DrawString(0, 0, "�V�t�g�Ŏ��̉�ʂł�", GetColor(0, 255, 0));
	DrawString(0, 10, "�G���^�[�Ō���ł�", GetColor(255, 0, 0));
	



}

//�^�C�g���㏈��
void Result::FinResult()
{
	DeleteGraph(R_Result_Selectino_Handle[1]);	//�N���A�w�i�摜�j��
	if (R_Continue)	//�R���e�j���[�t���O��true�Ȃ�
	{
		g_CurrentSceneID = SCENE_ID_INIT_PLAY;	//�v���C�V�[���ɖ߂�
	}

	else if (R_BackTitle)	//�^�C�g���t���O��true�Ȃ�
	{
		g_CurrentSceneID = SCENE_ID_INIT_TITLE;	//�^�C�g���V�[���ɖ߂�
	}
	
}