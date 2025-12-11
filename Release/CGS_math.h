#pragma once
#include "CGS_defines.h"


VERTEX vertMult(VERTEX vertex, Matrix3x3 matrix)
{
	VERTEX answer;
	answer.Position.x = (vertex.Position.x * matrix.xx) + (vertex.Position.y * matrix.yx) + (vertex.Position.z * matrix.zx);
	answer.Position.y = (vertex.Position.x * matrix.xy) + (vertex.Position.y * matrix.yy) + (vertex.Position.z * matrix.zy);
	answer.Position.z = (vertex.Position.x * matrix.xz) + (vertex.Position.y * matrix.yz) + (vertex.Position.z * matrix.zz);

	return answer;
}
VERTEX vertMatrixMul(VERTEX vertex, Matrix4x4 matrix)
{

	VERTEX answer;
	answer.Position.x = (vertex.Position.x * matrix.xx) + (vertex.Position.y * matrix.yx) + (vertex.Position.z * matrix.zx) + (vertex.Position.w * matrix.wx);
	answer.Position.y = (vertex.Position.x * matrix.xy) + (vertex.Position.y * matrix.yy) + (vertex.Position.z * matrix.zy) + (vertex.Position.w * matrix.wy);
	answer.Position.z = (vertex.Position.x * matrix.xz) + (vertex.Position.y * matrix.yz) + (vertex.Position.z * matrix.zz) + (vertex.Position.w * matrix.wz);
	answer.Position.w = (vertex.Position.x * matrix.xw) + (vertex.Position.y * matrix.yw) + (vertex.Position.z * matrix.zw) + (vertex.Position.w * matrix.ww);
	return answer;
}

Matrix4x4 matrixMatrixMul(Matrix4x4 mat1, Matrix4x4 mat2)
{
	Matrix4x4 ans;
	ans.xx = (mat1.xx * mat2.xx) + (mat1.xy * mat2.yx) + (mat1.xz * mat2.zx) + (mat1.xw * mat2.wx);
	ans.xy = (mat1.xx * mat2.xy) + (mat1.xy * mat2.yy) + (mat1.xz * mat2.zy) + (mat1.xw * mat2.wy);
	ans.xz = (mat1.xx * mat2.xz) + (mat1.xy * mat2.yz) + (mat1.xz * mat2.zz) + (mat1.xw * mat2.wz);
	ans.xw = (mat1.xx * mat2.xw) + (mat1.xy * mat2.yw) + (mat1.xz * mat2.zw) + (mat1.xw * mat2.ww);

	ans.yx = (mat1.yx * mat2.xx) + (mat1.yy * mat2.yx) + (mat1.yz * mat2.zx) + (mat1.yw * mat2.wx);
	ans.yy = (mat1.yx * mat2.xy) + (mat1.yy * mat2.yy) + (mat1.yz * mat2.zy) + (mat1.yw * mat2.wy);
	ans.yz = (mat1.yx * mat2.xz) + (mat1.yy * mat2.yz) + (mat1.yz * mat2.zz) + (mat1.yw * mat2.wz);
	ans.yw = (mat1.yx * mat2.xw) + (mat1.yy * mat2.yw) + (mat1.yz * mat2.zw) + (mat1.yw * mat2.ww);

	ans.zx = (mat1.zx * mat2.xx) + (mat1.zy * mat2.yx) + (mat1.zz * mat2.zx) + (mat1.zw * mat2.wx);
	ans.zy = (mat1.zx * mat2.xy) + (mat1.zy * mat2.yy) + (mat1.zz * mat2.zy) + (mat1.zw * mat2.wy);
	ans.zz = (mat1.zx * mat2.xz) + (mat1.zy * mat2.yz) + (mat1.zz * mat2.zz) + (mat1.zw * mat2.wz);
	ans.zw = (mat1.zx * mat2.xw) + (mat1.zy * mat2.yw) + (mat1.zz * mat2.zw) + (mat1.zw * mat2.ww);

	ans.wx = (mat1.wx * mat2.xx) + (mat1.wy * mat2.yx) + (mat1.wz * mat2.zx) + (mat1.ww * mat2.wx);
	ans.wy = (mat1.wx * mat2.xy) + (mat1.wy * mat2.yy) + (mat1.wz * mat2.zy) + (mat1.ww * mat2.wy);
	ans.wz = (mat1.wx * mat2.xz) + (mat1.wy * mat2.yz) + (mat1.wz * mat2.zz) + (mat1.ww * mat2.wz);
	ans.ww = (mat1.wx * mat2.xw) + (mat1.wy * mat2.yw) + (mat1.wz * mat2.zw) + (mat1.ww * mat2.ww);
	return ans;
}

Matrix4x4 matrixIdentity()
{
	Matrix4x4 ans = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	return ans;
}

Matrix4x4 ppMatrix(float xScale, float yScale, float zNear, float zFar)
{
	Matrix4x4 ans = { xScale, 0, 0, 0,
					0, yScale, 0 ,0,
					0,0,zFar / (zFar - zNear), 1,
					0,0, -((zFar * zNear) / (zFar - zNear)), 0 };

	return ans;

}

Matrix4x4 matrixRotation(Matrix4x4 mat, float xRot, float yRot, float zRot)
{
	Matrix4x4 X = { 1,	0,			0,				0,
					0,	cos(xRot),	sin(xRot) * -1 , 0,
					0,	sin(xRot),	cos(xRot),		 0,
					0,	0,			0,				1 };

	Matrix4x4 Y = { cos(yRot), 0, sin(yRot), 0,
					0,1,0,0,
					sin(yRot) * -1, 0, cos(yRot), 0,
					0,0,0,1 };

	Matrix4x4 Z = { cos(zRot),sin(zRot) * -1, 0, 0,
					sin(zRot), cos(zRot), 0, 0,
					0,0,1,0,
					0,0,0,1 };

	if (xRot != 0)
	{
		mat = matrixMatrixMul(mat, X);
	}
	if (yRot != 0)
	{
		mat = matrixMatrixMul(mat, Y);
	}
	if (zRot != 0)
	{
		mat = matrixMatrixMul(mat, Z);
	}

	return mat;
}

Matrix4x4 matrixTranslation(Matrix4x4 mat, VERTEX translation)
{
	Matrix4x4 temp = matrixIdentity();
	temp.wx = translation.Position.x;
	temp.wy = translation.Position.y;
	temp.wz = translation.Position.z;
	return temp;
}

Matrix4x4 matrixInverse(Matrix4x4 mat)
{
	Matrix4x4 ans;
	Matrix3x3 mTemp = { mat.xx, mat.yx, mat.zx, mat.xy, mat.yy, mat.zy, mat.xz, mat.yz, mat.zz };
	VERTEX vTemp = { mat.wx, mat.wy, mat.wz, mat.ww };
	VERTEX posVect = vertMult(vTemp, mTemp);
	posVect = { (posVect.Position.x * -1), (posVect.Position.y * -1), (posVect.Position.z * -1) };
	ans = { mTemp.xx, mTemp.xy, mTemp.xz, mat.xw,
			mTemp.yx, mTemp.yy, mTemp.yz, mat.yw,
			mTemp.zx, mTemp.zy, mTemp.zz, mat.zw,
			posVect.Position.x, posVect.Position.y, posVect.Position.z, mat.ww };//////////
	return ans;
}

float Lerp(float a, float b, float t)
{
	return a + t * (b - a);
}


VERTEX NDCtoScreen(VERTEX input)
{
	int x = (input.Position.x + 1) * (RASTER_WIDTH / 2);
	int y = (1 - input.Position.y) * (RASTER_HEIGHT / 2);
	VERTEX answer = { x, y , input.Position.z };

	return answer;
}

int Convert2Dto1D(int nX, int nY, int nWidth)
{
	return nY * nWidth + nX;
}



unsigned BGRAtoARGB(unsigned C)
{
	//0xBBGGRRAA to 0xAARRGGBB
	unsigned answer;

	unsigned red = C & 0x0000ff00;  //RED
	red = red << (2 * 4);

	unsigned blue = C & 0xff000000; //BLUE
	blue = blue >> (6 * 4);

	unsigned green = C & 0x00ff0000;  //GREEN
	green = green >> (2 * 4);

	unsigned alpha = C & 0x000000ff;  //ALPHA
	alpha = alpha << (6 * 4);

	answer = alpha | red | blue | green;
	return answer;
}

float ImplicitLineEquation(VERTEX start, VERTEX end, float x, float y)
{
	//  (Y1 - Y2)x + (X2 - X1)y + X1Y2 - X2Y1
	float Ax = (start.Position.y - end.Position.y) * x;
	float By = (end.Position.x - start.Position.x) * y;
	float C = (start.Position.x * end.Position.y) - (start.Position.y * end.Position.x);
	return Ax + By + C;
	
}

BYA FindBaryRatio(VERTEX A, VERTEX B, VERTEX C, float currX, float currY)
{
	BYA bya;

	float maxBeta = ImplicitLineEquation(A, C, B.Position.x, B.Position.y);
	float maxGamma = ImplicitLineEquation(B, A, C.Position.x, C.Position.y);
	float maxAlpha = ImplicitLineEquation(C, B, A.Position.x, A.Position.y);
	float pBeta = ImplicitLineEquation(A, C, currX, currY);
	float pGamma = ImplicitLineEquation(B, A, currX, currY);
	float pAlpha = ImplicitLineEquation(C, B, currX, currY);

	
	bya.b = (pBeta / maxBeta);
	bya.y = (pGamma / maxGamma);
	bya.a = (pAlpha / maxAlpha);

	
	
	
	
	return bya;
}

float BarycetricInterp(float a, float b, float c, BYA bya)
{
	float nInterp = (a * bya.a) + (b * bya.b) + (c * bya.y);
	return nInterp;
}

float BarycetricColor(unsigned int a, unsigned int b, unsigned int c, BYA bya)
{
	float nInterp = (a * bya.a) + (b * bya.b) + (c * bya.y);
	return nInterp;
}
