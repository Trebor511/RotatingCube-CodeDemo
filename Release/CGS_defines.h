#pragma once
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <math.h>
#include "RasterSurface.h"    //INCLUDES
#include "XTime.h"
#include "crashTexture.h"
#define RASTER_WIDTH 500							//DEFINES
#define RASTER_HEIGHT 600
#define NUM_PIXELS (RASTER_WIDTH * RASTER_HEIGHT)

unsigned SCREEN_ARRAY[NUM_PIXELS];   //GLOBAL VARIABLES
float DEPTH_ARRAY[NUM_PIXELS]; //For Z-Buffer

//STRUCTS
struct Float4
{
	union
	{
		struct
		{
			float V[4];
		};
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};
};

struct Matrix4x4
{
	union
	{
		struct
		{
			float  V[16];
		};
		struct
		{
			float  xx;
			float  xy;
			float  xz;
			float  xw;
			float  yx;
			float  yy;
			float  yz;
			float  yw;
			float  zx;
			float  zy;
			float  zz;
			float  zw;
			float  wx;
			float  wy;
			float  wz;
			float  ww;
		};
		struct
		{
			Float4 AxisX;
			Float4 AxisY;
			Float4 AxisZ;
			Float4 AxisW;
		};
	};
};

struct Matrix3x3
{
	union
	{
		struct
		{
			float  V[9];
		};
		struct
		{
			float  xx;
			float  xy;
			float  xz;

			float  yx;
			float  yy;
			float  yz;

			float  zx;
			float  zy;
			float  zz;


		};

	};
};
struct VERTEX
{
	Float4 Position;
	unsigned int color;

	float U;
	float V;
	//Space for later variables
};

struct Pixel
{
	int x;
	int y;
	unsigned int color;
};

struct BYA
{
	float b;
	float y;
	float a;
};
//CLASSES