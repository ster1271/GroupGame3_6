#include "DxLib.h"
#include "../Scene.h"
#include "SceneResult.h"
#include "../Input/Input.h"

int R_Result_Selectino_Handle[2];
int R_Result_Frame_Handle;
int R_Result_Sucoa;
int NumberFontHndle[10];

int R_ResultPoxX; //座標

bool R_Continue;	//コンテニューフラグ

bool R_BackTitle;	//タイトルフラグ

bool R_Wins_Score; //画像切り替え

int images[WIN_RLSULT]; // 画像を格納する配列
int currentImageIndex = 0; // 現在の画像のインデックス

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
    // 数字のピクセル画像を読み込む
    int numberImageHandle = LoadGraph(ROSILT_SUCOA);
    // 数字のピクセル画像を描画
    DrawGraph(150, 100, numberImageHandle, true);
    // PlayerBreakTile の数字を描画
    DrawFormatString(650, 600, GetColor(255, 0, 0), "%d", PlayerBreakTile);
    // 数字のピクセル画像の解放
    DeleteGraph(numberImageHandle);

    // その他の描画処理を行う
    DrawGraph(0, 0, R_Result_Selectino_Handle[0], true);
    DrawString(0, 0, "シフトで次の画面です", GetColor(255, 0, 0));
    DrawString(0, 20, "エンターで決定です", GetColor(255, 0, 0));

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





