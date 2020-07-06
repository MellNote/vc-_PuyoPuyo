#include "stdafx.h"
#include "Setting.h"

//�t�@�C���ǂݍ��݁iint�j
int readInt(const char *section, const char *keyword, int defaultValue, const char *filePath) {
	char valueString[CHARBUFF];
	if (readChar(section, keyword, "", valueString, filePath)) {
		return atof(valueString);
	}
	else {
		return defaultValue;
	}
}

//�t�@�C���ǂݍ��݁idouble�j
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

//�t�@�C���ǂݍ��݁ichar�j
bool  readChar(const char *section, const char *keyword, const char *defaultValue, char *returnValue, const char *filePath) {
	if (GetPrivateProfileString(section, keyword, defaultValue, returnValue, CHARBUFF, filePath) != 0) {
		return true;
	}
	else {
		return false;
	}
}

//���݂̃f�B���N�g���擾
void getCurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

//�t�@�C���������݁ichar�j
bool writeChar(const char *section, const char *keyword, const char *returnValue, const char *filePath) {
	return WritePrivateProfileString(section, keyword, returnValue, filePath);
}

//�t�@�C���������݁iint�j
bool writeInt(const char *section, const char *keyword, int returnValue, const char *filePath) {
	char valueChar[CHARBUFF];
	sprintf_s(valueChar, "%d", returnValue);
	return writeChar(section, keyword, valueChar, filePath);
}

//�t�@�C���������݁idouble�j
bool writeDouble(const char *section, const char *keyword, double returnValue, const char *filePath) {
	char valueChar[CHARBUFF];
	sprintf_s(valueChar, "%lf", returnValue);
	return writeChar(section, keyword, valueChar, filePath);
}

//�ő�`�F�C�������o�͂���֐�
void FileOutput(const char* fileName, int maxchain) {
	FILE* fp;
	errno_t error;
	double sum = 0;

	error = fopen_s(&fp, fileName, "w");

	if (error != 0) {
		fprintf_s(stderr, "failed to open");
	}
	else {
		fprintf(fp, "�ő�`�F�C�����F%d", maxchain);
		}
	fclose(fp);
	}
	

