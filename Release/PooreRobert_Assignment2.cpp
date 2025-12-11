// PooreRobert_Assignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CGS_rasterizationfunctions.h"

int main()
{
	RS_Initialize("Rotate the Cube!", RASTER_WIDTH, RASTER_HEIGHT);
	std::vector<VERTEX> cubeVertex;

	XTime timer;

	// CUBE VERTEX DECLARATION  (8 Points)
	VERTEX one = { -0.25, 0.25, -0.25, 1, 0xffff0000 };
	cubeVertex.push_back(one);
	VERTEX two = { 0.25, 0.25, -0.25, 1, 0xffff0000 };
	cubeVertex.push_back(two);
	VERTEX four = { -0.25, -0.25, -0.25, 1, 0xffff0000 };
	cubeVertex.push_back(four);
	VERTEX three = { 0.25, -0.25, -0.25, 1, 0xffff0000 };
	cubeVertex.push_back(three);

	VERTEX five = { -0.25, 0.25, 0.25, 1, 0xFFFFFFFF };
	cubeVertex.push_back(five);
	VERTEX six = { 0.25, 0.25, 0.25, 1, 0xff00ff00 };
	cubeVertex.push_back(six);
	VERTEX eight = { -0.25, -0.25, 0.25, 1, 0xFFFFFFFF };
	cubeVertex.push_back(eight);
	VERTEX seven = { 0.25, -0.25, 0.25, 1, 0xFFFFFFFF };
	cubeVertex.push_back(seven);

	Matrix4x4 cubeWorldMatrix = matrixIdentity();
	VERTEX up = { 0,0.25,0,0 };
	cubeWorldMatrix = matrixTranslation(cubeWorldMatrix, up);

	//GRID VERTEX DECLARATION (4 Points)
	VERTEX backLeft = { -0.5, 0.0, -0.5, 1, 0xFFFFFFFF };
	VERTEX backRight = { 0.5, 0.0, -0.5, 1,  0xffffffff };
	VERTEX frontLeft = { -0.5, 0.0, 0.5, 1, 0xffffffff };
	VERTEX frontRight = { 0.5, 0.0, 0.5, 1, 0xffffffff };

	Matrix4x4 gridWorldMatrix = matrixIdentity();

	//VIEW MATRIX/////////
	Matrix4x4 viewWorldMatrix = matrixIdentity();
	VERTEX back = { 0,0,-1.25,0 };
	viewWorldMatrix = matrixTranslation(viewWorldMatrix, back);
	viewWorldMatrix = matrixRotation(viewWorldMatrix, -0.314, 0, 0);

	VS_ViewMatrix = matrixInverse(viewWorldMatrix);
	//////////////////////

	//Perspective Matrix//////////////////
	float yScale = 1.0 / tan(0.785398);
	float xScale = yScale * ((float)RASTER_HEIGHT / RASTER_WIDTH);
	VS_PerspectiveProjection = ppMatrix(xScale, yScale, 0.1, 10.0);
	//  ////////////////////////////////////


	timer.Restart();
	float elapsed = 0;
	while (RS_Update(SCREEN_ARRAY, NUM_PIXELS))
	{
		ClearRaster();
		ClearDepthBuffer();


		VertexShader = VS_World;

		timer.Signal();
		elapsed += timer.Delta();

		VS_WorldMatrix = matrixMatrixMul(matrixTranslation(matrixIdentity(), up), matrixRotation(matrixIdentity(),
			0, timer.TotalTime(), 0));

		///CUBE/////////////////////////////////////////////////////////////////////////

		//FRONT
		DrawLine(one, two, 0x0000ff00);     //1----2
		DrawLine(two, three, 0x0000ff00);	// 2----3
		DrawLine(three, four, 0x0000ff00);	// 3----4
		DrawLine(four, one, 0x0000ff00);	//4----1


		DrawLine(five, six,		0x0000ff00);    //5----6
		DrawLine(six, seven,	0x0000ff00);	//6----7
		DrawLine(seven, eight,	0x0000ff00);	//7----8
		DrawLine(eight, five,	0x0000ff00);	//8----5

		DrawLine(two, six,		0x0000ff00);	//2----6
		DrawLine(one, five,		0x0000ff00);	//1----5
		DrawLine(four, eight,	0x0000ff00);	//4----8
		DrawLine(three, seven,	0x0000ff00);	//3----7
		////////////////////////////////////////////////////////////////////////////////
		
		///CUBE TRIANGLES///////////////////////////////////////////////////////////
		PixelShader = PS_blue;
		DrawTriangle(one, five, six);  //TOP 1
		DrawTriangle(one, two, six); //TOP 2
		//FillTriangle(one, five, six, 0x0000ff00);  //TOP 1
		//FillTriangle(one, six, two, 0x0000ff00);

		DrawTriangle(one, two, three);	//Front 1
		DrawTriangle(one, four, three);	//Front 2
		

		DrawTriangle(five, one, four); //Left 1
		DrawTriangle(five, eight, four); //Left 2

		DrawTriangle(two, six, seven); //Right 1
		DrawTriangle(two , three, seven); //Right 2


		DrawTriangle(six, five, eight); //Back 1
		DrawTriangle(six, seven, eight); //Back 2

		DrawTriangle(eight, seven, four); //bottom 1
		DrawTriangle(four, seven, three); //bottom 2

		PixelShader = PS_White;
		//////////////////////////////////////////////////////////////////////////////
		VS_WorldMatrix = gridWorldMatrix;
		///GRID/////////////////////////////////////////////////////////////////////////
		backLeft = { -0.5, 0.0, -0.5, 1, 0xFFFFFFFF };
		backRight = { 0.5, 0.0, -0.5, 1,  0xffffffff };
		frontLeft = { -0.5, 0.0, -0.5, 1, 0xffffffff };
		frontRight = { 0.5, 0.0, -0.5, 1, 0xffffffff };
		for (int i = 0; i < 11; i++)
		{

			DrawLine(frontLeft, frontRight, 0xfffffff);
			frontLeft.Position.z += 0.1;
			frontRight.Position.z += 0.1;
			if (i == 10)
			{

				DrawLine(frontLeft, frontRight, 0xfffffff);
			}

		}

		for (int j = 0; j < 11; j++)
		{
			DrawLine(frontRight, backRight, 0xfffffff);
			frontRight.Position.x -= 0.1;
			backRight.Position.x -= 0.1;
		}

		////////////////////////////////////////////////////////////////////////////////
	}
	RS_Shutdown();
	return 0;
}


