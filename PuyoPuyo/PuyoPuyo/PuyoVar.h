#pragma once

#define FIELD_W 8	//フィールドの横幅
#define FIELD_H 14	//フィールドの縦幅

#define START_X 3	//ぷよの初期座標x
#define START_Y 1	//ぷよの初期座標y

#define PUYO_TYPE 4	//ぷよの種類数

//ぷよの種類宣言
extern enum cell{
	NONE,WALL,PUYO_0,PUYO_1,PUYO_2,PUYO_3
};

//ぷよの回転角宣言
extern enum rad{
	ROT_0, ROT_90, ROT_180, ROT_270, ROT_MAX
};

//ぷよの回転後の位置（ROT_0, ROT_90, ROT_180, ROT_270, ROT_MAX）
extern int puyoPosition[][2];

extern int field[FIELD_H][FIELD_W];	//フィールド情報
extern int fieldcpy[FIELD_H][FIELD_W]; //フィールド情報コピー
extern int check[FIELD_H][FIELD_W];	//チェック用フラグ

//終了キー
extern int end_key;

//構造体
extern struct text {
	char* version;
	char* operation;
	char* filename;
};

extern text Text;

//ぷよの種類（NONE,WALL,MINO_0,MINO_1,MINO_2,MINO_3）
extern char minotype[][3];

extern int puyoX;	//ぷよの座標x
extern int puyoY;	//ぷよの座標y
extern int puyoType;		//軸ぷよの種類
extern int subpuyoType;	//サブぷよの種類
extern int puyoRot;		//ぷよの回転
extern int rotnum;	//回転時に用いる適当な大きな値
extern int chainPuyo;	//消したぷよの数
extern int maxchain;

extern bool user_stop;	//操作制限