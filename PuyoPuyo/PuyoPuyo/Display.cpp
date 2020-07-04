#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"
#include "Display.h"
#include "PuyoVar.h"

//画面再描画関数
void Display() {

	//画面クリア
	system("cls");

	//フィールド情報コピー
	memcpy(fieldcpy, field, sizeof field);

	//操作制限されていない場合
	if (!user_stop) {

		//回転後のサブぷよの座標x,y
		int subpuyoX = puyoX + puyoPosition[puyoRot][0];
		int subpuyoY = puyoY + puyoPosition[puyoRot][1];

		//軸・サブぷよの情報コピー
		fieldcpy[puyoY][puyoX] = puyoType + PUYO_0;
		fieldcpy[subpuyoY][subpuyoX] = subpuyoType + PUYO_0;

	}

	//フィールド再描画
	for (int y = 1; y < FIELD_H; y++) {
		for (int x = 0; x < FIELD_W; x++) {
			printf("%s", minotype[fieldcpy[y][x]]);
		}
		printf("\n");
	}
}