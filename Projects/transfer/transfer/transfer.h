#ifndef _TRANSFER_H_
#define _TRANSFER_H_

#include <Windows.h>
#include <math.h>

#define WIDTHBYTES(i) ((i+31)/32*4)
#define BINARYWIDTH(i) ((i+3)/4*4)

/**
* ͨ������ֵ����ͼƬ�ӻҶ�ͼתΪ��ֵͼ
*/
unsigned char** grayToBinaryByThreshold(BITMAPFILEHEADER bitMapFileHeader,
	BITMAPINFOHEADER bitMapInfoHeader, RGBQUAD* palettes, unsigned char** imgData, char threshold);

/**
* ͨ��Dither�㷨���Ҷ�ͼתΪ��ֵͼ
*/
unsigned char** grayToBinaryByDither(BITMAPFILEHEADER bitMapFileHeader,
	BITMAPINFOHEADER bitMapInfoHeader, RGBQUAD* palettes, unsigned char** imgData, int matrixSize);

/**
* ����Dither����
*/
unsigned char** getDitherMatrix(int n);

/**
* ���ɶ�ֵͼ����Ϣͷ������ֵ����
*/
BITMAPINFOHEADER getBinaryInfoHeaderByThreshold(BITMAPINFOHEADER bi);

/**
* ���ɶ�ֵͼ���ļ�ͷ������ֵ����
*/
BITMAPFILEHEADER getBinaryFileHeaderByThreshold(BITMAPFILEHEADER bf);

/**
* ���ɶ�ֵͼ�ĵ�ɫ��
*/
RGBQUAD* getBinaryRGBQuad();

#endif // !_TRANSFER_H_
