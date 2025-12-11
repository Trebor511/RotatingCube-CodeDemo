#pragma once
#include "CGS_math.h"

//The active vertex shader. Modifies an incoming vertex. Pre-Rasterization.
void (*VertexShader)(VERTEX&) = 0;

//The active Pixel shader. Modifies an outgoing pixel. Post-Rasterization.
void (*PixelShader)(Pixel&) = 0;

//Various custom vertex and pixel shaders, (Pre-Fixed by "VS" and "PS_")
//Can be swapped using the above function pointers as needed for flexability
Matrix4x4 VS_WorldMatrix;
Matrix4x4 VS_ViewMatrix;
Matrix4x4 VS_PerspectiveProjection;
//Applys the current world matrix to all
void VS_World(VERTEX& multiplyMe)
{
	multiplyMe = vertMatrixMul(multiplyMe, VS_WorldMatrix);
	multiplyMe = vertMatrixMul(multiplyMe, VS_ViewMatrix);
	multiplyMe = vertMatrixMul(multiplyMe, VS_PerspectiveProjection);

	multiplyMe.Position.x /= multiplyMe.Position.w;
	multiplyMe.Position.y /= multiplyMe.Position.w;
	multiplyMe.Position.z /= multiplyMe.Position.w;
}


//Basic pixel shader returns the color white
void PS_White(Pixel& makeWhite)
{
	makeWhite.color = 0xffffffff;
}

void PS_Red(Pixel& makered)
{
	makered.color = 0x00ff0000;
}

void PS_blue(Pixel& makeblue)
{
	makeblue.color = 0x000000ff;
}