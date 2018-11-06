#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"

#include "Vector.h"
#include "IntPoint.h"

bool IsInRange(int x, int y);
void PutPixel(int x, int y);

bool IsInRange(int x, int y)
{
	return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
}

void PutPixel(const IntPoint& InPt) 
{
	PutPixel(InPt.X, InPt.Y);
}

void PutPixel(int x, int y)
{
	if (!IsInRange(x, y)) return;

	ULONG* dest = (ULONG*)g_pBits;
	DWORD offset = g_nClientWidth * g_nClientHeight / 2 + g_nClientWidth / 2 + x + g_nClientWidth * -y;
	*(dest + offset) = g_CurrentColor;
}


void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	// Draw
	SetColor(255, 0, 0);

	// Draw a circle with radius 100
	Vector2 center(0.0f, 0.0f);
	float radius = 100.0f;

	//Matrix2 scaleMat;
	//scaleMat.SetScale(2.0f, 0.5f);

/*
	Matrix2 SRMat = scaleMat * rotMat;
	Matrix2 RSmat = rotMat * scaleMat;*/

	int nradius = (int)radius;
	static float degree = 0.0f;
	degree += 0.5f;
	degree = fmodf(degree, 360.0f);

	Matrix3 rotMat;
	rotMat.SetRotation(degree);
	rotMat.Transpose();

	static float scale = 1;
	scale += 0.01f;
	scale = fmodf(scale, 2.0f);

	Matrix3 scaleMat;
	scaleMat.SetScale(scale, scale, scale);

	static float move = 1;
	move += 1;
	move = fmodf(move, 150);
	Matrix3 translationMat;
	translationMat.SetTranslation(move, move);

	Matrix3 SR = rotMat * scaleMat;
	Matrix3 TRS = translationMat * rotMat * scaleMat;

	for (int i = -nradius; i <= nradius; i++)
	{
		for (int j = -nradius; j <= nradius; j++)
		{
			PutPixel(Vector3((float)i, (float)j) * SR);
		}
	}

	BufferSwap();
}
