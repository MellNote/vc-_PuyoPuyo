#include "stdafx.h"
#include "PuyoMotion.h"
#include "Display.h"
#include "Setting.h"
#include "PuyoVar.h"

text Text;	//構造体宣言

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

	int cnt = 0;
	
	for (int x = 0; x < FIELD_W; x++) {
		if (field[1][x] != NONE) {
			cnt++;
		}
	}
	
	if (cnt >=3) {
		end_key = 1;
	}
	else {
		cnt = 0;
	}
	printf("\n");
	printf("%s%d\n", "現在チェイン数：",chainPuyo);
	printf("\n");
	printf("%s%d\n", "最大チェイン数：", maxchain);

	//操作方法描画
	printf("\n");
	printf("%s\n", "【操作方法】");
	printf("%s\n", Text.operation);

	//バージョン描画
	printf("\n");
	printf("%s\n", "【バージョン】");
	printf("%s\n", Text.version);

}