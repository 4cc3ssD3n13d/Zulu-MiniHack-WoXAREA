#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <process.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <ostream>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <detours.h>
#include "__xor.h"
#include "__classes.h"
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3d9.lib")
#pragma warning( disable : 4244)
using namespace std;
const char* __aylar[] =
{
"Ocak", "Subat", "Mart", "Nisan", "Mayis", "Haziran",
"Temmuz", "Agustos", "Eylul", "Ekim", "Kasim", "Aralik"
};
CHAR __zaman_yapisi[MAX_PATH] = { "hh':'mm':'ss tt" };
CHAR __zaman_yazi[MAX_PATH];
const char *_ac_kapat[] = { "OFF", "ON" };
const char *_ac_kapat3[] = {  "BETA" ,"BETA"};
const char *_ac_kapat2[] = {  "ON" ,"ON"};
const char *_esp[] = { "OFF", "2D", "3D" };
const char *_enemy_select[] = { "Takým", "Herkes" };
IDirect3DVertexBuffer9 *pStreamData;
UINT XOffset = 0;
UINT LStride = 0;
IDirect3DVertexShader9* vShader;
UINT vSize;
bool setup = true;
#define GRASS pCount == 208
#define GLADYO  NumVertices == 3699 || NumVertices == 3214 || NumVertices == 3346 || NumVertices == 2968 || NumVertices == 3151 || NumVertices == 3653 || NumVertices == 3109 || NumVertices == 3610 || NumVertices == 3011
#define ZULA    NumVertices == 5672 || NumVertices == 2833 || NumVertices == 2531 || NumVertices == 2374 || NumVertices == 2503 || NumVertices == 3645 || NumVertices == 3108 || NumVertices == 2729 || NumVertices == 2714
#define ZULAMAX  NumVertices == 4847 || NumVertices == 4747 || NumVertices == 4847 || NumVertices == 4855 || NumVertices == 4913 || NumVertices == 5170 || NumVertices == 5180 || NumVertices == 5215 || NumVertices == 5296 || NumVertices == 5908 || NumVertices == 6126 || NumVertices == 6359
#define GLADYOMAX  NumVertices == 4915 || NumVertices == 4815 && NumVertices == 4915 || NumVertices == 4915 || NumVertices == 4969 || NumVertices == 5313 || NumVertices == 5486 || NumVertices == 5685 || NumVertices == 5697 || NumVertices == 6226 || NumVertices == 6305 || NumVertices == 6450 || NumVertices == 6467

unsigned int	uiStride = NULL;
LPD3DXFONT		g_pFont = NULL;
LPD3DXLINE		g_pLine = NULL;
D3DVIEWPORT9	g_ViewPort;

typedef HRESULT(WINAPI* tSetStreamSource)(LPDIRECT3DDEVICE9 pDevice, UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride);
tSetStreamSource oSetStreamSource;

typedef HRESULT(WINAPI* tEndScene)(LPDIRECT3DDEVICE9 pDevice);
tEndScene oEndScene;

typedef HRESULT(WINAPI* tDrawIndexedPrimitive)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);
tDrawIndexedPrimitive oDrawIndexedPrimitive;


void __add_cheat(const char *String, int MaxValue, int &Variable, int Folder, const char **Option)
{
	if (__menu.ShowMenu)
	{
		if (__menu.__menu_secimi == __menu._simdiki)
		{
			if (GetAsyncKeyState(0x27) & 1)
			{
				if (Variable < MaxValue)
					Variable++;
			}
			else if (GetAsyncKeyState(0x25) & 1)
			{
				if (Variable > 0)
					Variable--;
			}
		}

		if (__menu.__menu_secimi == __menu._simdiki)
		{
			__write_text(__menu.matrixPos[0] + 35, __menu.matrixPos[2] + (__menu._simdiki * 15), White, String); // Secilen
			__write_text(__menu.matrixPos[0] + 145, __menu.matrixPos[2] + (__menu._simdiki * 15), White, Option[Variable]);
		}
		else if (Variable > 0)
		{
			if (Folder == 1)
			{
				__write_text(__menu.matrixPos[0] + 20, __menu.matrixPos[2] + (__menu._simdiki * 15), Blue, String);
				__write_text(__menu.matrixPos[0] + 145, __menu.matrixPos[2] + (__menu._simdiki * 15), Blue, Option[Variable]);
			}
			else
			{
				__write_text(__menu.matrixPos[0] + 20, __menu.matrixPos[2] + (__menu._simdiki * 15), White, String);
				__write_text(__menu.matrixPos[0] + 145, __menu.matrixPos[2] + (__menu._simdiki * 15), White, Option[Variable]);
			}
		}
		else
		{
			if (Folder == 1)
			{
				__write_text(__menu.matrixPos[0] + 20, __menu.matrixPos[2] + (__menu._simdiki * 15), Blue, String);
				__write_text(__menu.matrixPos[0] + 145, __menu.matrixPos[2] + (__menu._simdiki * 15), Blue, Option[Variable]);
			}
			else
			{
				__write_text(__menu.matrixPos[0] + 20, __menu.matrixPos[2] + (__menu._simdiki * 15), White, String); // Tüm yazýlar
				__write_text(__menu.matrixPos[0] + 145, __menu.matrixPos[2] + (__menu._simdiki * 15), White, Option[Variable]); // Tüm yazýlar
			}
		}

		__menu._simdiki++;
	}
}


void DrawESPLine(float x1, float y1, float x2, float y2, float width, bool antialias, DWORD color,LPDIRECT3DDEVICE9 pDevice)
{
   D3DXCreateLine(pDevice, &g_pLine);
   D3DXVECTOR2 line[] = {D3DXVECTOR2(x1, y1), D3DXVECTOR2(x2, y2)};
   g_pLine->SetWidth(width);
   if(antialias) g_pLine->SetAntialias(1);
   g_pLine->Begin();
   g_pLine->Draw(line, 2, color);
   g_pLine->End();
   g_pLine->Release();
}

void MyEsp(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR4 vHead;
	D3DXMATRIX matrix, m1;
	D3DXVECTOR4 position;
	Device->GetVertexShaderConstantF(224, matrix, 4);
	D3DXMatrixTranspose(&matrix, &matrix);
	D3DXVec4Transform(&position, &vHead, &matrix);
	vHead.x = 0.0f;
	vHead.y = -33.f;
	vHead.z = 0.0f;
	vHead.w = 0.0f;
	position.x = vHead.x * matrix._11 + vHead.y * matrix._21 + vHead.z * matrix._31 + matrix._41;
	position.y = vHead.x * matrix._12 + vHead.y * matrix._22 + vHead.z * matrix._32 + matrix._42;
	position.z = vHead.x * matrix._13 + vHead.y * matrix._23 + vHead.z * matrix._33 + matrix._43;
	position.w = vHead.x * matrix._14 + vHead.y * matrix._24 + vHead.z * matrix._34 + matrix._44;
	float distanceX = vHead.x * matrix._14 + vHead.y * matrix._24 + vHead.z * matrix._34 + matrix._44;
	float RealDistanceX = (distanceX * 0.1f) - 7.f;
	char xxd2[64];
	sprintf(xxd2, "[© W O X A R E A ]: %dm", static_cast<int>(RealDistanceX));
	if (matrix._44 > 1.0f)
	{
		float xx = ((position.x / position.w) * (viewport.Width / 2)) + viewport.X + (viewport.Width / 2);
		float yy = viewport.Y + (viewport.Height / 2) - ((position.y / position.w) * (viewport.Height / 2));
		DrawESPLine(viewport.Width / 2.0f,viewport.Height,xx,yy - 5,1,false,White,Device);
		if (__var[11] > 0)
		{
			__esp_text((int)xx, (int)yy, Red, xxd2);
		}
	}
}
void MyEsp2(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR4 vHead;
	D3DXMATRIX matrix, m1;
	D3DXVECTOR4 position;
	Device->GetVertexShaderConstantF(224, matrix, 4);
	D3DXMatrixTranspose(&matrix, &matrix);
	D3DXVec4Transform(&position, &vHead, &matrix);
	vHead.x = 0.0f;
	vHead.y = -33.f;
	vHead.z = 0.0f;
	vHead.w = 0.0f;
	position.x = vHead.x * matrix._11 + vHead.y * matrix._21 + vHead.z * matrix._31 + matrix._41;
	position.y = vHead.x * matrix._12 + vHead.y * matrix._22 + vHead.z * matrix._32 + matrix._42;
	position.z = vHead.x * matrix._13 + vHead.y * matrix._23 + vHead.z * matrix._33 + matrix._43;
	position.w = vHead.x * matrix._14 + vHead.y * matrix._24 + vHead.z * matrix._34 + matrix._44;
	float distanceX = vHead.x * matrix._14 + vHead.y * matrix._24 + vHead.z * matrix._34 + matrix._44;
	float RealDistanceX = (distanceX * 0.1f) - 7.f;
	char xxd2[64];
		sprintf(xxd2, "[© W O X A R E A ]: %dm", static_cast<int>(RealDistanceX));
	


	if (matrix._44 > 1.0f)
	{
	
			float xx = ((position.x / position.w) * (viewport.Width / 2)) + viewport.X + (viewport.Width / 2);
		float yy = viewport.Y + (viewport.Height / 2) - ((position.y / position.w) * (viewport.Height / 2));
			

		if (__var[13] > 0)
		{
			__esp_text((int)xx, (int)yy, Green, xxd2);
		}
	}
}


void ShowMenu(LPDIRECT3DDEVICE9 __device)
{
	__device->GetViewport(&viewport);
	if (GetAsyncKeyState(VK_INSERT) & 1)
		__menu.ShowMenu = !__menu.ShowMenu;

	if (__menu.ShowMenu && __menu.Font)
	{
		std::string str = ".::Zula Wox Mini Hack 1.0::.";
			

		

		char *cstr = new char[str.length() + 1];
		strcpy(cstr, str.c_str());


			std::string str2 = "[Credit / © WOXAREA.NET]";


		char *aaa = new char[str2.length() + 1];
		
		strcpy(aaa, str2.c_str());
		

		
		__fillrgb(__menu.matrixPos[0] - 5,    __menu.matrixPos[1] - 27, 200, ((__menu._simdiki * 15) + 50), Black, __device);// Hile arkaplan

		__drawborder(__menu.matrixPos[0] - 5, __menu.matrixPos[1] - 27, 200, ((__menu._simdiki * 15) + 50), 1, White, __device);// Hile Border

		__fillrgb(__menu.matrixPos[0],        __menu.matrixPos[1] - 22, 190, ((__menu._simdiki * 15) + 40), Black, __device);// Hile arkaplan
				__drawborder(__menu.matrixPos[0],     __menu.matrixPos[1] - 22, 190, ((__menu._simdiki * 15) + 40), 1, White, __device);// Hile Border
		
		__drawborder(__menu.matrixPos[0],     __menu.matrixPos[1] - 62, 320, ((__menu._simdiki * 3) + 1), 1, White, __device);// Hile Border Yukardaki þey

		__write_text(__menu.matrixPos[0] + 50, __menu.matrixPos[1] - 19, White, cstr); // Title text
				__write_text(__menu.matrixPos[0] + 10, __menu.matrixPos[2] - 50, White, aaa); // Title text

		__drawborder(__menu.matrixPos[0],      __menu.matrixPos[1] - 22, 190, 20, 1, White, __device); // Title border

		__drawborder(__menu.matrixPos[0] + 10, ((__menu.matrixPos[2]) + (__menu.__menu_secimi * 15)), 175, 16, 2, White, __device); // Selection
		__menu._simdiki = 1;
		if (GetAsyncKeyState(0x26) & 1)
			__menu.__menu_secimi--;

		if (GetAsyncKeyState(0x28) & 1)
			__menu.__menu_secimi++;

		__add_cheat(/*Esp Wall*/XorStr<0x47, 9, 0x2CAE7FFE>("\x02\x3B\x39\x6A\x1C\x2D\x21\x22" + 0x2CAE7FFE).s, 1, __var[0], 0, _ac_kapat);
		__add_cheat(/*Esp Box*/XorStr<0x91, 8, 0x5A86826C>("\xD4\xE1\xE3\xB4\xD7\xF9\xEF" + 0x5A86826C).s, 1, __var[1], 0, _ac_kapat);
		__add_cheat(/*Esp Distance*/XorStr<0xD3, 13, 0xAABF9CBC>("\x96\xA7\xA5\xF6\x93\xB1\xAA\xAE\xBA\xB2\xBE\xBB" + 0xAABF9CBC).s, 1, __var[11], 0, _ac_kapat);
			__add_cheat("Esp Distance Green", 1, __var[13], 0, _ac_kapat);
							__add_cheat("Esp Line", 1, __var[99], 0, _ac_kapat2);
					
			
		__add_cheat(/*Team Select*/XorStr<0xD7, 12, 0x9184F5AD>("\x83\xBD\xB8\xB7\xFB\x8F\xB8\xB2\xBA\x83\x95" + 0x9184F5AD).s, 1, __var[2], 0, _enemy_select);
			
		__add_cheat(/*Crosshair*/XorStr<0x6B, 10, 0xE85ABF5C>("\x28\x1E\x02\x1D\x1C\x18\x10\x1B\x01" + 0xE85ABF5C).s, 1, __var[3], 0, _ac_kapat);
		__add_cheat("Aimbot [BETA]", 2, __var[55], 0, _ac_kapat3);
	

			
		
				




		
		if (__menu.__menu_secimi >= __menu._simdiki)
			__menu.__menu_secimi = 1;
		else if (__menu.__menu_secimi <= 0)
			__menu.__menu_secimi = (__menu._simdiki - 1);
	}

	ScreenCenterX = viewport.Width / 2.0f;
	ScreenCenterY = viewport.Height / 2.0f;
	__cheatloop(__device);
}

HRESULT WINAPI hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (g_pFont == NULL) D3DXCreateFont(pDevice, 15, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Verdana", &g_pFont);
	if (g_pLine == NULL) D3DXCreateLine(pDevice, &g_pLine);

	if (setup) {
		__menu.__menu_secimi = 1;
		D3DXCreateLine(pDevice, &Line2);
		D3DXCreateFontA(pDevice, 14, 5, FW_NORMAL, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, "Tahoma", &__menu.Font);
		D3DXCreateFontA(pDevice, 11, 5, FW_BOLD, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, "Tahoma", &__menu.Font2);
		setup = false;
	}

	pDevice->GetViewport(&g_ViewPort);

	if (g_pFont != NULL && g_pLine != NULL){
		ShowMenu(pDevice);
	}
	return oEndScene(pDevice);
}


HRESULT WINAPI hkDrawIndexedPrimitive(LPDIRECT3DDEVICE9 Device, D3DPRIMITIVETYPE PrimType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT PrimitiveCount)
{
	__asm nop
	HRESULT hRet = oDrawIndexedPrimitive(Device, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, PrimitiveCount);
	if (Device->GetStreamSource(0, &pStreamData, &XOffset, &LStride) == D3D_OK)
		if (pStreamData != NULL) { pStreamData->Release(); pStreamData = NULL; }
	if (SUCCEEDED(Device->GetVertexShader(&vShader)))
		if (vShader != NULL)
			if (SUCCEEDED(vShader->GetFunction(NULL, &vSize)))
				if (vShader != NULL) { vShader->Release(); vShader = NULL; }
	if (__var[0] > 0)
	{
		if (GLADYO && ZULA && ZULAMAX && GLADYOMAX)
		{
			Device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
			Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);		
			oDrawIndexedPrimitive(Device, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, PrimitiveCount);
			Device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		}
	}
	if (__var[2] < 1)
	{
		if (CheckEnemy() == "Zula")
			if (GLADYO && GLADYOMAX)
				MyEsp(Device);
			MyEsp2(Device);
	
			
		if (CheckEnemy() == "Gladyo")
			if (ZULA && ZULAMAX)
				MyEsp(Device);
			MyEsp2(Device);
		
	}

	if (__var[2] > 0)
	{
		if (CheckEnemy() == "Zula") {
			if (GLADYO && GLADYOMAX)
				MyEsp(Device);
			if (ZULA && ZULAMAX)
				MyEsp(Device);
				MyEsp2(Device);
		
		}
		if (CheckEnemy() == "Gladyo") {
			if (ZULA && ZULAMAX)
				MyEsp(Device);
				MyEsp2(Device);
			
			if (GLADYO && GLADYOMAX)
				MyEsp(Device);
				MyEsp2(Device);
					
		}
		if (__var[1] > 0)
		{
			int xz = 15;
			int uzunluk = xz * 2;
			if (__var[2] < 1)
			{
				if (CheckEnemy() == "Zula")
				{
					if (GLADYO && GLADYOMAX)
					{
						D3DXVECTOR3 vHead(0, 28.f, 0); D3DXVECTOR3 vFeet(0, -31.f, 0);
						{
							D3DXMATRIX projection, view, world;
							D3DXVECTOR3 vScreenCoord(0, 28.f, 0);
							Device->GetTransform(D3DTS_VIEW, &view);
							Device->GetTransform(D3DTS_PROJECTION, &projection);
							Device->GetTransform(D3DTS_WORLD, &world);

							D3DXVec3Project(&vScreenCoord, &vHead, &viewport, &projection, &view, &world);
						}

						{
							D3DXVECTOR3 vScreenCoord(0, -31.f, 0);
							D3DXMATRIX projection, view, world;
							Device->GetTransform(D3DTS_VIEW, &view);
							Device->GetTransform(D3DTS_PROJECTION, &projection);
							Device->GetTransform(D3DTS_WORLD, &world);

							D3DXVec3Project(&vScreenCoord, &vFeet, &viewport, &projection, &view, &world);
						}

						D3DXVECTOR3 Pos0, Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8;
						Pos0 = GetMidPoint(vHead, vFeet);
						DrawLine2(ScreenCenterX, ScreenCenterY, Pos0.x, Pos0.y, Red);
						Pos1 = Pos0 + D3DXVECTOR3(-xz, uzunluk, -xz);
						Pos2 = Pos0 + D3DXVECTOR3(-xz, -uzunluk, -xz);
						Pos3 = Pos0 + D3DXVECTOR3(xz, -uzunluk, -xz);
						Pos4 = Pos0 + D3DXVECTOR3(xz, uzunluk, -xz);
						Pos5 = Pos0 + D3DXVECTOR3(-xz, uzunluk, xz);
						Pos6 = Pos0 + D3DXVECTOR3(-xz, -uzunluk, xz);
						Pos7 = Pos0 + D3DXVECTOR3(xz, -uzunluk, xz);
						Pos8 = Pos0 + D3DXVECTOR3(xz, uzunluk, xz);

						if (Trans3DTo2D(Device, &Pos1) && Trans3DTo2D(Device, &Pos2) &&
							Trans3DTo2D(Device, &Pos3) && Trans3DTo2D(Device, &Pos4) &&
							Trans3DTo2D(Device, &Pos5) && Trans3DTo2D(Device, &Pos6) &&
							Trans3DTo2D(Device, &Pos7) && Trans3DTo2D(Device, &Pos8))
						{
							if (__var[1] > 0)
							{
								DrawLine2(Pos1.x, Pos1.y, Pos2.x, Pos2.y, Purple);
								DrawLine2(Pos2.x, Pos2.y, Pos3.x, Pos3.y, Purple);
								DrawLine2(Pos3.x, Pos3.y, Pos4.x, Pos4.y, Purple);
								DrawLine2(Pos4.x, Pos4.y, Pos1.x, Pos1.y, Purple);
								DrawLine2(Pos5.x, Pos5.y, Pos6.x, Pos6.y, Purple);
								DrawLine2(Pos6.x, Pos6.y, Pos7.x, Pos7.y, Purple);
								DrawLine2(Pos7.x, Pos7.y, Pos8.x, Pos8.y, Purple);
								DrawLine2(Pos8.x, Pos8.y, Pos5.x, Pos5.y, Purple);
								DrawLine2(Pos1.x, Pos1.y, Pos5.x, Pos5.y, Purple);
								DrawLine2(Pos2.x, Pos2.y, Pos6.x, Pos6.y, Purple);
								DrawLine2(Pos3.x, Pos3.y, Pos7.x, Pos7.y, Purple);
								DrawLine2(Pos4.x, Pos4.y, Pos8.x, Pos8.y, Purple);
							}
						}
					}
				}
				if (CheckEnemy() == "Gladyo")
				{
					if (ZULA && ZULAMAX)
					{
						D3DXVECTOR3 vHead(0, 28.f, 0); D3DXVECTOR3 vFeet(0, -31.f, 0);
						{
							D3DXMATRIX projection, view, world;
							D3DXVECTOR3 vScreenCoord(0, 28.f, 0);
							Device->GetTransform(D3DTS_VIEW, &view);
							Device->GetTransform(D3DTS_PROJECTION, &projection);
							Device->GetTransform(D3DTS_WORLD, &world);

							D3DXVec3Project(&vScreenCoord, &vHead, &viewport, &projection, &view, &world);
						}

						{
							D3DXVECTOR3 vScreenCoord(0, -31.f, 0);
							D3DXMATRIX projection, view, world;
							Device->GetTransform(D3DTS_VIEW, &view);
							Device->GetTransform(D3DTS_PROJECTION, &projection);
							Device->GetTransform(D3DTS_WORLD, &world);

							D3DXVec3Project(&vScreenCoord, &vFeet, &viewport, &projection, &view, &world);
						}

						D3DXVECTOR3 Pos0, Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8;
						Pos0 = GetMidPoint(vHead, vFeet);
						Pos1 = Pos0 + D3DXVECTOR3(-xz, uzunluk, -xz);
						Pos2 = Pos0 + D3DXVECTOR3(-xz, -uzunluk, -xz);
						Pos3 = Pos0 + D3DXVECTOR3(xz, -uzunluk, -xz);
						Pos4 = Pos0 + D3DXVECTOR3(xz, uzunluk, -xz);
						Pos5 = Pos0 + D3DXVECTOR3(-xz, uzunluk, xz);
						Pos6 = Pos0 + D3DXVECTOR3(-xz, -uzunluk, xz);
						Pos7 = Pos0 + D3DXVECTOR3(xz, -uzunluk, xz);
						Pos8 = Pos0 + D3DXVECTOR3(xz, uzunluk, xz);

						if (Trans3DTo2D(Device, &Pos1) && Trans3DTo2D(Device, &Pos2) &&
							Trans3DTo2D(Device, &Pos3) && Trans3DTo2D(Device, &Pos4) &&
							Trans3DTo2D(Device, &Pos5) && Trans3DTo2D(Device, &Pos6) &&
							Trans3DTo2D(Device, &Pos7) && Trans3DTo2D(Device, &Pos8))
						{
							if (__var[1] > 0)
							{
								DrawLine2(Pos1.x, Pos1.y, Pos2.x, Pos2.y, Purple);
								DrawLine2(Pos2.x, Pos2.y, Pos3.x, Pos3.y, Purple);
								DrawLine2(Pos3.x, Pos3.y, Pos4.x, Pos4.y, Purple);
								DrawLine2(Pos4.x, Pos4.y, Pos1.x, Pos1.y, Purple);
								DrawLine2(Pos5.x, Pos5.y, Pos6.x, Pos6.y, Purple);
								DrawLine2(Pos6.x, Pos6.y, Pos7.x, Pos7.y, Purple);
								DrawLine2(Pos7.x, Pos7.y, Pos8.x, Pos8.y, Purple);
								DrawLine2(Pos8.x, Pos8.y, Pos5.x, Pos5.y, Purple);
								DrawLine2(Pos1.x, Pos1.y, Pos5.x, Pos5.y, Purple);
								DrawLine2(Pos2.x, Pos2.y, Pos6.x, Pos6.y, Purple);
								DrawLine2(Pos3.x, Pos3.y, Pos7.x, Pos7.y, Purple);
								DrawLine2(Pos4.x, Pos4.y, Pos8.x, Pos8.y, Purple);
							}
						}
					}
				}
			}
			if (__var[2] > 0)
			{
				if (CheckEnemy() == "Zula")
				{
					if (GLADYO && GLADYOMAX)
					{
						D3DXVECTOR3 vHead(0, 28.f, 0); D3DXVECTOR3 vFeet(0, -31.f, 0);
						{
							D3DXMATRIX projection, view, world;
							D3DXVECTOR3 vScreenCoord(0, 28.f, 0);
							Device->GetTransform(D3DTS_VIEW, &view);
							Device->GetTransform(D3DTS_PROJECTION, &projection);
							Device->GetTransform(D3DTS_WORLD, &world);

							D3DXVec3Project(&vScreenCoord, &vHead, &viewport, &projection, &view, &world);
						}

						{
							D3DXVECTOR3 vScreenCoord(0, -31.f, 0);
							D3DXMATRIX projection, view, world;
							Device->GetTransform(D3DTS_VIEW, &view);
							Device->GetTransform(D3DTS_PROJECTION, &projection);
							Device->GetTransform(D3DTS_WORLD, &world);

							D3DXVec3Project(&vScreenCoord, &vFeet, &viewport, &projection, &view, &world);
						}

						D3DXVECTOR3 Pos0, Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8;
						Pos0 = GetMidPoint(vHead, vFeet);
						Pos1 = Pos0 + D3DXVECTOR3(-xz, uzunluk, -xz);
						Pos2 = Pos0 + D3DXVECTOR3(-xz, -uzunluk, -xz);
						Pos3 = Pos0 + D3DXVECTOR3(xz, -uzunluk, -xz);
						Pos4 = Pos0 + D3DXVECTOR3(xz, uzunluk, -xz);
						Pos5 = Pos0 + D3DXVECTOR3(-xz, uzunluk, xz);
						Pos6 = Pos0 + D3DXVECTOR3(-xz, -uzunluk, xz);
						Pos7 = Pos0 + D3DXVECTOR3(xz, -uzunluk, xz);
						Pos8 = Pos0 + D3DXVECTOR3(xz, uzunluk, xz);
						if (Trans3DTo2D(Device, &Pos1) && Trans3DTo2D(Device, &Pos2) &&
							Trans3DTo2D(Device, &Pos3) && Trans3DTo2D(Device, &Pos4) &&
							Trans3DTo2D(Device, &Pos5) && Trans3DTo2D(Device, &Pos6) &&
							Trans3DTo2D(Device, &Pos7) && Trans3DTo2D(Device, &Pos8))
						{
							if (__var[1] > 0)
							{
								DrawLine2(Pos1.x, Pos1.y, Pos2.x, Pos2.y, Purple);
								DrawLine2(Pos2.x, Pos2.y, Pos3.x, Pos3.y, Purple);
								DrawLine2(Pos3.x, Pos3.y, Pos4.x, Pos4.y, Purple);
								DrawLine2(Pos4.x, Pos4.y, Pos1.x, Pos1.y, Purple);
								DrawLine2(Pos5.x, Pos5.y, Pos6.x, Pos6.y, Purple);
								DrawLine2(Pos6.x, Pos6.y, Pos7.x, Pos7.y, Purple);
								DrawLine2(Pos7.x, Pos7.y, Pos8.x, Pos8.y, Purple);
								DrawLine2(Pos8.x, Pos8.y, Pos5.x, Pos5.y, Purple);
								DrawLine2(Pos1.x, Pos1.y, Pos5.x, Pos5.y, Purple);
								DrawLine2(Pos2.x, Pos2.y, Pos6.x, Pos6.y, Purple);
								DrawLine2(Pos3.x, Pos3.y, Pos7.x, Pos7.y, Purple);
								DrawLine2(Pos4.x, Pos4.y, Pos8.x, Pos8.y, Purple);
							}
						}
					}
					if (ZULA && ZULAMAX)
					{
						D3DXVECTOR3 vHead(0, 28.f, 0); D3DXVECTOR3 vFeet(0, -31.f, 0);
						{
							D3DXMATRIX projection, view, world;
							D3DXVECTOR3 vScreenCoord(0, 28.f, 0);
							Device->GetTransform(D3DTS_VIEW, &view);
							Device->GetTransform(D3DTS_PROJECTION, &projection);
							Device->GetTransform(D3DTS_WORLD, &world);

							D3DXVec3Project(&vScreenCoord, &vHead, &viewport, &projection, &view, &world);
						}
						{
							D3DXVECTOR3 vScreenCoord(0, -31.f, 0);
							D3DXMATRIX projection, view, world;
							Device->GetTransform(D3DTS_VIEW, &view);
							Device->GetTransform(D3DTS_PROJECTION, &projection);
							Device->GetTransform(D3DTS_WORLD, &world);

							D3DXVec3Project(&vScreenCoord, &vFeet, &viewport, &projection, &view, &world);
						}

						D3DXVECTOR3 Pos0, Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8;
						Pos0 = GetMidPoint(vHead, vFeet);
						Pos1 = Pos0 + D3DXVECTOR3(-xz, uzunluk, -xz);
						Pos2 = Pos0 + D3DXVECTOR3(-xz, -uzunluk, -xz);
						Pos3 = Pos0 + D3DXVECTOR3(xz, -uzunluk, -xz);
						Pos4 = Pos0 + D3DXVECTOR3(xz, uzunluk, -xz);
						Pos5 = Pos0 + D3DXVECTOR3(-xz, uzunluk, xz);
						Pos6 = Pos0 + D3DXVECTOR3(-xz, -uzunluk, xz);
						Pos7 = Pos0 + D3DXVECTOR3(xz, -uzunluk, xz);
						Pos8 = Pos0 + D3DXVECTOR3(xz, uzunluk, xz);

						if (Trans3DTo2D(Device, &Pos1) && Trans3DTo2D(Device, &Pos2) &&
							Trans3DTo2D(Device, &Pos3) && Trans3DTo2D(Device, &Pos4) &&
							Trans3DTo2D(Device, &Pos5) && Trans3DTo2D(Device, &Pos6) &&
							Trans3DTo2D(Device, &Pos7) && Trans3DTo2D(Device, &Pos8))
						{
							if (__var[1] > 0)
							{
								DrawLine2(Pos1.x, Pos1.y, Pos2.x, Pos2.y, Blue);
								DrawLine2(Pos2.x, Pos2.y, Pos3.x, Pos3.y, Blue);
								DrawLine2(Pos3.x, Pos3.y, Pos4.x, Pos4.y, Blue);
								DrawLine2(Pos4.x, Pos4.y, Pos1.x, Pos1.y, Blue);
								DrawLine2(Pos5.x, Pos5.y, Pos6.x, Pos6.y, Blue);
								DrawLine2(Pos6.x, Pos6.y, Pos7.x, Pos7.y, Blue);
								DrawLine2(Pos7.x, Pos7.y, Pos8.x, Pos8.y, Blue);
								DrawLine2(Pos8.x, Pos8.y, Pos5.x, Pos5.y, Blue);
								DrawLine2(Pos1.x, Pos1.y, Pos5.x, Pos5.y, Blue);
								DrawLine2(Pos2.x, Pos2.y, Pos6.x, Pos6.y, Blue);
								DrawLine2(Pos3.x, Pos3.y, Pos7.x, Pos7.y, Blue);
								DrawLine2(Pos4.x, Pos4.y, Pos8.x, Pos8.y, Blue);
							}
						}
					}
				}
				if (CheckEnemy() == "Gladyo")
				{
					if (ZULA && ZULAMAX)
					{
						D3DXVECTOR3 vHead(0, 28.f, 0); D3DXVECTOR3 vFeet(0, -31.f, 0);
						{
							D3DXMATRIX projection, view, world;
							D3DXVECTOR3 vScreenCoord(0, 28.f, 0);
							Device->GetTransform(D3DTS_VIEW, &view);
							Device->GetTransform(D3DTS_PROJECTION, &projection);
							Device->GetTransform(D3DTS_WORLD, &world);

							D3DXVec3Project(&vScreenCoord, &vHead, &viewport, &projection, &view, &world);
						}

						{
							D3DXVECTOR3 vScreenCoord(0, -31.f, 0);
							D3DXMATRIX projection, view, world;
							Device->GetTransform(D3DTS_VIEW, &view);
							Device->GetTransform(D3DTS_PROJECTION, &projection);
							Device->GetTransform(D3DTS_WORLD, &world);

							D3DXVec3Project(&vScreenCoord, &vFeet, &viewport, &projection, &view, &world);
						}

						D3DXVECTOR3 Pos0, Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8;
						Pos0 = GetMidPoint(vHead, vFeet);
						Pos1 = Pos0 + D3DXVECTOR3(-xz, uzunluk, -xz);
						Pos2 = Pos0 + D3DXVECTOR3(-xz, -uzunluk, -xz);
						Pos3 = Pos0 + D3DXVECTOR3(xz, -uzunluk, -xz);
						Pos4 = Pos0 + D3DXVECTOR3(xz, uzunluk, -xz);
						Pos5 = Pos0 + D3DXVECTOR3(-xz, uzunluk, xz);
						Pos6 = Pos0 + D3DXVECTOR3(-xz, -uzunluk, xz);
						Pos7 = Pos0 + D3DXVECTOR3(xz, -uzunluk, xz);
						Pos8 = Pos0 + D3DXVECTOR3(xz, uzunluk, xz);

						if (Trans3DTo2D(Device, &Pos1) && Trans3DTo2D(Device, &Pos2) &&
							Trans3DTo2D(Device, &Pos3) && Trans3DTo2D(Device, &Pos4) &&
							Trans3DTo2D(Device, &Pos5) && Trans3DTo2D(Device, &Pos6) &&
							Trans3DTo2D(Device, &Pos7) && Trans3DTo2D(Device, &Pos8))
						{
							if (__var[1] > 0)
							{
								DrawLine2(Pos1.x, Pos1.y, Pos2.x, Pos2.y, Purple);
								DrawLine2(Pos2.x, Pos2.y, Pos3.x, Pos3.y, Purple);
								DrawLine2(Pos3.x, Pos3.y, Pos4.x, Pos4.y, Purple);
								DrawLine2(Pos4.x, Pos4.y, Pos1.x, Pos1.y, Purple);
								DrawLine2(Pos5.x, Pos5.y, Pos6.x, Pos6.y, Purple);
								DrawLine2(Pos6.x, Pos6.y, Pos7.x, Pos7.y, Purple);
								DrawLine2(Pos7.x, Pos7.y, Pos8.x, Pos8.y, Purple);
								DrawLine2(Pos8.x, Pos8.y, Pos5.x, Pos5.y, Purple);
								DrawLine2(Pos1.x, Pos1.y, Pos5.x, Pos5.y, Purple);
								DrawLine2(Pos2.x, Pos2.y, Pos6.x, Pos6.y, Purple);
								DrawLine2(Pos3.x, Pos3.y, Pos7.x, Pos7.y, Purple);
								DrawLine2(Pos4.x, Pos4.y, Pos8.x, Pos8.y, Purple);
							}
						}
					}
					if (GLADYO && GLADYOMAX)
					{
						D3DXVECTOR3 vHead(0, 28.f, 0); D3DXVECTOR3 vFeet(0, -31.f, 0);
						{
							D3DXMATRIX projection, view, world;
							D3DXVECTOR3 vScreenCoord(0, 28.f, 0);
							Device->GetTransform(D3DTS_VIEW, &view);
							Device->GetTransform(D3DTS_PROJECTION, &projection);
							Device->GetTransform(D3DTS_WORLD, &world);

							D3DXVec3Project(&vScreenCoord, &vHead, &viewport, &projection, &view, &world);
						}

						{
							D3DXVECTOR3 vScreenCoord(0, -31.f, 0);
							D3DXMATRIX projection, view, world;
							Device->GetTransform(D3DTS_VIEW, &view);
							Device->GetTransform(D3DTS_PROJECTION, &projection);
							Device->GetTransform(D3DTS_WORLD, &world);

							D3DXVec3Project(&vScreenCoord, &vFeet, &viewport, &projection, &view, &world);
						}
						D3DXVECTOR3 Pos0, Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8;
						Pos0 = GetMidPoint(vHead, vFeet);
						Pos1 = Pos0 + D3DXVECTOR3(-xz, uzunluk, -xz);
						Pos2 = Pos0 + D3DXVECTOR3(-xz, -uzunluk, -xz);
						Pos3 = Pos0 + D3DXVECTOR3(xz, -uzunluk, -xz);
						Pos4 = Pos0 + D3DXVECTOR3(xz, uzunluk, -xz);
						Pos5 = Pos0 + D3DXVECTOR3(-xz, uzunluk, xz);
						Pos6 = Pos0 + D3DXVECTOR3(-xz, -uzunluk, xz);
						Pos7 = Pos0 + D3DXVECTOR3(xz, -uzunluk, xz);
						Pos8 = Pos0 + D3DXVECTOR3(xz, uzunluk, xz);

						if (Trans3DTo2D(Device, &Pos1) && Trans3DTo2D(Device, &Pos2) &&
							Trans3DTo2D(Device, &Pos3) && Trans3DTo2D(Device, &Pos4) &&
							Trans3DTo2D(Device, &Pos5) && Trans3DTo2D(Device, &Pos6) &&
							Trans3DTo2D(Device, &Pos7) && Trans3DTo2D(Device, &Pos8))
						{
							if (__var[1] > 0)
							{
								DrawLine2(Pos1.x, Pos1.y, Pos2.x, Pos2.y, Green);
								DrawLine2(Pos2.x, Pos2.y, Pos3.x, Pos3.y, Green);
								DrawLine2(Pos3.x, Pos3.y, Pos4.x, Pos4.y, Green);
								DrawLine2(Pos4.x, Pos4.y, Pos1.x, Pos1.y, Green);
								DrawLine2(Pos5.x, Pos5.y, Pos6.x, Pos6.y, Green);
								DrawLine2(Pos6.x, Pos6.y, Pos7.x, Pos7.y, Green);
								DrawLine2(Pos7.x, Pos7.y, Pos8.x, Pos8.y, Green);
								DrawLine2(Pos8.x, Pos8.y, Pos5.x, Pos5.y, Green);
								DrawLine2(Pos1.x, Pos1.y, Pos5.x, Pos5.y, Green);
								DrawLine2(Pos2.x, Pos2.y, Pos6.x, Pos6.y, Green);
								DrawLine2(Pos3.x, Pos3.y, Pos7.x, Pos7.y, Green);
								DrawLine2(Pos4.x, Pos4.y, Pos8.x, Pos8.y, Green);
							}
						}
					}
				}
			}	
	}
}
	return hRet;
}

HRESULT WINAPI hkSetStreamSource(LPDIRECT3DDEVICE9 pDevice, UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)
{
	__asm nop

	if (StreamNumber == 0){
		uiStride = Stride;
	}

	return oSetStreamSource(pDevice, StreamNumber, pStreamData, OffsetInBytes, Stride);
}

LRESULT CALLBACK MsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){ return DefWindowProc(hwnd, uMsg, wParam, lParam); }
#define HOOK(func,addy)	o##func = (t##func)DetourFunction((PBYTE)addy,(PBYTE)hk##func)
#define ES	0
#define DIP	1
#define SSS	2
void DX_Init(DWORD* table)
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassEx(&wc);
	HWND hWnd = CreateWindow("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	LPDIRECT3D9 pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	LPDIRECT3DDEVICE9 pd3dDevice;
	pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice);
	DWORD* pVTable = (DWORD*)pd3dDevice;
	pVTable = (DWORD*)pVTable[0];
	table[ES] = pVTable[42];
	table[DIP] = pVTable[82];
	table[SSS] = pVTable[100];
	DestroyWindow(hWnd);
}

DWORD WINAPI MyThread(LPVOID)
{
	DWORD VTable[3] = { 0 };
	while (GetModuleHandle("d3d9.dll") == NULL){
		Sleep(250);
	}
	DX_Init(VTable);
	HOOK(EndScene, VTable[ES]);
	HOOK(DrawIndexedPrimitive, VTable[DIP]);
	HOOK(SetStreamSource, VTable[SSS]);
	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH){
		CreateThread(0, 0, MyThread, 0, 0, 0);
	}
	return TRUE;
}