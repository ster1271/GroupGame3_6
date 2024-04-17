#pragma once

//入力制御初期化
void InitInput();

//入力制御ステップ
//他のStepより早く呼ぶ
void StepInput();

//今押された
bool IsKeyPush(int Key_code);

//ずっと押されている
bool IsKeyKeep(int Key_code);

//キーを離した
bool IsKeyRelease(int Key_code);

//単純に押されているか
bool IsKeyDown(int Key_code);

