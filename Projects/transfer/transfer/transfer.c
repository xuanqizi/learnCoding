#include "transfer.h"

unsigned char** grayToBinaryByThreshold(BITMAPFILEHEADER bitMapFileHeader,
	BITMAPINFOHEADER bitMapInfoHeader, RGBQUAD* palettes, unsigned char** imgData, char threshold) {
	LONG width = bitMapInfoHeader.biWidth;		// ���
	LONG height = bitMapInfoHeader.biHeight;	// �߶�
	LONG count = bitMapInfoHeader.biBitCount;	// λ��
	DWORD lineBytes = (DWORD)WIDTHBYTES(width * count);		// ÿ�е��ֽ���
	// ���ڶ�ȡ�ļ�ʱ�Ѿ�������룬����ֻ��Ҫ˳���ȡ����
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < lineBytes; j++) {
			char index = imgData[i][j];		// ��ȡ��ɫ��Ӧ�ĵ�ɫ������
			RGBQUAD color = palettes[index];		// ����������ȡ��Ӧ�ĵ�ɫ��
			BYTE gray = color.rgbRed;		// �Ҷ�ͼ��RGB��ֵ��ȣ����ֻ��ȡ����һ��
			if (gray >= threshold) {
				imgData[i][j] = 255;
			}
			else {
				imgData[i][j] = 0;
			}
		}
	}
	return imgData;
}

unsigned char** grayToBinaryByDither(BITMAPFILEHEADER bitMapFileHeader,
	BITMAPINFOHEADER bitMapInfoHeader, RGBQUAD* palettes, unsigned char** imgData, int matrixSize) {
	LONG width = bitMapInfoHeader.biWidth;		// ���
	LONG height = bitMapInfoHeader.biHeight;	// �߶�
	LONG count = bitMapInfoHeader.biBitCount;	// λ��
	DWORD lineBytes = (DWORD)WIDTHBYTES(width * count);		// ÿ�е��ֽ���
	// ��ͼƬ���ݷ�Χ����ѹ��
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < lineBytes; j++) {
			imgData[i][j] = imgData[i][j] * (matrixSize * matrixSize + 1) / 256;
		}
	}
	unsigned char** ditherMatrix = getDitherMatrix(matrixSize);		// ����dither����
	unsigned char** outputData = (unsigned char**)malloc(matrixSize * height * sizeof(unsigned char*));
	// ����dither������ж�ֵ��
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int x = i * matrixSize;
			int y = j * matrixSize;
			for (int ditherI = 0; ditherI < matrixSize; ditherI++) {
				for (int ditherJ = 0; ditherJ < matrixSize; ditherJ++) {
					if (imgData[i][j] >= ditherMatrix[ditherI][ditherJ]) {

					}
				}
			}
		}
	}
	return NULL;
}

unsigned char** getDitherMatrix(int n) {
	char** matrix = (char**)malloc(n * sizeof(char*));
	for (int i = 0; i < n; i++) {
		matrix[i] = (char*)malloc(n * sizeof(char));
	}
	if (n == 2) {
		matrix[0][0] = 0;
		matrix[0][1] = 2;
		matrix[1][0] = 1;
		matrix[1][1] = 3;
		return matrix;
	}
}

BITMAPINFOHEADER getBinaryInfoHeaderByThreshold(BITMAPINFOHEADER bi) {
	bi.biBitCount = 1;
	return bi;
}

BITMAPFILEHEADER getBinaryFileHeaderByThreshold(BITMAPFILEHEADER bf) {
	bf.bfSize -= (254 * sizeof(RGBQUAD));
	bf.bfOffBits -= (254 * sizeof(RGBQUAD));
	return bf;
}

RGBQUAD* getBinaryRGBQuad() {
	RGBQUAD* rgbQuad = (RGBQUAD*)malloc(2 * sizeof(RGBQUAD));
	RGBQUAD white;
	white.rgbRed = 0; white.rgbGreen = 0; white.rgbBlue = 0; white.rgbReserved = 0;
	RGBQUAD black;
	black.rgbRed = 255; black.rgbGreen = 255; black.rgbBlue = 255; black.rgbReserved = 0;
	rgbQuad[0] = white;
	rgbQuad[1] = black;
	return rgbQuad;
}