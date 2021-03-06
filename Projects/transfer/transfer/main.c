﻿/**
* 用于对方法进行测试的类
*/
#define _CRT_SECURE_NO_WARNINGS

#include "examples.h"

int main() {
	// g2bThresholdExample();		// 通过单阈值法将灰度图转为二值图的示例
	// g2bDitherExample();			// 通过Dither算法将灰度图转为二值图的示例
	// g2bOrderedDitherExample();		// 通过Ordered Dither算法将灰度图转为二值图的示例
	// c2gHSIExample();		// 通过RGB-HSI的方法将24位真彩色图转为灰度图的示例
	c2gYCbCrExample();		// 通过RGB-YCbCr的方法将24位真彩色图转为灰度图的示例
	return 0;
}