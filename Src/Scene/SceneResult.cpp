#include "DxLib.h"
#include "../Scene.h"
#include "SceneResult.h"
#include "../Input/Input.h"
#include <string>

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
    // その他の描画処理を行う
    DrawGraph(0, 0, R_Result_Selectino_Handle[0], true);
    DrawString(0, 0, "シフトで次の画面です", GetColor(255, 0, 0));
    DrawString(0, 20, "エンターで決定です", GetColor(255, 0, 0));
    // 数字のピクセル画像を読み込む
    int numberImageHandle = LoadGraph(ROSILT_SUCOA);
    // PlayerBreakTile の数字をピクセルで描画
    // ピクセルの数字の幅と高さ
    const int digitWidth = 200;
    const int digitHeight = 190;
    // 数字の得点を文字列に変換
    std::string scoreString = std::to_string(PlayerBreakTile);
    // 数字のピクセル画像を読み込んで描画
    int posX = 400; // 描画するX座標
    for (char& digit : scoreString) {
        // 各数字のピクセル画像を描画
        int digitValue = digit - '0'; // 文字を数値に変換
        DrawRectGraph(posX, 500, digitValue * digitWidth, 0, digitWidth, digitHeight, numberImageHandle, true);
        // 次の数字の描画位置を設定
        posX += digitWidth;
    }
    // 数字のピクセル画像の解放
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





