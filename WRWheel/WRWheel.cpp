#include "plugin.h"
#include "CFileLoader.h"
#include "CSprite2d.h"
#include "CWorld.h"
#include <iomanip>
#include <iostream>
#include "CFont.h"
#include "common.h"
#include "CPlayerPed.h"
#include "ScreenAddons.h"
#include "CTimer.h"
#include "CHud.h"
using namespace plugin;
using namespace std;
class WRWheel {
public:
	WRWheel() {
		static RwTexDictionary *ring = nullptr;
		static RwTexDictionary *radio = nullptr;
		static CSprite2d bg, hl, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12;
		static CSprite2d radiot;
		static double sw, sh, st, sd, a, b, c, d;
		static unsigned char w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12;
		Events::initRwEvent += [&] {
			//config_file conf(PLUGIN_PATH("recthud.ini"));
			ring = CFileLoader::LoadTexDictionary(GAME_PATH("rect_hud_charlesvercetti\\ring_iii.txd"));
			radio = CFileLoader::LoadTexDictionary(GAME_PATH("rect_hud_charlesvercetti\\radio_iii.txd"));
			Events::drawingEvent += [&] {
				CPlayerPed* pla = FindPlayerPed();
				CVehicle* veh = FindPlayerVehicle();
				int weps = pla->m_nWepSlot;
				eWeaponType WeaponType = pla->m_aWeapons[weps].m_nType;
				int shot = pla ? pla->m_aWeapons[weps].m_nAmmoInClip : 0;
				int tot = pla ? pla->m_aWeapons[weps].m_nTotalAmmo : 0;
				int rad = veh ? veh->m_nRadioStation : 0;
				int driveConf = veh ? veh->bDriving : 0;
				int vehId =veh? veh->m_nModelIndex : 0;

				string names[13] = { "Unarmed","Baseball Bat", "Colt.45","Uzi" ,"Shotgun"," AK - 47"," M16", "Sniper Rifle",
					"Rocket Launcher", "Flamethrower", "MolotovCocktail","Grenade","RemoteDetonator" };
				string radios[12] = { "Head Radio", "Double Clef FM","K - Jah","Rise FM", "Lips 106", "Game FM", "MSX FM",
					 "Flashback 95.6","Chatterbox FM","MP3 Player","CD Player(XBox)","OFF"};

				sh = screen::GetScreenMaxY();
				sw = screen::GetScreenMaxX();
				sd = sw / sh;
				float sx, sy;
				sx = 0.9 / (sd / (4.0f / 3.0f));
				sy = 1.8 / (sd / (4.0f / 3.0f));
				int clip, ammo;
				if (WeaponType == WEAPONTYPE_FLAMETHROWER) {
					clip = shot / 10;

					if ((tot - shot) / 10 <= 9999)
						ammo = (tot - shot) / 10;
					else
						ammo = 9999;
				}
				else if (WeaponType == WEAPONTYPE_ROCKETLAUNCHER || WeaponType == WEAPONTYPE_SNIPERRIFLE ||
					WeaponType == WEAPONTYPE_GRENADE || WeaponType == WEAPONTYPE_MOLOTOV)
				{
					clip = shot;

					if ((tot - shot) >= 99999)
						ammo = 99999;
					else
						ammo = tot - shot + 1;
				}
				else {
					clip = shot;

					if ((tot - shot) > 9999)
						ammo = 9999;
					else
						ammo = tot - shot;
				}
				
				/*plugin::gamefont::Print(plugin::gamefont::ScreenSide::RightTop, gamefont::AlignLeft,
					Format("%d:%d", ammo, clip), SCREEN_RIGHT(86.0), SCREEN_TOP(86.0), 2, SCREEN_LEFT(0.5909090638f), SCREEN_TOP(1.136363626f), CRGBA(0, 255, 255, 255),
					1.0f, CRGBA(0, 0, 0, 255), false, 9999.0f, true, true);*/
					//ammo display new
				CFont::SetDropShadowPosition(1.0);
				CFont::SetDropColor(CRGBA(0, 0, 0, 255));
				CFont::SetBackgroundOff();
				CFont::SetCentreSize(SCREEN_LEFT(640.0f));
				CFont::SetFontStyle(2);
				CFont::SetColor(CRGBA(255, 255, 255, 255));
				CFont::SetScale(SCREEN_LEFT(0.4263f), SCREEN_TOP(0.82f));
				CFont::SetPropOn();
				CFont::SetRightJustifyOn();
				ScreenAddons::SetScreenMult(0.8, 0.8);
				if (patch::GetUInt(0x6FAD68, 1) != 1) { //disable on cutscenes
					if (int(weps) >= 2)
					{
						if (int(shot) <= 1 || WeaponType == WEAPONTYPE_ROCKETLAUNCHER || WeaponType == WEAPONTYPE_SNIPERRIFLE ||
							WeaponType == WEAPONTYPE_GRENADE || WeaponType == WEAPONTYPE_MOLOTOV)
						{
							if(patch::GetFloat(0x5FDB94, 1)==39.0f)	//money top
								CFont::PrintString(SCREEN_RIGHT(32.0), SCREEN_TOP(50.0), Format("%d", ammo).c_str());
							else
								CFont::PrintString(SCREEN_RIGHT(32.0), SCREEN_TOP(35.0), Format("%d", ammo).c_str());
						}
						else
						{	if(patch::GetFloat(0x5FDB94, 1) == 39.0f)
								CFont::PrintString(SCREEN_RIGHT(32.0), SCREEN_TOP(50.0), Format("%d %d", ammo, clip).c_str());
							else
								CFont::PrintString(SCREEN_RIGHT(32.0), SCREEN_TOP(35.0), Format("%d %d", ammo, clip).c_str());
						}
					}

					double q1, q2, q3, q4, q5, q6, q7, q8, mi, size1, size2, size3, size4, scr, sc2;
					double j1, j2, j3, j4, j5, j6, j7, j8;
					scr = sw / 2.0;
					sc2 = sh / 2.0;
					mi = ((int(weps) * 30 * 22) / 7.0) / 180.0;// +(45 * 22) / 7.0) / 180.0;
					size1 = sc2 / 1.5;
					size2 = scr;
					size3 = sc2 / 1.5;
					size4 = sc2;
					//for the slot indicator
					q1 = cos(mi)*size1 - sin(mi) * (size1)+size2;
					q3 = cos(mi)*size1 - sin(mi) * (-size1) + size2;
					q5 = cos(mi)*(-size1) - sin(mi) * size1 + size2;
					q7 = cos(mi)*(-size1) - sin(mi) * (-size1) + size2;
					q2 = sin(mi)*size3 + cos(mi)* (size3)+size4;
					q4 = sin(mi)*size3 + cos(mi)* (-size3) + size4;
					q6 = sin(mi)*(-size3) + cos(mi)* size3 + size4;
					q8 = sin(mi)*(-size3) + cos(mi)* (-size3) + size4;
					//for the rest
					mi = (90 * 22) / (180.0*7.0);
					j1 = cos(mi)*size1 - sin(mi) * (size1)+size2;
					j3 = cos(mi)*size1 - sin(mi) * (-size1) + size2;
					j5 = cos(mi)*(-size1) - sin(mi) * size1 + size2;
					j7 = cos(mi)*(-size1) - sin(mi) * (-size1) + size2;
					j2 = sin(mi)*size3 + cos(mi)* (size3)+size4;
					j4 = sin(mi)*size3 + cos(mi)* (-size3) + size4;
					j6 = sin(mi)*(-size3) + cos(mi)* size3 + size4;
					j8 = sin(mi)*(-size3) + cos(mi)* (-size3) + size4;
					//radio and weapon wheel
					bg.m_pTexture = RwTexDictionaryFindNamedTexture(ring, Format("bg").c_str());
					hl.m_pTexture = RwTexDictionaryFindNamedTexture(ring, Format("hl").c_str());
					if (rad >= 0 && rad <= 9)
					{
						radiot.m_pTexture = RwTexDictionaryFindNamedTexture(radio, Format("%d", rad).c_str());
					}
					else {
						radiot.m_pTexture = RwTexDictionaryFindNamedTexture(radio, Format("10").c_str());
					}


					w1 = pla ? pla->m_aWeapons[1].m_nType : '\0';
					w2 = pla ? pla->m_aWeapons[2].m_nType : '\0';
					w3 = pla ? pla->m_aWeapons[3].m_nType : '\0';
					w4 = pla ? pla->m_aWeapons[4].m_nType : '\0';
					w5 = pla ? pla->m_aWeapons[5].m_nType : '\0';
					w6 = pla ? pla->m_aWeapons[6].m_nType : '\0';
					w7 = pla ? pla->m_aWeapons[7].m_nType : '\0';
					w8 = pla ? pla->m_aWeapons[8].m_nType : '\0';
					w9 = pla ? pla->m_aWeapons[9].m_nType : '\0';
					w10 = pla ? pla->m_aWeapons[10].m_nType : '\0';
					w11 = pla ? pla->m_aWeapons[11].m_nType : '\0';
					w12 = pla ? pla->m_aWeapons[12].m_nType : '\0';
					
					if ((KeyPressed(VK_MBUTTON) || KeyPressed('1')) && !KeyPressed('2') && !KeyPressed(VK_RBUTTON))
					{
						CTimer::ms_fTimeScale = 0.5;
						bg.Draw(j1, j2, j3, j4, j5, j6, j7, j8, CRGBA(255, 255, 255, 255));
						hl.Draw(q1, q2, q3, q4, q5, q6, q7, q8, CRGBA(255, 255, 255, 192));
						CFont::SetCentreOn();
						CFont::SetFontStyle(2);
						CFont::SetScale(SCREEN_LEFT(0.3639f), SCREEN_TOP(0.7f));
						CFont::PrintString(SCREEN_MIDDLE_X(0.0), SCREEN_MIDDLE_Y(0.0), Format("%s", names[weps]).c_str());
						if (w1)
						{
							s1.m_pTexture = RwTexDictionaryFindNamedTexture(ring, Format("%u", w1).c_str());
							s1.Draw(j1, j2, j3, j4, j5, j6, j7, j8, CRGBA(255, 255, 255, 192));
						}
						if (w2)
						{
							s2.m_pTexture = RwTexDictionaryFindNamedTexture(ring, Format("%u", w2).c_str());
							s2.Draw(j1, j2, j3, j4, j5, j6, j7, j8, CRGBA(255, 255, 255, 192));
						}
						if (w3)
						{
							s3.m_pTexture = RwTexDictionaryFindNamedTexture(ring, Format("%u", w3).c_str());
							s3.Draw(j1, j2, j3, j4, j5, j6, j7, j8, CRGBA(255, 255, 255, 192));
						}
						if (w4)
						{
							s4.m_pTexture = RwTexDictionaryFindNamedTexture(ring, Format("%u", w4).c_str());
							s4.Draw(j1, j2, j3, j4, j5, j6, j7, j8, CRGBA(255, 255, 255, 192));
						}
						if (w5)
						{
							s5.m_pTexture = RwTexDictionaryFindNamedTexture(ring, Format("%u", w5).c_str());
							s5.Draw(j1, j2, j3, j4, j5, j6, j7, j8, CRGBA(255, 255, 255, 192));
						}
						if (w6)
						{
							s6.m_pTexture = RwTexDictionaryFindNamedTexture(ring, Format("%u", w6).c_str());
							s6.Draw(j1, j2, j3, j4, j5, j6, j7, j8, CRGBA(255, 255, 255, 192));
						}
						if (w7)
						{
							s7.m_pTexture = RwTexDictionaryFindNamedTexture(ring, Format("%u", w7).c_str());
							s7.Draw(j1, j2, j3, j4, j5, j6, j7, j8, CRGBA(255, 255, 255, 192));
						}
						if (w8)
						{
							s8.m_pTexture = RwTexDictionaryFindNamedTexture(ring, Format("%u", w8).c_str());
							s8.Draw(j1, j2, j3, j4, j5, j6, j7, j8, CRGBA(255, 255, 255, 192));
						}
						if (w9)
						{
							s9.m_pTexture = RwTexDictionaryFindNamedTexture(ring, Format("%u", w9).c_str());
							s9.Draw(j1, j2, j3, j4, j5, j6, j7, j8, CRGBA(255, 255, 255, 192));
						}
						if (w10)
						{
							s10.m_pTexture = RwTexDictionaryFindNamedTexture(ring, Format("%u", w10).c_str());
							s10.Draw(j1, j2, j3, j4, j5, j6, j7, j8, CRGBA(255, 255, 255, 192));
						}
						if (w11)
						{
							s11.m_pTexture = RwTexDictionaryFindNamedTexture(ring, Format("%u", w11).c_str());
							s11.Draw(j1, j2, j3, j4, j5, j6, j7, j8, CRGBA(255, 255, 255, 192));
						}
						if (w12)
						{
							s12.m_pTexture = RwTexDictionaryFindNamedTexture(ring, Format("%u", w12).c_str());
							s12.Draw(j1, j2, j3, j4, j5, j6, j7, j8, CRGBA(255, 255, 255, 192));
						}
						else
						{
							s12.m_pTexture = RwTexDictionaryFindNamedTexture(ring, Format("fist").c_str());
							s12.Draw(j1, j2, j3, j4, j5, j6, j7, j8, CRGBA(255, 255, 255, 192));
						}
					}
					else {
						CTimer::ms_fTimeScale = 1.0;
					}
					if (driveConf) {
						patch::Nop(0x57E954, 1);
						patch::Nop(0x57E93E, 1);
						
						if (vehId != 97 && vehId != 106 && vehId != 107 && vehId != 122 && vehId != 116 && vehId != 117) //disabling wheel on emergency vehicles
						{
							static int delay;
							if ((KeyPressed('2') || KeyPressed('R')) && (!KeyPressed(VK_MBUTTON) || !KeyPressed('1')))
							{
								delay = CTimer::m_snTimeInMilliseconds + 2000;
							}
							if (CTimer::m_snTimeInMilliseconds <= delay)
							{
								CFont::SetCentreOn();
								CFont::SetFontStyle(2);
								CFont::SetScale(SCREEN_LEFT(0.3639f), SCREEN_TOP(0.7f));
								CFont::PrintString(SCREEN_MIDDLE_X(0.0), SCREEN_MIDDLE_Y(0.0), Format("%s", radios[rad]).c_str());
								radiot.Draw(j1, j2, j3, j4, j5, j6, j7, j8, CRGBA(255, 255, 255, 192));
							}
						}
					}
				}
				/*	plugin::gamefont::Print(plugin::gamefont::ScreenSide::RightTop, gamefont::AlignLeft,
					Format("%u:%u",too,wo), SCREEN_COORD_RIGHT(300.0f), SCREEN_COORD_TOP(300.0f), FONT_DEFAULT, 2, 2, CRGBA(0, 255, 255, 255),
					1.0f, CRGBA(0, 0, 0, 255), false, 9999.0f, true, false);*/

			};
		};
		Events::shutdownRwEvent += [] {
			RwTexDictionaryDestroy(radio);
			RwTexDictionaryDestroy(ring);
			bg.m_pTexture = nullptr;
			hl.m_pTexture = nullptr;
			s1.m_pTexture = nullptr;
			s2.m_pTexture = nullptr;
			s3.m_pTexture = nullptr;
			s4.m_pTexture = nullptr;
			s5.m_pTexture = nullptr;
			s6.m_pTexture = nullptr;
			s7.m_pTexture = nullptr;
			s8.m_pTexture = nullptr;
			s9.m_pTexture = nullptr;
			s10.m_pTexture = nullptr;
			s11.m_pTexture = nullptr;
			s12.m_pTexture = nullptr;
			radiot.m_pTexture = nullptr;
		};
	}

}wRWheel;
/*weapon ids
slot 0
---
0=Unarmed
slot 1
---
1=Brass_Knuckles
2=ScrewDriver
3=GolfClub
4=NightStick
5=Knife
6=Baseball_Bat
7=Hammer
8=Meat_Cleaver
9=Machete
10=Katana
11=Chainsaw
slot 2
-----
12=Grenade
13=Remote_Detonation_Grenades
14=Tear_Gas
15=Molotov_Cocktails
16=Rocket
slot 3
-----
17=Colt45
18=Python
slot 4
-----
19=Shotgun
20=Spas12_Shotgun
21=Stubby_Shotgun
slot 5
--------
22=Tec9
23=Uzi
24=Silenced_Ingram
25=Mp5
slot 6
-------
26=m4
27=Ruger
slot 7
----

30=Rocket_Launcher
31=Flame_Thrower
32=M60
33=Minigun
slot 8
---------
28=Sniper_Rifle
29=Laser_Scope_Sniper_Rifle
*/
/*radio ids
0=wildstyle
1=flash fm
2=kchat
3=fever 103
4=vrock
5=vcpr
6=espantoso
7=emotion 98.3
8=wave 103
9=mp3 player
10=off
*/