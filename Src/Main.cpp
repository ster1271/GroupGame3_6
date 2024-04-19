//�E�B���h�E��\������v���O�����i�ЂȌ`�j

#include "DxLib.h"	//DX���C�u�����̃C���N���[�h
#include "Scene.h"
#include "Common.h"
#include "Scene/SceneTitle.h"
#include "Scene/ScenePlay.h"
#include "Scene/SceneResult.h"
#include "Input/Input.h"

//�ݒ�t���[�����[�g�@(60FPS)
#define FRAME_RATE	(60)

//1�t���[�����[�g�̎���(�~���b)
#define FRAME_TIME (1000 / FRAME_RATE)

struct FrameRateInfo
{
	int currentTime;	//���݂̎���
	int LastFrameTime;	//�O��̃t���[�����s���̎���
	int g_count;			//�t���[���J�E���g�p
	int calcFpsTime;	//FPS���v�Z��������
	float fps;			//�v�Z����FPS(�\���p)
};

//�t���[�����[�g���ϐ�
FrameRateInfo frameRateInfo;

//FPS�v�Z
void CalcFPS();

//FPS�\��(�f�o�b�N�p�j
void DrawFPS();

//�V�[���Ǘ��ϐ�
SCENE_ID g_CurrentSceneID = SCENE_ID_INIT_TITLE;

//������ԊǗ��ϐ�
WIN_STATE Get_Win = EMPTY;

//���̊���������(�o�Ă���l�����p�ӂ��Ă�(player1, player2, cpu))
int TileBreakNum[3];

// Win32�A�v���P�[�V������ WinMain�֐� ����n�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�̏�Ԃ�ݒ肷��
	ChangeWindowMode(true);

	//DX���C�u�����̏�����
	if (DxLib_Init() == -1) {
		return -1;
	}

	// ��ʃT�C�Y��ύX
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//�`�悷��X�N���[����ݒ肷��
	SetDrawScreen(DX_SCREEN_BACK);
	
	//-----------------------------------------
	//��ԍŏ��ɂP�񂾂���鏈���������ɏ���

	//�V�[���N���X�̐錾
	Title title;
	Play play;
	Result result;

	//-----------------------------------------

	//�Q�[�����C�����[�v
	while (ProcessMessage() != -1)
	{
		Sleep(1);	//�V�X�e��������Ԃ�

		//���݂̎��Ԃ��擾
		frameRateInfo.currentTime = GetNowCount();

		//�ŏ��̃��[�v�Ȃ�
		//���݂̎��Ԃ��AFPS�̌v�Z���������Ԃɐݒ�
		if (frameRateInfo.calcFpsTime == 0.0f)
		{
			frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
			frameRateInfo.fps = (float)FRAME_RATE;
		}

		//���݂̎��Ԃ��A�O��̃t���[�������
		//1000/60�~���b�i1/60�j�ȏ�o�߂��������珈�������s����
		if (frameRateInfo.currentTime - frameRateInfo.LastFrameTime >= FRAME_TIME)
		{
			//�t���[�����s���̎��Ԃ��X�V
			frameRateInfo.LastFrameTime = frameRateInfo.currentTime;

			//�t���[�������J�E���g
			frameRateInfo.g_count++;

			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				//�G�X�P�[�v�L�[�������ꂽ��I��
				break;
			}

			//��ʂɕ\�����ꂽ���̂��������i�P���[�v�̂P�x�����s���j
			ClearDrawScreen();

			//���͐���X�e�b�v
			StepInput();

			switch (g_CurrentSceneID) 
			{
				/*==============�^�C�g���V�[��=============*/
				case SCENE_ID_INIT_TITLE:
				{
					//�^�C�g��������
					title.InitTitle();

				}//SCENE_ID_INIT_TITLE�I���̊���
				break;

				case SCENE_ID_LOOP_TITLE:
				{
					//�^�C�g���ʏ폈��
					title.StepTitle();

					//�^�C�g���`�揈��
					title.DrawTitle();

				}//SCENE_ID_LOOP_TITLE�I���̊���
				break;

				case SCENE_ID_FIN_TITLE:
				{
					//�^�C�g���㏈��
					title.FinTitle();

				}//SCENE_ID_FIN_TITLE�I���̊���
				break;

				
				/*==============�v���C�V�[��=============*/
				case SCENE_ID_INIT_PLAY:
				{
					//�v���C������
					play.InitPlay();

				}//SCENE_ID_INIT_PLAY�I���̊���
				break;
				case SCENE_ID_LOOP_PLAY:
				{
					//�v���C�ʏ폈��
					play.StepPlay();

					//�v���C�`�揈��
					play.DrawPlay();

				}//SCENE_ID_LOOP_RESULT�I���̊���
				break;
				case SCENE_ID_FIN_PLAY:
				{
					//�v���C�㏈��
					play.FinPlay();
				}
				break;

				
				/*==============���U���g�V�[��=============*/
				case SCENE_ID_INIT_RESULT:
				{
					//���U���g������
					result.InitResult();

				}//SCENE_ID_INIT_RESULT�I���̊���
				break;

				case SCENE_ID_LOOP_RESULT:
				{
					//���U���g�ʏ폈��
					result.StepResult();

					//���U���g�`�揈��
					result.DrawResult();

				}//SCENE_ID_LOOP_RESULT�I���̊���
				break;

				case SCENE_ID_FIN_RESULT:
				{
					//���U���g�㏈��
					result.FinResult();
				}
				break;
				
			}

			
			//FPS�v�Z
			CalcFPS();

			//FPS�\��
			DrawFPS();

			//�t���b�v�֐��i���[�v�̏I���ɂP�x�����s���j
			ScreenFlip();
			
			

		}//�t���[�����[�g��if���̏I���

	}//���C�����[�v�̏I���

	//-----------------------------------------
	//�Ō�ɂP�񂾂���鏈���������ɏ���


	//-----------------------------------------
	//DX���C�u�����̌㏈��
	DxLib_End();

	return 0;
}

void CalcFPS()
{
	//�O���FPS���v�Z�������Ԃ���o�ߎ��Ԃ����߂�
	int difTime = frameRateInfo.currentTime - frameRateInfo.calcFpsTime;

	//�O���FPS���v�Z�������Ԃ���
	//�P�b�ȏ�o�߂��Ă�����FPS���v�Z����
	if (difTime > 1000)
	{
		//�t���[���񐔂��~���b�ɍ��킹��
		//�����܂ŏo�������̂�float�ɃL���X�g
		float frameCount = (float)(frameRateInfo.g_count * 1000.0f);

		//FPS�����߂�
		//���z�̐��l��6000/1000��60�ƂȂ�
		frameRateInfo.fps = frameCount / difTime;

		//�t���[���J�E���g���N���A
		frameRateInfo.g_count = 0;

		//FPS���v�Z�������Ԃ��X�V
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
	}
}

void DrawFPS()
{
	DrawFormatString(SCREEN_SIZE_X - 90, SCREEN_SIZE_Y - 20, GetColor(255, 30, 30), "FPS[%.2f]", frameRateInfo.fps);
}

