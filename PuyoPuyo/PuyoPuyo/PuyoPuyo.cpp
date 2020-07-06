#include "stdafx.h"
#include "PuyoMotion.h"
#include "Display.h"
#include "Setting.h"
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

//ぷよの種類（NONE,WALL,PUYO_0,PUYO_1,PUYO_2,PUYO_3）
//【補足】全角文字は2バイト+1バイト(null)=3バイトで表される。
char minotype[][3] = { "・","■","〇","△","☆","◎" };

int puyoX = START_X;	//ぷよの座標x
int puyoY = START_Y;	//ぷよの座標y
int puyoType;		//軸ぷよの種類
int subpuyoType;	//サブぷよの種類
int puyoRot;		//ぷよの回転
int chainPuyo = 0;	//消したぷよの数
int maxchain = 0;	//最大チェイン数
int rotnum = 16000;	//回転時に用いる適当な大きな値
int end_key;	//終了フラグ

bool user_stop = false;	//操作制限フラグ

int main(){

	//現在のディレクトリ取得
	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);

	//iniファイルのパラメータ取得に用いる文字列配列
	char info[CHARBUFF];
	char info2[CHARBUFF];
	char info3[CHARBUFF];
	char settingFile[CHARBUFF];

	//iniファイルのパラメータ取得
	sprintf_s(settingFile, "%s\\Text.ini", currentDirectory);
	readChar("puyopuyo", "keyword1", "none", info, settingFile);
	Text.version = info;
	readChar("puyopuyo", "keyword2", "none", info2, settingFile);
	Text.operation = info2;
	readChar("filename", "keyword3", "none", info3, settingFile);
	Text.filename = info3;

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

				//最大チェイン数更新
				if (chainPuyo > maxchain) {
					maxchain = chainPuyo;
				}

				chainPuyo = 0;	//チェイン数初期化

				//地面までぷよ落下
				if (!ObjectJudge(puyoX, puyoY + 1, puyoRot)) {
					puyoY++;
				}

				else {

					//サブぷよの座標更新
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
									chainPuyo++;	//チェイン数カウント
									user_stop = true;
								}
							}
						}
					}
				}
				
			}
			
			Display();	//画面再描画
		}

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
				case 'f':end_key = 1; break;	//終了
				}
			
				//オブジェクトじゃなければ座標更新
				if (ObjectJudge(x, y, rot) != true) {
					puyoX = x;
					puyoY = y;
					puyoRot = rot;
				}
				Display();	//画面再描画
			}
		}

		

		//無限ループ終了
		if (end_key == 1) {
			FileOutput(Text.filename, maxchain);	//ファイル出力
			break;
		}
	}

	return 0;

}