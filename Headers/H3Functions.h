//////////////////////////////////////////////////////////////////////
//                                                                  //
//                  Created by RoseKavalier:                        //
//                  rosekavalierhc@gmail.com                        //
//                                                                  //
//          ***You may use or distribute these files freely         //
//             so long as this notice remains present.***           //
//                                                                  //
//          In preparing these files, several sources were          //
//            consulted, they are listed in no particular           //
//                          order below.                            //
//                                                                  //
//  Source: https://github.com/potmdehex/homm3tools                 //
//  Author: potmdehex and contributors                              //
//                                                                  //
//  Source: https://github.com/redxu/HoMM3_FA                       //
//  Author: redxu                                                   //
//                                                                  //
//  Source: https://github.com/openhomm/openhomm                    //
//  Author: Ershov Stanislav, Fomin Roman, Akulich Alexander        //
//                                                                  //
//  Source: https://github.com/GrayFace/wog                         //
//  Author: GrayFace and WoG team                                   //
//                                                                  //
//  Source: https://github.com/ethernidee/era                       //
//  Author: Berserker                                               //
//                                                                  //
//  Source: https://github.com/ethernidee/era-editor                //
//  Author: Grayface and Berserker                                  //
//                                                                  //
//  Source: http://wforum.heroes35.net/showthread.php?tid=3900      //
//  Author: Slava and GrayFace                                      //
//                                                                  //
//  Source: http://wforum.heroes35.net/showthread.php?tid=4583      //
//  Author: gamecreator                                             //
//                                                                  //
//  Thanks: patcher_x86 by baratorch and code therein               //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3FUNCTIONS_H_
#define _H3FUNCTIONS_H_

#pragma once

#include "H3Base.h"
#include "H3Structures.h"
#include "H3Defines.h"

// * inserts a breakpoint for quick stop using debugger
inline VOID F_Breakpoint()
{
	if (IsDebuggerPresent())
		__asm int 3;
}

// * Gets cursor coordinates within game window
inline VOID F_GetCursorPosition(INT &x, INT &y)
{
	STDCALL_2(VOID, 0x50D700, &x, &y);
}

// * Gets cursor coordinates within game window
inline VOID F_GetCursorPosition(POINT & p)
{
	STDCALL_2(VOID, 0x50D700, &p.x, &p.y);
}

// * given power ratio k, returns the diplomacy power factor
inline INT32 F_GetDiplomacyPowerFactor(float k)
{
	return STDCALL_1(INT32, 0x4A7330, k);
}

// * returns a creature's upgraded version id
inline INT32 F_GetCreatureUpgrade(INT id)
{
	return THISCALL_1(INT32, 0x47AAD0, id);
}

// * checks whether the given creature has an upgraded version
inline BOOL8 F_CreatureHasUpgrade(INT id)
{
	return THISCALL_1(BOOL8, 0x47AA50, id);
}

// * GetCurrentDirectoryA using h3 assets
inline INT F_GetCurrentDirectory(PCHAR buf, INT bufLen = MAX_PATH)
{
	return STDCALL_2(INT, IntAt(0x63A1A4), bufLen, buf);
}

// * message box with text shown (default h3_TextBuffer) on right mouse button click
inline VOID F_MessageBoxRMB(LPCSTR text = h3_TextBuffer)
{
	FASTCALL_12(VOID, 0x4F6C00, text, 4, -1, -1, -1, 0, -1, 0, -1, 0, -1, 0);
}

// * message box with text shown (default h3_TextBuffer) with an 'OK' button
inline VOID F_MessageBox(LPCSTR text = h3_TextBuffer)
{
	FASTCALL_12(VOID, 0x4F6C00, text, 1, -1, -1, -1, 0, -1, 0, -1, 0, -1, 0);
}

// * message box with 'OK' and 'Cancel' buttons
// * returns true if clicked 'OK'
inline BOOL F_MessageBoxChoice(LPCSTR text = h3_TextBuffer)
{
	FASTCALL_12(VOID, 0x4F6C00, text, 2, -1, -1, -1, 0, -1, 0, -1, 0, -1, 0);
	return H3Pointers::WindowManager()->ClickedOK();
}

// * prints text to the log screen (default h3_TextBuffer)
inline VOID F_PrintScreenText(LPCSTR text = h3_TextBuffer)
{
	CDECL_3(VOID, 0x553C40, 0x69D800, "%s", text);
}

// * checks whether the active player can view given coordinates
inline BOOL F_CanViewTile(INT x, INT y, INT z)
{
	return (FASTCALL_3(UINT8, 0x4F8040, x, y, z) & h3_ActivePlayerBitset);
}

// * Pointer to vision information of coordinates
inline H3TileVision* F_GetTileVision(INT x, INT y, INT z)
{
	return FASTCALL_3(H3TileVision*, 0x4F8070, x, y, z);
}

// * reveals tile for current player at coordinates
inline VOID F_ReveaTile(INT x, INT y, INT z)
{
	F_GetTileVision(x, y, z)->vision |= h3_ActivePlayerBitset;
}

// * timeGetTime using H3 assets
inline DWORD F_GetTime()
{
	return STDCALL_0(DWORD, PtrAt(0x63A354));
}

// * reverses string in buffer, returned to buffer
inline PCHAR F_strRev(PCHAR buffer)
{
	return CDECL_1(PCHAR, 0x627690, buffer);
}

// * FindFirstFileA using H3 assets
inline HANDLE F_FindFirstFileA(LPCSTR path, WIN32_FIND_DATAA & data)
{
	return STDCALL_2(HANDLE, PtrAt(0x63A11C), path, &data);
}

// * FindFirstFileA using H3 assets
inline HANDLE F_FindFirstFileA(H3String & path, WIN32_FIND_DATAA & data)
{
	return STDCALL_2(HANDLE, PtrAt(0x63A11C), path.String(), &data);
}

// * FindNextFileA using H3 assets
inline HANDLE F_FindNextFileA(HANDLE handle, WIN32_FIND_DATAA & data)
{
	return STDCALL_2(HANDLE, PtrAt(0x63A120), handle, &data);
}

// * converts text to integer using H3 assets
inline INT32 F_atoi(LPCSTR text)
{
	return CDECL_1(INT32, 0x6184D9, text);
}

// * compares two strings up to len characters
inline INT F_strnicmp(LPCSTR string1, LPCSTR string2, INT len)
{
	return CDECL_3(INT, 0x626680, string1, string2, len);
}

// * copies len characters from source to dest
inline PCHAR F_strncpy(LPCSTR dest, LPCSTR src, INT len)
{
	return CDECL_3(PCHAR, 0x618FE0, dest, src, len);
}

// * Checks if the current game features more than 1 human
inline BOOL8 F_Multiplayer()
{
	return STDCALL_0(BOOL8, 0x4CE950);
}

// * converts text to wide char, destination is buffer that needs to be pre-allocated
inline LPCWSTR F_MultiByteToWideChar(LPCSTR text, int textLength, WCHAR *buffer)
{
	return STDCALL_6(LPCWSTR, PtrAt(0x63A1CC), CP_ACP, 0, text, textLength, buffer, textLength);
}

inline INT F_MultiplayerRNG(INT min_value, INT max_value)
{
	return FASTCALL_2(INT, 0x50B3C0, min_value, max_value);
}

inline INT F_GetLocalTime()
{
	SYSTEMTIME time;
	STDCALL_1(VOID, PtrAt(0x63A248), &time);
	return F_sprintf("%04d.%02d.%02d - %02dh%02dm%02ds", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
}

inline FILE* F_fopen(LPCSTR filename, LPCSTR mode)
{
	return CDECL_2(FILE*, 0x619691, filename, mode);
}

inline int F_fclose(FILE *f)
{
	return CDECL_1(int, 0x618F5E, f);
}

inline DWORD F_ftell(FILE *f)
{
	return CDECL_1(DWORD, 0x6194DD, f);
}

inline INT F_fseek(FILE *f, INT offset, INT origin)
{
	return CDECL_3(INT, 0x618C78, f, offset, origin);
}

inline DWORD F_GetFileSize(FILE *f)
{
	F_fseek(f, 0, SEEK_END);
	DWORD size = F_ftell(f);
	F_fseek(f, 0, SEEK_SET);
	return size;
}

inline size_t F_fread(PVOID buffer, size_t size, size_t count, FILE *f)
{
	return CDECL_4(size_t, 0x6196A4, buffer, size, count, f);
}

inline size_t F_fwrite(const VOID* buffer, size_t size, size_t count, FILE *f)
{
	return CDECL_4(size_t, 0x618A1A, buffer, size, count, f);
}

inline int F_fsetpos(FILE *f, const fpos_t & pos)
{
	return CDECL_2(int, 0x618D31, f, &pos);
}

inline int F_fgetpos(FILE *f, fpos_t & pos)
{
	return CDECL_2(int, 0x618C56, f, &pos);
}

inline int F_fputc(const CHAR c, FILE *f)
{
	return CDECL_2(int, 0x618B53, c, f);
}

inline INT F_strtol(LPCSTR str, INT base, PCHAR* end = nullptr)
{
	return CDECL_3(INT, 0x619BF8, str, &end, nullptr);
}

inline UINT F_strtoul(LPCSTR str, INT base, PCHAR* end = nullptr)
{
	return CDECL_3(INT, 0x619E14, str, end, base);
}

inline PCHAR F_strtok(LPCSTR str, LPCSTR delimiters)
{
	return CDECL_2(PCHAR, 0x617FBB, str, delimiters);
}

inline VOID H3SoundManager::ClickSound()
{
	H3WavFile *buttonWav = C_ButtonWav;
	INT32 backup = clickSoundVar;
	buttonWav->spinCount = 64;
	buttonWav->debugInfo = (PRTL_CRITICAL_SECTION_DEBUG)1;
	buttonWav->lockSemaphore = (HANDLE)(HANDLE_FLAG_PROTECT_FROM_CLOSE | HANDLE_FLAG_INHERIT);
	THISCALL_2(VOID, 0x59A510, this, buttonWav);
	clickSoundVar = backup;
}

#endif /* #define _H3FUNCTIONS_H_ */