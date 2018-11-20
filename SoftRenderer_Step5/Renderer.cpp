#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"

#include "Vector.h"
#include "IntPoint.h"
#include "Vertex.h"

bool IsInRange(int x, int y);
void PutPixel(int x, int y);

void DrawTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3);
void DrawTriangle(const Vector3 &p1, const Vector3 &p2, const Vector3 &p3);

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

void DrawLine(const Vector3 &start, const Vector3 &end)
{
	// L = (1-t)P + tQ   0 <= t <= 1
	float length = Vector3::Dist(end, start);
	float inc = 1.0f / length;
	int nLength = (int)(length + 1);

	for (int i = 0; i <= nLength; i++)
	{
		float t = inc * i;
		if (t >= length) t = 1.0f;
		Vector3 pt = start * (1.0f - t) + end * t;
		PutPixel(IntPoint(pt));
	}
}

void DrawTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3)
{
	Vector2 minPos = Vector2(INFINITY, INFINITY);
	Vector2 maxPos = Vector2(-INFINITY, -INFINITY);

	Vector3 p1 = v1.position;
	Vector3 p2 = v2.position;
	Vector3 p3 = v3.position;

	if (p1.X < minPos.X) minPos.X = p1.X;
	if (p1.Y < minPos.Y) minPos.Y = p1.Y;
	if (p1.X > maxPos.X) maxPos.X = p1.X;
	if (p1.Y > maxPos.Y) maxPos.Y = p1.Y;

	if (p2.X < minPos.X) minPos.X = p2.X;
	if (p2.Y < minPos.Y) minPos.Y = p2.Y;
	if (p2.X > maxPos.X) maxPos.X = p2.X;
	if (p2.Y > maxPos.Y) maxPos.Y = p2.Y;

	if (p3.X < minPos.X) minPos.X = p3.X;
	if (p3.Y < minPos.Y) minPos.Y = p3.Y;
	if (p3.X > maxPos.X) maxPos.X = p3.X;
	if (p3.Y > maxPos.Y) maxPos.Y = p3.Y;

	Vector3 u = p2 - p1;
	Vector3 v = p3 - p1;
	float dotUU = Vector3::Dot(u, u);
	float dotUV = Vector3::Dot(u, v);
	float dotVV = Vector3::Dot(v, v);
	float invDenom = 1.0f / (dotUU * dotVV - dotUV * dotUV);

	IntPoint minPt(minPos);
	IntPoint maxPt(maxPos);

	for (int x = minPt.X; x < maxPt.X; x++)
	{
		for (int y = minPt.Y; y < maxPt.Y; y++)
		{
			IntPoint pt(x, y);
			Vector3 w = pt.ToVector3() - p1;
			float dotUW = Vector3::Dot(u, w);
			float dotVW = Vector3::Dot(v, w);
			float s = (dotVV * dotUW - dotUV * dotVW) * invDenom;
			float t = (dotUU * dotVW - dotUV * dotUW) * invDenom;
			if (s >= 0 && t >= 0 && ((s + t) <= 1))
			{
				BYTE RV1 = GetRValue(v1.color);
				BYTE RV2 = GetRValue(v2.color);
				BYTE RV3 = GetRValue(v3.color);

				BYTE GV1 = GetGValue(v1.color);
				BYTE GV2 = GetGValue(v2.color);
				BYTE GV3 = GetGValue(v3.color);

				BYTE BV1 = GetBValue(v1.color);
				BYTE BV2 = GetBValue(v2.color);
				BYTE BV3 = GetBValue(v3.color);

				BYTE FinalR = (BYTE)(RV1 * (1 - s - t) + RV2 * s + RV3 * t);
				BYTE FinalG = (BYTE)(GV1 * (1 - s - t) + GV2 * s + GV3 * t);
				BYTE FinalB = (BYTE)(BV1 * (1 - s - t) + BV2 * s + BV3 * t);

				SetColor(FinalR, FinalG, FinalB);
				PutPixel(pt);
			}
		}
	}
}

void DrawTriangle(const Vector3 &p1, const Vector3 &p2, const Vector3 &p3)
{
	Vector2 minPos = Vector2(INFINITY, INFINITY);
	Vector2 maxPos = Vector2(-INFINITY, -INFINITY);

	if (p1.X < minPos.X) minPos.X = p1.X;
	if (p1.Y < minPos.Y) minPos.Y = p1.Y;
	if (p1.X > maxPos.X) maxPos.X = p1.X;
	if (p1.Y > maxPos.Y) maxPos.Y = p1.Y;

	if (p2.X < minPos.X) minPos.X = p2.X;
	if (p2.Y < minPos.Y) minPos.Y = p2.Y;
	if (p2.X > maxPos.X) maxPos.X = p2.X;
	if (p2.Y > maxPos.Y) maxPos.Y = p2.Y;

	if (p3.X < minPos.X) minPos.X = p3.X;
	if (p3.Y < minPos.Y) minPos.Y = p3.Y;
	if (p3.X > maxPos.X) maxPos.X = p3.X;
	if (p3.Y > maxPos.Y) maxPos.Y = p3.Y;

	Vector3 u = p2 - p1;
	Vector3 v = p3 - p1;
	float dotUU = Vector3::Dot(u, u);
	float dotUV = Vector3::Dot(u, v);
	float dotVV = Vector3::Dot(v, v);
	float invDenom = 1.0f / (dotUU * dotVV - dotUV * dotUV);

	IntPoint minPt(minPos);
	IntPoint maxPt(maxPos);

	for (int x = minPt.X; x < maxPt.X; x++)
	{
		for (int y = minPt.Y; y < maxPt.Y; y++)
		{
			IntPoint pt(x, y);
			Vector3 w = pt.ToVector3() - p1;
			float dotUW = Vector3::Dot(u, w);
			float dotVW = Vector3::Dot(v, w);
			float s = (dotVV * dotUW - dotUV * dotVW) * invDenom;
			float t = (dotUU * dotVW - dotUV * dotUW) * invDenom;
			if (s >= 0 && t >= 0 && ((s + t) <= 1))
			{
				PutPixel(pt);
			}
		}
	}
}


/*
	Linearity -> Vector Space
	Vector -> Linear Transformation(Matrix)
	선형는 행렬(Matrix)로 계산한다.

	f(x+y) = f(x) + f(y)
	a*f(x) = f(a*x)
	a = 스칼라(Scalar) -> 백터를 마음대로 주무른다/...?


	백터 공간(vector space) = Linearity

	Vector Space -> 벡터의 집합체이다.
					스칼라(Scalar)라는 값이 있다. R(Real Number : 실수)이라고도 표현한다.

	basis vector -> 기저벡터 (X, y) 기저벡터는 서로 다른 축에 영향을 줄 수 없다.

	standard basis vector -> 표준 기저벡터 (x축과 y축이 1인 벡터공간)

	span -> 벡터를 생성한다.(ax + by) a와 b는 스칼라, x와 y는 벡터(기저벡터)
	2차원 벡터는 x, y 축만 있는 벡터공간을 말한다.
	Dimension(차원)

	64bit = double(공학)
	32bit = float(게임)
	basis vector(기저벡터)를 변형하는게 Linear Transformation(선형 벡터)이다.

	basis vector(기저벡터)를 Linear Transformation(선형 벡터)로 변환하는 방법.

	M(matrix) * V1 = V2

	m1, m2 * x = m1 * x + m3 * x + m2 * y + m4 * y
	m3, m4 * y

	행렬식(determinant) -> 역행렬 유무판단
	ad - bc = 0이면, 해가 없는 경우다.

	ad - bc
	
	어떤 벡터의 크기를 알려주는게 행렬이다.
	1. 항등행렬 ->	1 0 
					0 1

	//sin, cos 쓰는 이유//
		sin = c/b
		cos = c/a
		sin, cos 를 만든 사람 : 과학자 오일러

		항해술을 위해 발명이 되었다.

	아핀공간 -> 점과 벡터가 있는 공간
	P + v = P -> P - P = v
	
	P + P != P(예외 사항 aP1 + bP2 = P3)(단, a+b = 1)


	Barycentric Coordinate -> 삼각형의 중점을 구하는 공식?
	
*/

void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	static float theta = 0;
	static float pos = 0;
	static float scale = 1;

	// Input 
	if (GetAsyncKeyState(VK_LEFT)) theta -= 1;
	if (GetAsyncKeyState(VK_RIGHT)) theta += 1;
	if (GetAsyncKeyState(VK_UP)) pos += 1;
	if (GetAsyncKeyState(VK_DOWN)) pos -= 1;
	if (GetAsyncKeyState(VK_PRIOR)) scale += 0.01f;
	if (GetAsyncKeyState(VK_NEXT)) scale -= 0.01f;

	// Define Matrix
	Matrix3 tMat, rMat, sMat, trsMat;
	sMat.SetScale(scale, scale, 1);
	rMat.SetRotation(theta);
	tMat.SetTranslation(pos, pos);
	trsMat = tMat * rMat * sMat;

	// Draw
	SetColor(255, 0, 0);

	// Define Vector Space
	//Vector3 start = Vector3::Make2DPoint(-50, -50) * trsMat;
	//Vector3 end = Vector3::Make2DPoint(50, 50) * trsMat;
	//DrawLine(start, end);

	Vector3 p1 = Vector3::Make2DPoint(-80, -80) * trsMat;
	Vector3 p2 = Vector3::Make2DPoint(-80, 80) * trsMat;
	Vector3 p3 = Vector3::Make2DPoint(80, 80) * trsMat;
	Vector3 p4 = Vector3::Make2DPoint(80, -80) * trsMat;

	Vertex v1(p1, RGB32(255, 0, 0));
	Vertex v2(p2, RGB32(0, 255, 0));
	Vertex v3(p3, RGB32(0, 0, 255));
	Vertex v4(p4, RGB32(255, 255, 255));

	DrawTriangle(v1, v2, v3);
	DrawTriangle(v1, v3, v4);

	//DrawTriangle(p1, p2, p3);
	//DrawTriangle(p1, p3, p4);

	//float radius = 100.0f;
	//int nradius = (int)radius;
	//for (int i = -nradius; i <= nradius; i++)
	//{
	//	for (int j = -nradius; j <= nradius; j++)
	//	{
	//		PutPixel(Vector3((float)i, (float)j) * trsMat);
	//	}
	//}


	// Buffer Swap 
	BufferSwap();
}


//backup
//// Draw a filled circle with radius 100
//Vector3 center(0.0f, 0.0f);
//float radius = 100.0f;
//int nradius = (int)radius;
//
//static float degree = 0;
//degree += 1;
//degree = fmodf(degree, 360.0f);
//
//Matrix3 rotMat;
//rotMat.SetRotation(degree);
//rotMat.Transpose();
//
//float maxScale = 1;
//float scale = ((sinf(Deg2Rad(degree * 2)) + 1) * 0.5) * maxScale;
//if (scale < 0.5f) scale = 0.5f;
//
//Matrix3 scaleMat;
//scaleMat.SetScale(scale, scale, scale);
//
//float maxPos = 150;
//float pos = sinf(Deg2Rad(degree)) * maxPos;
//Matrix3 translationMat;
//translationMat.SetTranslation(pos, pos);
//
//Matrix3 SR = scaleMat * rotMat;
//Matrix3 TRS = translationMat * rotMat * scaleMat;
////Matrix3 SRT = scaleMat * rotMat * translationMat;
//
//for (int i = -nradius; i <= nradius; i++)
//{
//	for (int j = -nradius; j <= nradius; j++)
//	{
//		PutPixel(Vector3((float)i, (float)j) * TRS);
//	}
//}