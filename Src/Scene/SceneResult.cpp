#include "DxLib.h"
#include "../Scene.h"
#include "SceneResult.h"
#include "../Input/Input.h"
#include <string>

int R_Result_Selectino_Handle[2];
int R_Result_Frame_Handle;
int R_Result_Sucoa;
int NumberFontHndle[10];

int R_ResultPoxX; //���W

bool R_Continue;	//�R���e�j���[�t���O

bool R_BackTitle;	//�^�C�g���t���O

bool R_Wins_Score; //�摜�؂�ւ�

int images[WIN_RLSULT]; // �摜���i�[����z��
int currentImageIndex = 0; // ���݂̉摜�̃C���f�b�N�X

void Result::InitResult()
{
    R_Result_Selectino_Handle[0] = LoadGraph(RISULT_WIN_SCORE);
    R_Result_Selectino_Handle[1] = LoadGraph(RISULT_SELECTION);
    R_Result_Frame_Handle = LoadGraph(RISULT_FRAME);
    R_Result_Sucoa = LoadGraph(ROSILT_SUCOA);
    NumberFontHndle[10] = { 0 };
    LoadDivGraph("Data/ClearImage/number.png", 10, 10, 1, 200, 200, NumberFontHndle);
    R_ResultPoxX = 150;
    R_Wins_Score = false;
    R_Continue = false;
    R_BackTitle = false;
    g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}
void Result::StepResult()
{
    if (IsKeyPush(KEY_INPUT_SPACE))
    {
        R_Wins_Score = true;
        if (R_Wins_Score) {
            DeleteGraph(currentImageIndex);
            R_Result_Selectino_Handle[0] = R_Result_Selectino_Handle[1];
        }
    }
    if (IsKeyPush(KEY_INPUT_A) || IsKeyPush(KEY_INPUT_LEFT))
    {
        if (R_ResultPoxX == 650)
        {
            R_ResultPoxX = 150;
        }
    }
    else if (IsKeyPush(KEY_INPUT_D) || IsKeyPush(KEY_INPUT_RIGHT))
    {
        if (R_ResultPoxX == 150)
        {
            R_ResultPoxX = 650;
        }
    }
    else if (IsKeyPush(KEY_INPUT_RETURN))
    {
        if (R_ResultPoxX == 150)
        {
            R_Continue = true;
        }
        else if (R_ResultPoxX == 650)
        {
            R_BackTitle = true;
        }
        g_CurrentSceneID = SCENE_ID_FIN_RESULT;
    }
}
void Result::DrawResult()
{
    // ���̑��̕`�揈�����s��
    DrawGraph(0, 0, R_Result_Selectino_Handle[0], true);
    DrawString(0, 0, "�V�t�g�Ŏ��̉�ʂł�", GetColor(255, 0, 0));
    DrawString(0, 20, "�G���^�[�Ō���ł�", GetColor(255, 0, 0));
    // �����̃s�N�Z���摜��ǂݍ���
    int numberImageHandle = LoadGraph(ROSILT_SUCOA);
    // PlayerBreakTile �̐������s�N�Z���ŕ`��
    // �s�N�Z���̐����̕��ƍ���
    const int digitWidth = 200;
    const int digitHeight = 190;
    // �����̓��_�𕶎���ɕϊ�
    std::string scoreString = std::to_string(PlayerBreakTile);
    // �����̃s�N�Z���摜��ǂݍ���ŕ`��
    int posX = 400; // �`�悷��X���W
    for (char& digit : scoreString) {
        // �e�����̃s�N�Z���摜��`��
        int digitValue = digit - '0'; // �����𐔒l�ɕϊ�
        DrawRectGraph(posX, 500, digitValue * digitWidth, 0, digitWidth, digitHeight, numberImageHandle, true);
        // ���̐����̕`��ʒu��ݒ�
        posX += digitWidth;
    }
    // �����̃s�N�Z���摜�̉��
    DeleteGraph(numberImageHandle);
}
void Result::FinResult()
{
    DeleteGraph(R_Result_Selectino_Handle[1]);
    if (R_Continue)
    {
        g_CurrentSceneID = SCENE_ID_INIT_PLAY;
    }
    else if (R_BackTitle)
    {
        g_CurrentSceneID = SCENE_ID_INIT_TITLE;
    }
}





