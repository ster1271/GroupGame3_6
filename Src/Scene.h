#pragma once

enum SCENE_ID
{
	//�^�C�g���V�[����ID
	SCENE_ID_INIT_TITLE,		//�^�C�g��������
	SCENE_ID_LOOP_TITLE,		//�J��Ԃ�
	SCENE_ID_FIN_TITLE,			//�㏈��

	//�v���C�V�[����ID
	SCENE_ID_INIT_PLAY,		//�v���C������
	SCENE_ID_LOOP_PLAY,		//�v���C�J��Ԃ�
	SCENE_ID_FIN_PLAY,		//�v���C�㏈��

	//���U���g�V�[����ID
	SCENE_ID_INIT_RESULT,	//���U���g������
	SCENE_ID_LOOP_RESULT,	//���U���g�J��Ԃ�
	SCENE_ID_FIN_RESULT,	//���U���g�㏈��
};

//�������
enum WIN_STATE
{
	EMPTY,			//���Җ��m��
	PLAYER1_WIN,	//�v���C���[1����
	PLAYER2_WIN,	//�v���C���[2����
	CPU_WIN,		//CPU����
	DRAW			//��������
};

//���݂̃V�[��ID
extern  SCENE_ID g_CurrentSceneID;

//�������
extern WIN_STATE Get_Win;

//������������
extern int TileBreakNum[3];	
