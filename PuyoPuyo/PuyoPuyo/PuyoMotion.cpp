#include "stdafx.h"
#include "PuyoMotion.h"
#include "Display.h"
//#include "Setting.h"
#include "PuyoVar.h"

//オブジェクト判定関数
bool ObjectJudge(int puyoX, int puyoY, int puyoRot) {

	//軸ぷよ壁判定
	if (field[puyoY][puyoX] != NONE) {
		return true;
	}

	//回転後のサブぷよの座標x,y
	int subpuyoX = puyoX + puyoPosition[puyoRot][0];
	int subpuyoY = puyoY + puyoPosition[puyoRot][1];

	//サブぷよ壁判定
	if (field[subpuyoY][subpuyoX] != NONE) {
		return true;
	}

	return false;

}

//同じぷよが何個連結しているか判定する関数
int PuyoCount(int x, int y, int type, int count) {
	if (check[y][x] || field[y][x] != type) {
		return count;
	}

	count++;
	check[y][x] = true;

	//上下左右チェック(再帰で全画面チェック)
	for (int i = 0; i < ROT_MAX; i++) {
		int _x = x + puyoPosition[i][0];
		int _y = y + puyoPosition[i][1];
		count = PuyoCount(_x, _y, type, count);
	}

	return count;
}

//ぷよが4個以上で消える関数
void PuyoErase(int x, int y, int  type) {
	

	if (field[y][x] != type) {
		
		return;
	}

	field[y][x] = NONE;

	//上下左右の同じぷよを消す（再帰）
	for (int i = 0; i < ROT_MAX; i++) {
		int _x = x + puyoPosition[i][0];
		int _y = y + puyoPosition[i][1];
		PuyoErase(_x, _y, type);
	}
}