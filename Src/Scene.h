#pragma once

enum SCENE_ID
{
	//タイトルシーンのID
	SCENE_ID_INIT_TITLE,		//タイトル初期化
	SCENE_ID_LOOP_TITLE,		//繰り返し
	SCENE_ID_FIN_TITLE,			//後処理

	//プレイシーンのID
	SCENE_ID_INIT_PLAY,		//プレイ初期化
	SCENE_ID_LOOP_PLAY,		//プレイ繰り返し
	SCENE_ID_FIN_PLAY,		//プレイ後処理

	//リザルトシーンのID
	SCENE_ID_INIT_RESULT,	//リザルト初期化
	SCENE_ID_LOOP_RESULT,	//リザルト繰り返し
	SCENE_ID_FIN_RESULT,	//リザルト後処理
};

//現在のシーンID
extern  SCENE_ID g_CurrentSceneID;
