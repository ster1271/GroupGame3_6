
#include <DxLib.h>
#include "Effect.h"
#include "../Common.h"

/*
  �i�߂�菇
  1�F�G�t�F�N�g���\���̂�����������
  2�FInitEffect�֐�����������
  3�FLoadEffect�֐�����������
  4�FPlayEffect�֐�����������
  5�FDrawEffect�֐�����������@�������܂Ŏ����ł���Ώ����Ȃ��G�t�F�N�g����������
  6�FStepEffect�֐�����������
  7�FFinEffect�֐�����������

  ��������͎����̃Q�[���Ƀ\�[�X�t�@�C�����R�s�[���G�t�F�N�g���������Ă݂܂��傤!!
*/

//��x�ɕ\���ł���G�t�F�N�g�ő吔
#define EFFECT_MAX_NUM		(20)

//�G�t�F�N�g�̃A�j���ő吔
#define EFFECT_ANIME_MAX_NUM	(10)	

//�G�t�F�N�g���
struct EffectInfo
{
	EFFECT_TYPE	effectType;	//�G�t�F�N�g�̎��

	int	imghundle[EFFECT_ANIME_MAX_NUM];	//�摜�n���h��

	int x, y;		//���W
	bool isUse;		//�g�p�t���O

	int animeUsedNum;			//�A�j����
	int currentAnimeIndex;	//���݂̃A�j���ԍ�

	float changeTime;		//�P��������̕\������
	float currentAnimeTime;	//���݂̃A�j������
};

//�G�t�F�N�g���
EffectInfo effectInfo[EFFECT_MAX_NUM];

//�G�t�F�N�g�̃t�@�C���p�X
const char effectFilePath[EFFECT_TYPE_NUM][256] =
{
	"Data/Effect/Effect����.png",		//EFFECT_TYPE_EXPLOSION
	"Data/Effect/Effect��.png",		//EFFECT_TYPE_RECOVERY
	"Data/Effect/Effect�a��.png",		//EFFECT_TYPE_SLASH
	"Data/Effect/EffectExplosion.png",	//EFFECT_TYPE_DOWNEXPLOSION
	
};

//�e�G�t�F�N�g�̃A�j����
const int effectAnimeImgNum[EFFECT_TYPE_NUM] =
{
	5,	//EFFECT_TYPE_EXPLOSION
	8,	//EFFECT_TYPE_RECOVERY
	5,	//EFFECT_TYPE_SLASH
	4,  //EFFECT_TYPE_DOWNEXPLOSION
};

//�e�G�t�F�N�g�̉摜������ [0] = x, [1] = y
const int effectImageSplitNum[EFFECT_TYPE_NUM][2] =
{
	{ 5, 1,},	//EFFECT_TYPE_EXPLOSION
	{ 8, 1,},	//EFFECT_TYPE_RECOVERY
	{ 5, 1,},	//EFFECT_TYPE_SLASH
	{ 2, 2,},	//EFFECT_TYPE_DOWNEXPLOSION
};

//�G�t�F�N�g�̉摜�T�C�Y
const int effectImageSize[EFFECT_TYPE_NUM] =
{
	120,	//EFFECT_TYPE_EXPLOSION
	120,	//EFFECT_TYPE_RECOVERY
	120,	//EFFECT_TYPE_SLASH
	64,		//EFFECT_TYPE_DOWNEXPLOSION
};

//�e�G�t�F�N�g�̃A�j���摜�؂�ւ�����
const float effectChageTime[EFFECT_TYPE_NUM] =
{
	0.1f,	//EFFECT_TYPE_EXPLOSION
	0.1f,	//EFFECT_TYPE_RECOVERY
	0.05f,	//EFFECT_TYPE_SLASH
	0.05f,	//EFFECT_TYPE_DOWNEXPLOSION
};

//�G�t�F�N�g�̓ǂݍ���
//����	�F�G�t�F�N�g�̎�ށA�쐬��
void LoadEffect(EFFECT_TYPE type, int create_num)
{
	for (int effectnum = 0; effectnum < create_num; effectnum++)
	{
		for (int effectIndex = 0; effectIndex < EFFECT_MAX_NUM; effectIndex++)
		{
			//���ǂݍ��݂��Ă��Ȃ��G�t�F�N�g����������
			//���i�ЂƂڂ̉摜�n���h�����[���Ȃ�ǂݍ��݂���ĂȂ��j
			if (effectInfo[effectIndex].imghundle[0] == 0)
			{
				//�e�G�t�F�N�g�̃A�j����
				int AnimeImgNum = effectAnimeImgNum[type];

				//�e�G�t�F�N�g�̉摜������
				int ImageSplitNumX = effectImageSplitNum[type][0];
				int ImageSplitNumY = effectImageSplitNum[type][1];

				//�G�t�F�N�g�̉摜�T�C�Y
				int ImageSize = effectImageSize[type];

				//���摜�𕪊��ǂݍ���
				int success_flg = LoadDivGraph(effectFilePath[type], AnimeImgNum, ImageSplitNumX, ImageSplitNumY,
					ImageSize, ImageSize, effectInfo[effectIndex].imghundle);

				//��������
				if (success_flg == 0)
				{
					//���A�j�������i�[
					effectInfo[effectIndex].animeUsedNum = AnimeImgNum;

					//���P��������̕\�����Ԃ�ݒ�
					effectInfo[effectIndex].changeTime = effectChageTime[type];

					//���G�t�F�N�g�̎�ނ�ݒ�
					effectInfo[effectIndex].effectType = type;
				}

				//�����ۂɂ�����炸������
				break;
			}
		}
	}
}

//�G�t�F�N�g�̏�����
void InitEffect()
{
	//�����ׂẴG�t�F�N�g���̕ϐ����N���A����i�[���ɂ���j
	for (int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++)
	{
		effectInfo[effect_index].x = 0;
		effectInfo[effect_index].y = 0;
		effectInfo[effect_index].animeUsedNum = 0;
		effectInfo[effect_index].currentAnimeIndex = 0;
		effectInfo[effect_index].changeTime = 0.0f;
		effectInfo[effect_index].currentAnimeTime = 0.0f;
		effectInfo[effect_index].isUse = false;
		//effectInfo[effect_index].effectType = EFFECT_TYPE_EXPLOSION;

		for (int i = 0; i < EFFECT_ANIME_MAX_NUM; i++)
		{
			effectInfo[effect_index].imghundle[i] = 0;
		}
	}
}

//�G�t�F�N�g�ʏ폈��
void StepEffect()
{
	for (int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++)
	{
		
		if (effectInfo[effect_index].isUse)
		{
			//���g�p���Ȃ�A�j�����Ԃ��o�߂����āA�A�j���ԍ����X�V����
			if (effectInfo[effect_index].currentAnimeTime >= effectInfo[effect_index].changeTime)
			{
				//���摜�؂�ւ��ɕK�v�Ȏ��Ԍo�߂�����

				//�����̉摜��
				effectInfo[effect_index].currentAnimeIndex++;

				//���v�����ԃ��Z�b�g
				effectInfo[effect_index].currentAnimeTime = 0.0f;
				
				//�����̉摜�����������Ȃ�
				if (effectInfo[effect_index].currentAnimeIndex >= effectInfo[effect_index].animeUsedNum)
				{
					//���g�p���t���O��OFF��
					effectInfo[effect_index].isUse = false;
					//���ȉ��̏����͕s�v
					continue;
				}
			}

			//�����ԍX�V
			effectInfo[effect_index].currentAnimeTime += 1.0f / FRAME_RATE;
		}
	}		
}

//�G�t�F�N�g�`�揈��
void DrawEffect(int screenx, int screeny)
{
	for(int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++)
	{
		if (effectInfo[effect_index].isUse)
		{
			int x = effectInfo[effect_index].x - screenx;
			int y = effectInfo[effect_index].y - screeny;
			int hundleIndex = effectInfo[effect_index].currentAnimeIndex;
			int imgHundle = effectInfo[effect_index].imghundle[hundleIndex];
			//���g�p���Ȃ猻�݂̃A�j���ԍ��ŕ`�悷��
			DrawRotaGraph(x/* - screenx*/, y/* - screeny*/, 3.0f, 0.0f, imgHundle, true);
		}
	}
}

//�G�t�F�N�g�̌㏈��
void FinEffect()
{
	//�����ׂẴG�t�F�N�g���폜����
	for (int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++)
	{
		//�����ׂč폜����
		for (int image_index = 0; image_index < EFFECT_MAX_NUM; image_index++)
		{
			//���[���ȊO�Ȃ�폜����
			if (effectInfo[effect_index].imghundle[image_index] != 0)
			{
				//���摜�폜������ݒ肷��
				DeleteGraph(effectInfo[effect_index].imghundle[image_index]);

				//���폜������[�������Ă���
				effectInfo[effect_index].imghundle[image_index] = 0;
			}
				
		}
	}
}

//�G�t�F�N�g�̍Đ�
//����	�F�G�t�F�N�g�̎��, �w���W, �x���W, �P��������̕\������
void PlayEffect(EFFECT_TYPE type, int x, int y)
{
	//�����g�p�G�t�F�N�g��T���čĐ�
	for (int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++)
	{
		//���g�p���Ȃ�ȉ��s��Ȃ�
		if (!effectInfo[effect_index].isUse)
		{
			//���^�C�v����v����
			if (effectInfo[effect_index].effectType == type)
			{
				//�����W�ݒ�
				effectInfo[effect_index].x = x;
				effectInfo[effect_index].y = y;

				//���v���p�̕ϐ����N���A
				effectInfo[effect_index].currentAnimeIndex = 0;		//���݂̃A�j���ԍ�
				effectInfo[effect_index].currentAnimeTime = 0.0f;	//���݂̃A�j������
				
				//���g�p���ɂ���
				effectInfo[effect_index].isUse = true;

				//��������
				break;
			}
		}
	}
}
