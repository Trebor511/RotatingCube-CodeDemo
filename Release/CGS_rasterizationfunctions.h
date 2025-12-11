#pragma once
#include "CGS_shaders.h"



void PlotPixel(int xPos, int yPos, float zPos, int color)
{

	int index = Convert2Dto1D(xPos, yPos, RASTER_WIDTH);
	if (index < NUM_PIXELS - 1 && xPos < RASTER_WIDTH && yPos < RASTER_HEIGHT)
	{
		if (zPos < DEPTH_ARRAY[index])
		{
			DEPTH_ARRAY[index] = zPos;
		SCREEN_ARRAY[index] = color;
		}

	}
	// Make sure its on the raster
	//if current depth < whats in the depth buffer[index]
	//set color to color buffer and set depth to depth buffer
	//record depth buffer with updated values
}


void FillTriangle(VERTEX a, VERTEX b, VERTEX c, unsigned int color)
{
	//Better Brute after for Optimization

	

	float startX = min(min(a.Position.x, b.Position.x), c.Position.x);
	float startY = min(min(a.Position.y, b.Position.y), c.Position.y);
	float endX = max(min(a.Position.x, b.Position.x), c.Position.x);
	float endY = max(min(a.Position.y, b.Position.y), c.Position.y);

	BYA ratio;
	//Find Bery, if out of range, move on
	for (int i = startY; i <= endY; ++i)
	{
		for (int j = startX; j <= endX; ++j)
		{

			ratio = FindBaryRatio(a, b, c, j, i);
			if (ratio.b >= 0 && ratio.b <= 1 && ratio.y >= 0 && ratio.y <= 1 && ratio.a >= 0 && ratio.a <= 1)
			{
				float zRatio = BarycetricInterp(a.Position.z, b.Position.z, c.Position.z, ratio);
				float uRatio = BarycetricInterp(a.U, b.U, c.U, ratio);
				float vRatio = BarycetricInterp(a.V, b.V, c.V, ratio);
				//unsigned int color = BarycetricColor(a.color, b.color, c.color, ratio);
				VERTEX vert = { j,i,zRatio, 1,color, uRatio, vRatio, };
				if (VertexShader)
				{
					VertexShader(vert);
				}
				PlotPixel(j, i, zRatio, color);

			}
		}
	}

}


void ClearRaster()
{
	for (int i = 0; i < NUM_PIXELS; i++)
	{
		SCREEN_ARRAY[i] = 0x00000000;

	}
}

void ClearDepthBuffer()
{
	for (int i = 0; i < NUM_PIXELS; ++i)
	{
		DEPTH_ARRAY[i] = 1.0f;
	}
}

void PlotLine(VERTEX start, VERTEX end, unsigned int color)
{
	//Determine line properties
	float delX = end.Position.x - start.Position.x;
	float delY = end.Position.y - start.Position.y;
	float largest = max(abs(delX), abs(delY));


	for (int i = 0; i < largest; ++i)
	{
		float ratio = i / largest;
		float currX = Lerp(start.Position.x, end.Position.x, ratio);
		float currY = Lerp(start.Position.y, end.Position.y, ratio);
		float currZ = Lerp(start.Position.z, end.Position.z, ratio);


		PlotPixel((int)currX, (int)currY, (int)currZ, color);
	}
}
void DrawLine(const VERTEX& start, const VERTEX& end, unsigned int color)
{


	//Copy input data and send through shaders
	VERTEX copy_start = start;
	VERTEX copy_end = end;

	//Use vertex shader to modify incoming copies only
	if (VertexShader)
	{
		VertexShader(copy_start);
		VertexShader(copy_end);
	}
	VERTEX screen_start = NDCtoScreen(copy_start);
	VERTEX screen_end = NDCtoScreen(copy_end);


	Pixel copyColor;
	copyColor.color = color; //Just like a Vertex, copy original
	if (PixelShader) PixelShader(copyColor); //Modify copy

	PlotLine(screen_start, screen_end, copyColor.color);

}

void DrawTriangle( VERTEX& a, VERTEX& b, VERTEX& c)
{
	DrawLine(a, b, a.color);
	DrawLine(b, c, b.color);
	DrawLine(c, a, c.color);

	
	VERTEX copy_A = a;
	VERTEX copy_B = b;
	VERTEX copy_C = c;
	// Use vertex shader to modify incoming copies only.
	if (VertexShader)
	{
		VertexShader(copy_A);
		VertexShader(copy_B);
		VertexShader(copy_C);
	}

	// original plotting variables adapted to use new cartesian data
	VERTEX screen_A = NDCtoScreen(copy_A);
	VERTEX screen_B = NDCtoScreen(copy_B);
	VERTEX screen_C = NDCtoScreen(copy_C);
	// Standard line drawing code follows using integer coordinates...
	FillTriangle(screen_A, screen_B, screen_C, a.color);
}


