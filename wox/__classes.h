#include "__patternfunc.h"
#include "GameClass.h"
LPD3DXLINE Line2;
D3DVIEWPORT9 viewport;
#pragma warning( disable : 4244)
float ScreenCenterX;
float ScreenCenterY;
#define Red       D3DCOLOR_XRGB(223,43,43)
#define Green     D3DCOLOR_ARGB(215,000,255,000)
#define Orange    D3DCOLOR_ARGB(255, 255, 140, 000)
#define Blue      D3DCOLOR_XRGB(68,80,248)
#define Yellow    D3DCOLOR_ARGB(255, 255, 255,  51)
#define Black     D3DCOLOR_ARGB(255, 000, 000, 000)
#define Grey      D3DCOLOR_ARGB(255, 112, 112, 112)
#define Gold      D3DCOLOR_ARGB(255, 255, 215, 000)
#define Pink      D3DCOLOR_ARGB(255, 255, 192, 203)
#define Purple    D3DCOLOR_ARGB(255, 128, 000, 128)
#define White     D3DCOLOR_ARGB(255, 255, 255, 249)
#define Cyan      D3DCOLOR_ARGB(255, 000, 255, 255)
#define Magenta   D3DCOLOR_ARGB(255, 255, 000, 255)
#define TBlack    D3DCOLOR_ARGB(128, 000, 000, 000)

void __fillrgb(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice)
{
	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}
VOID __drawborder(INT x, INT y, INT w, INT h, INT px, D3DCOLOR BorderColor, LPDIRECT3DDEVICE9 pDevice)
{
	__fillrgb(x, (y + h - px), w, px, BorderColor, pDevice);
	__fillrgb(x, y, px, h, BorderColor, pDevice);
	__fillrgb(x, y, w, px, BorderColor, pDevice);
	__fillrgb(x + w - px, y, px, h, BorderColor, pDevice);
}

void Box2D(D3DXVECTOR3 Head, D3DXVECTOR3 Foot, DWORD dwColor, LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR3 Box = Head - Foot;
	if (Box.y < 0)
		Box.y *= -1;
	int BoxWidth = (int)Box.y / 2;
	int DrawX = (int)Head.x - (BoxWidth / 2);
	int DrawY = (int)Head.y;
	if ((int)Box.y / 2 < (int)Box.y / 1.0)
		__drawborder(DrawX, DrawY, (int)Box.y / 2, (int)Box.y, (int)1.5f, dwColor, pDevice);
}

DWORD suckMe()
{
	DWORD pBase = (DWORD)(*(DWORD*)__myoffs::MemBaseAddr + __myoffs::PlayerSystemOffset);
	mWeaponSystem = (WeaponSystem*)pBase;
	mPlayerHealth = (PlayerHealth*)pBase;
	mPlayerPosData = (PlayerPosData*)pBase;
	mANet_Player = (ANet_player*)__myoffs::PlayerCountAddr;
	return 0;
}
std::string CheckEnemy()
{
	int XCheckEnemy = *(DWORD*)(*(DWORD*)__myoffs::MemBaseAddr + __myoffs::CheckEnemyOffset);
	if (XCheckEnemy == 1)
		return std::string(/*Zula*/XorStr<0x22, 5, 0x7883EDDC>("\x78\x56\x48\x44" + 0x7883EDDC).s);
	else
		return std::string(/*Gladyo*/XorStr<0x19, 7, 0xDFFD2E05>("\x5E\x76\x7A\x78\x64\x71" + 0xDFFD2E05).s);
}

struct __d3d_options
{
	int __menu_secimi, matrixPos[3], _simdiki;
	bool ShowMenu;
	LPD3DXFONT Font;
	LPD3DXFONT Font2;
	__d3d_options(void)
	{
		ShowMenu = 1;
		_simdiki = 1;
		matrixPos[0] = 30; //x1
		matrixPos[1] = 70; //y1
		matrixPos[2] = 60; //y2
		matrixPos[3] = 00; //x2
	}
}
__menu;
INT __var[MAX_PATH];
INT __fol[MAX_PATH];
struct IPlayer_t
{
	D3DXVECTOR3	pHeadGladio;
	D3DXVECTOR3	pHeadZula;
	float RealDistance;
	float CrosshairDistance;
};
std::vector<IPlayer_t*>IPlayerEsp;


void Nop(void* dst, unsigned int size)
{
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}
VOID __write_text(int _x, int _y, DWORD __color, const char *__text)
{
	RECT __rect;
	SetRect(&__rect, _x, _y, _x, _y);
	__menu.Font->DrawText(NULL, __text, -1, &__rect, DT_NOCLIP | DT_LEFT, __color);
}

VOID __esp_text(int _x, int _y, DWORD __color, const char *__text)
{
	RECT __rect;
	SetRect(&__rect, _x, _y, _x, _y);
	__menu.Font2->DrawText(NULL, __text, -1, &__rect, DT_NOCLIP | DT_CENTER, __color);
}
void DrawLine2(float StartX, float StartY, float EndX, float EndY, D3DCOLOR dColor)
{
	Line2[0].SetWidth(0.7f);
	Line2[0].SetGLLines(0);
	Line2[0].SetAntialias(0);

	D3DXVECTOR2 v2Line[2];
	v2Line[0].x = StartX;
	v2Line[0].y = StartY;
	v2Line[1].x = EndX;
	v2Line[1].y = EndY;

	Line2[0].Begin();
	Line2[0].Draw(v2Line, 2, dColor);
	Line2[0].End();
}

D3DXVECTOR3 GetMidPoint(D3DXVECTOR3 V1, D3DXVECTOR3 V2)
{
	D3DXVECTOR3 Mid;
	Mid.x = (V1.x + V2.x) / 2;
	Mid.y = (V1.y + V2.y) / 2;
	Mid.z = (V1.z + V2.z) / 2;
	return Mid;
}
bool Trans3DTo2D(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 *InOut)
{
	D3DXVECTOR3 vScreen;
	D3DXVECTOR3 PlayerPos(InOut->x, InOut->y, InOut->z);
	D3DVIEWPORT9 viewPort = { 0 };
	D3DXMATRIX projection, view, world;
	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &projection);
	pDevice->GetTransform(D3DTS_WORLD, &world);
	pDevice->GetViewport(&viewPort);
	D3DXVec3Project(&vScreen, &PlayerPos, &viewPort, &projection, &view, &world);
	if (vScreen.z < 1)
	{
		*InOut = vScreen;
		return true;
	}
	return false;
}	

int aimsmooth = 2;
float GetDistance(float Xx, float Yy, float xX, float yY)
{
	return sqrt((yY - Yy) * (yY - Yy) + (xX - Xx) * (xX - Xx));
}

float lvlsymX, lvlsymY, hpbarX, hpbarY, defaulthpbarX, defaulthpbarY;
bool recoil = true;
bool spread = true;
bool gunrapid = true;
bool sniprapid = true;
DWORD recoil_memory = NULL, recoil2_memory = NULL, spread_memory = NULL, rapidgun_memory = NULL, rapidsniper_memory = NULL;

void memory_active(DWORD hSigAddr, unsigned int nop_size)
{
	if (hSigAddr != NULL)
	{
		DWORD __recoil = hSigAddr;
		Nop((void*)__recoil, nop_size);
	}
}

void memory_deactive(DWORD hSigAddr, LPCVOID val)
{
	if (hSigAddr != NULL)
	{
		DWORD __recoil = hSigAddr;
		WriteProcessMemory(GetCurrentProcess(), (LPVOID)__recoil, val, 12, NULL);
	}
}

bool trec = true;
void __cheatloop(LPDIRECT3DDEVICE9 pDevice)
{
	_asm nop
	suckMe();
		if (__var[3] > 0)
		{
			__fillrgb(ScreenCenterX - 13, ScreenCenterY, 10, 1, Red, pDevice);//Left line
			__fillrgb(ScreenCenterX + 4, ScreenCenterY, 10, 1, Red, pDevice);//Right line
			__fillrgb(ScreenCenterX, ScreenCenterY - 13, 1, 10, Red, pDevice);//Top line
			__fillrgb(ScreenCenterX, ScreenCenterY + 4, 1, 10, Red, pDevice);//Bottom line
			__fillrgb(ScreenCenterX, ScreenCenterY - 1, 1, 1, Green, pDevice);//Dot point
		}


		if (IPlayerEsp.size() != NULL)
		{
			UINT BestTarget = -1;
			DOUBLE fClosestPos = 99999;
			
		
			for (unsigned int i = 0; i < IPlayerEsp.size(); i++)
			{
				char xxd2[64];
				float rdist = IPlayerEsp[i]->RealDistance;
				sprintf(xxd2, "Distance: %dm", static_cast<int>(rdist));

				if (__var[11] > 0)
				{
					__esp_text(IPlayerEsp[i]->pHeadGladio.x, IPlayerEsp[i]->pHeadGladio.y, Green, xxd2);
				}
				
				float radiusx = 90 * (ScreenCenterX / 100.0f);
				float radiusy = 90 * (ScreenCenterY / 100.0f);

				IPlayerEsp[i]->CrosshairDistance = GetDistance(IPlayerEsp[i]->pHeadGladio.x, IPlayerEsp[i]->pHeadGladio.y, ScreenCenterX, ScreenCenterY);

				if (IPlayerEsp[i]->pHeadGladio.x >= ScreenCenterX - radiusx &&
					IPlayerEsp[i]->pHeadGladio.x <= ScreenCenterX + radiusx &&
					IPlayerEsp[i]->pHeadGladio.y >= ScreenCenterY - radiusy && 
					IPlayerEsp[i]->pHeadGladio.y <= ScreenCenterY + radiusy)
					if (IPlayerEsp[i]->CrosshairDistance < fClosestPos)
					{
						fClosestPos = IPlayerEsp[i]->CrosshairDistance;
						BestTarget = i;
					}
			}

			if (BestTarget != -1)
			{
				hpbarX = IPlayerEsp[BestTarget]->pHeadGladio.x;
				hpbarY = IPlayerEsp[BestTarget]->pHeadGladio.y;
				defaulthpbarX = IPlayerEsp[BestTarget]->pHeadGladio.x;
				defaulthpbarY = IPlayerEsp[BestTarget]->pHeadGladio.y;
				
				if (IPlayerEsp[BestTarget]->pHeadGladio.x > (ScreenCenterX)) {
					hpbarX = (IPlayerEsp[BestTarget]->pHeadGladio.x - 56.0f);
				}

				else if (IPlayerEsp[BestTarget]->pHeadGladio.x < (ScreenCenterX)) {
					hpbarX = (IPlayerEsp[BestTarget]->pHeadGladio.x + 56.0f);
				}

				__write_text(hpbarX, IPlayerEsp[BestTarget]->pHeadGladio.y, Green, "lvl");
				double DistX = (double)IPlayerEsp[BestTarget]->pHeadGladio.x - viewport.Width / 2.0f;
				double DistY = (double)IPlayerEsp[BestTarget]->pHeadGladio.y - viewport.Height / 2.0f;

				aimsmooth /= DistX;
				aimsmooth /= DistY;
				if (GetAsyncKeyState(VK_CAPITAL) & 0x8000)
				{
					mouse_event(MOUSEEVENTF_MOVE, DistX, DistY, NULL, NULL);
				}
			}
			IPlayerEsp.clear();
		}

	_asm nop
}