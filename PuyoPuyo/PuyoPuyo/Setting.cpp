#include "stdafx.h"
#include "Setting.h"

//ファイル読み込み（int）
int readInt(const char *section, const char *keyword, int defaultValue, const char *filePath) {
	char valueString[CHARBUFF];
	if (readChar(section, keyword, "", valueString, filePath)) {
		return atof(valueString);
	}
	else {
		return defaultValue;
	}
}

//ファイル読み込み（double）
double readDouble(const char *section, const char *keyword, double defaultValue, const char *filePath) {
	char valueString[CHARBUFF];
	char *endptr;
	if (readChar(section, keyword, "", valueString, filePath)) {
		return strtod(valueString, &endptr);
	}
	else {
		return defaultValue;
	}
}

//ファイル読み込み（char）
bool  readChar(const char *section, const char *keyword, const char *defaultValue, char *returnValue, const char *filePath) {
	if (GetPrivateProfileString(section, keyword, defaultValue, returnValue, CHARBUFF, filePath) != 0) {
		return true;
	}
	else {
		return false;
	}
}

//現在のディレクトリ取得
void getCurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

//ファイル書き込み（char）
bool writeChar(const char *section, const char *keyword, const char *returnValue, const char *filePath) {
	return WritePrivateProfileString(section, keyword, returnValue, filePath);
}

//ファイル書き込み（int）
bool writeInt(const char *section, const char *keyword, int returnValue, const char *filePath) {
	char valueChar[CHARBUFF];
	sprintf_s(valueChar, "%d", returnValue);
	return writeChar(section, keyword, valueChar, filePath);
}

//ファイル書き込み（double）
bool writeDouble(const char *section, const char *keyword, double returnValue, const char *filePath) {
	char valueChar[CHARBUFF];
	sprintf_s(valueChar, "%lf", returnValue);
	return writeChar(section, keyword, valueChar, filePath);
}

//最大チェイン数を出力する関数
void FileOutput(const char* fileName, int maxchain) {
	FILE* fp;
	errno_t error;
	double sum = 0;

	error = fopen_s(&fp, fileName, "w");

	if (error != 0) {
		fprintf_s(stderr, "failed to open");
	}
	else {
		fprintf(fp, "最大チェイン数：%d", maxchain);
		}
	fclose(fp);
	}
	

