﻿#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <Windows.h>
#include "PuyoMotion.h"
#include "Display.h"
#include "Setting.h"
#include "stdafx.h"
#include "PuyoVar.h"

#define FIELD_W 8	//フィールドの横幅
#define FIELD_H 14	//フィールドの縦幅

#define START_X 3	//ぷよの初期座標x
#define START_Y 1	//ぷよの初期座標y

#define PUYO_TYPE 4	//ぷよの種類数

//ぷよの種類宣言
enum cell;

//ぷよの回転角宣言
enum rad;

//ぷよの回転後の位置（ROT_0, ROT_90, ROT_180, ROT_270, ROT_MAX）
int puyoPosition[][2] = { {0,-1},{-1,0},{0,1},{1,0}	};

int field[FIELD_H][FIELD_W];	//フィールド情報
int fieldcpy[FIELD_H][FIELD_W]; //フィールド情報コピー
int check[FIELD_H][FIELD_W];	//チェック用フラグ

//ぷよの種類（NONE,WALL,MINO_0,MINO_1,MINO_2,MINO_3）
char minotype[][3] = { "・","■","〇","△","☆","◎" };

int puyoX = START_X;	//ぷよの座標x
int puyoY = START_Y;	//ぷよの座標y
int puyoType;		//軸ぷよの種類
int subpuyoType;	//サブぷよの種類
int puyoRot;		//ぷよの回転
int rotnum = 16000;	//回転時に用いる適当な大きな値

bool user_stop = false;	//操作制限

int main(){

	//乱数初期化
	srand((unsigned int)time(NULL));

	//壁配置（たて）
	for (int y = 0; y < FIELD_H; y++) {
		field[y][0] = WALL;
		field[y][FIELD_W-1] = WALL;
	}

	//壁配置（よこ）
	for (int x = 0; x < FIELD_W; x++) {
		field[FIELD_H-1][x] = WALL;
	}

	//ぷよの種類をランダム
	puyoType = rand() % PUYO_TYPE;
	subpuyoType = rand() % PUYO_TYPE;

	time_t t = 0;	//時間を扱う変数

	while (1) {

		//tが現時刻より小さい場合、画面の再描画
		if (t < time(NULL)) {
			t = time(NULL);	//タイム更新（1秒ごとに更新）


			//操作制限されていない場合
			if (!user_stop) {

				//地面までぷよ落下
				if (ObjectJudge(puyoX, puyoY + 1, puyoRot) != true) {
					puyoY++;
				}
				else {

					int subpuyoX = puyoX + puyoPosition[puyoRot][0];
					int subpuyoY = puyoY + puyoPosition[puyoRot][1];

					//地面到達時にぷよをフィールドに書き込む
					field[puyoY][puyoX] = PUYO_0 + puyoType;
					field[subpuyoY][subpuyoX] = PUYO_0 + subpuyoType;

					//ぷよの座標・角度・種類リセット
					puyoX = START_X;
					puyoY = START_Y;
					puyoRot = ROT_0;
					puyoType = rand() % PUYO_TYPE;
					subpuyoType = rand() % PUYO_TYPE;

					user_stop = true;	//操作制限する

				}
			}

			//ぷよの落下モーション
			if (user_stop) {
				user_stop = false;
				for (int y = FIELD_H - 3; y >= 0; y--) {
					for (int x = 1; x < FIELD_W - 1; x++) {
						if ((field[y][x] != NONE)&&(field[y+1][x]==NONE)) {
							field[y + 1][x] = field[y][x];
							field[y][x] = NONE;
							user_stop = true;
						}
					}
				}

				//ぷよの4連結以上(消える)モーション
				if (!user_stop) {
					memset(check, 0, sizeof check);
					for (int y = 0; y < FIELD_H - 1; y++) {
						for (int x = 1; x < FIELD_W - 1; x++) {
							if (field[y][x] != NONE) {
								if (PuyoCount(x, y, field[y][x], 0) >= 4) {
									PuyoErase(x, y, field[y][x]);
									user_stop = true;
								}
							}
						}
					}
				}
			}

			Display();	//画面再描画
		}

		//終了キー
		int end_key = 0;

		//キー入力
		if (_kbhit()) {

			//操作制限されている場合
			if (user_stop) {
				_getch();
			}

			//操作制限されていない場合
			else {

				//オブジェクト判定時に用いる仮想ぷよ
				int x = puyoX;
				int y = puyoY;
				int rot = puyoRot;

				//ぷよの移動・回転処理
				switch (_getch()) {
				//case 'w':y--; break;	//上（デバッグ用）
				case 's':y++; break;	//下
				case 'a':x--; break;	//左
				case 'd':x++; break;	//右
				case 'e':rot = (--rotnum) % ROT_MAX; break;	//右回転（時計回り）
				case 'q':rot = (++rotnum) % ROT_MAX; break;	//左回転（反時計回り）
				}

				//オブジェクトじゃなければ座標更新
				if (ObjectJudge(x, y, rot) != true) {
					puyoX = x;
					puyoY = y;
					puyoRot = rot;
				}
				Display();	//画面再描画
			}

			//ゲーム終了キー
			switch (_getch()) {
			case 'f':end_key = 1; break;	//終了
			}
		}

		//無限ループ終了
		if (end_key == 1) {
			break;
		}

	}

	return 0;

}

