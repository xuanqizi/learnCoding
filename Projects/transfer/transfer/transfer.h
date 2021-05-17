#ifndef _TRANSFER_H_
#define _TRANSFER_H_

#include <Windows.h>
#include <math.h>

#define WIDTHBYTES(i) ((i+31)/32*4)
#define BINARYWIDTH(i) ((i+3)/4*4)

/// <summary>
/// ͨ������ֵ����ͼƬ�ӻҶ�ͼתΪ��ֵͼ
/// </summary>
/// <param name="bitMapFileHeader">�Ҷ�ͼ���ļ�ͷ</param>
/// <param name="bitMapInfoHeader">�Ҷ�ͼ����Ϣͷ</param>
/// <param name="palettes">�Ҷ�ͼ�ĵ�ɫ��</param>
/// <param name="imgData">�Ҷ�ͼ��ͼƬ����</param>
/// <param name="threshold">����ֵ������ֵ</param>
/// <returns>��ֵͼ��ͼƬ����</returns>
unsigned char** grayToBinaryByThreshold(BITMAPFILEHEADER bitMapFileHeader,
	BITMAPINFOHEADER bitMapInfoHeader, RGBQUAD* palettes, unsigned char** imgData, char threshold);

/**
* ͨ��Dither�㷨���Ҷ�ͼתΪ��ֵͼ
*/
unsigned char** grayToBinaryByDither(BITMAPFILEHEADER bitMapFileHeader,
	BITMAPINFOHEADER bitMapInfoHeader, RGBQUAD* palettes, unsigned char** imgData, int matrixSize);

/// <summary>
/// ����n*n��Dither����
/// </summary>
/// <param name="n">����ĳߴ磨����Ϊ2����������</param>
/// <returns>Dither����</returns>
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

/// <summary>
/// ���ɶ�ֵͼ����Ϣͷ��Dither��
/// </summary>
/// <param name="bi">�Ҷ�ͼ����Ϣͷ</param>
/// <param name="n">Dither����Ĵ�СΪn*n</param>
/// <returns></returns>
BITMAPINFOHEADER getBinaryInfoHeaderByDither(BITMAPINFOHEADER bi, int n);

/// <summary>
/// ���ɶ�ֵͼ���ļ�ͷ��Dither��
/// </summary>
/// <param name="bf">�Ҷ�ͼ���ļ�ͷ</param>
/// <param name="n">Dither����Ĵ�С</param>
/// <returns></returns>
BITMAPFILEHEADER getBinaryFileHeaderByDither(BITMAPFILEHEADER bf, BITMAPINFOHEADER bi, int n);

#endif // !_TRANSFER_H_
