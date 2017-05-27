#include "stdafx.h"
#include "MyBMP.h"
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <fstream>

using namespace std;

void save(const char* filename, const char* fileheader, const char* infoheader, const char* rgbquad, const char* data, int length);

int calculateLenth(MyBMP* bmp) {
	BITMAPINFOHEADER infoheader = bmp->getInfoheader();

	int bitCount = infoheader.biBitCount;
	int width = infoheader.biWidth;
	int height = infoheader.biHeight;

	int length = 0;
	if (bitCount == 1) {
		length = 0;
	}
	else if (bitCount == 4) {
		//length = 1 * width * height / 8;
		length = 0;
	}
	else if (bitCount == 8) {
		length = 1 * width * height / 8;
	}
	else if (bitCount == 24) {
		length = 3 * width * height / 8;
	}
	return length;
}

BYTE* hide(MyBMP* bmp, const char* content) {
	char tmp = 1;
	int i;
	int j;
	int length;

	BITMAPFILEHEADER fileheader = bmp->getFileheader();
	BITMAPINFOHEADER infoheader = bmp->getInfoheader();

	int bitCount = infoheader.biBitCount;
	int width = infoheader.biWidth;
	int height = infoheader.biHeight;
	if (bitCount == 1 || bitCount == 4) {
		return NULL;
	}
	if (bitCount == 8) {
		length = width * height;
	}
	else {
		length = 3 * width * height;
	}
	BYTE* oldData = bmp->getImagedata();
	BYTE* newData = new BYTE[length];

	memcpy(newData, oldData, length * sizeof(BYTE));
	for (i = 0; i < strlen(content); i++) {
		for (j = 0; j < 8; j++) {
			tmp = ((oldData[i * 8 + j] >> 1) << 1) | (tmp & (content[i] >> (7 - j)));
			newData[i * 8 + j] = tmp;
			tmp = 1;
		}
	}
	for (int k = 0; k < 8; k++) {
		tmp = ((oldData[i * 8 + k] >> 1) << 1);//½áÊø·û'\0'
		newData[i * 8 + k] = tmp;
		tmp = 1;
	}

	ofstream outputfile("tmp.BMP", ios::binary);

	if (outputfile) {
		outputfile.write((char*)(&fileheader), sizeof(BITMAPFILEHEADER));
		outputfile.write((char*)(&infoheader), sizeof(BITMAPINFOHEADER));
		if (bitCount == 8) {
			outputfile.write((char*)(bmp->getRGBQUAD()), sizeof(RGBQUAD) * 256);
		}
		outputfile.write((char*)(newData), sizeof(BYTE) * length);
		outputfile.close();
	}
	//save("mmd.bmp", (char*)(&fileheader), (char*)(&infoheader), NULL, (char*)newData, length);
	delete[] oldData;
	return newData;
}

void save(const char* filename, const char* fileheader, const char* infoheader, const char* rgbquad, const char* data, int length) {
	ofstream outputfile(filename, ios::binary);

	if (outputfile) {
		outputfile.write((fileheader), sizeof(BITMAPFILEHEADER));
		outputfile.write((infoheader), sizeof(BITMAPINFOHEADER));
		if (rgbquad != NULL) {
			outputfile.write((rgbquad), sizeof(RGBQUAD) * 256);
		}
		outputfile.write(data, sizeof(BYTE) * length);
		outputfile.close();
	}
}

const char* extract(MyBMP* bmp) {
	char tmp = 0;
	int i;
	int j;
	int length;
	BITMAPINFOHEADER infoheader = bmp->getInfoheader();

	int bitCount = infoheader.biBitCount;
	int width = infoheader.biWidth;
	int height = infoheader.biHeight;
	if (bitCount == 1 || bitCount == 4) {
		return NULL;
	}
	if (bitCount == 8) {
		length = width * height;
	}
	else {
		length = 3 * width * height;
	}
	BYTE* oldData = bmp->getImagedata();

	char* content = (char*)malloc(sizeof(BYTE) * length / 8);

	for (i = 0; i < length;) {
		for (j = 0; j < 8; i++, j++) {
			if ((oldData[i] & 1) == 1) {
				tmp |= 1 << (7 - j);
			}
			else {
				tmp &= ~(1 << (7 - j));
			}
		}
		content[i / 8 - 1] = tmp;
		if (tmp == '\0') {
			delete[] oldData;
			return content;
		}
	}
}