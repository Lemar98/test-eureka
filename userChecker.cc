#include <windows.h>
#include <lm.h>
#include <iostream>
#pragma comment(lib, "netapi32.lib")
#include "./node_modules/node-addon-api/napi.h"

BOOL IsValidUser(LPCWSTR username)
{
    LPUSER_INFO_0 info = NULL;
    DWORD bufSize = 0;
    NET_API_STATUS result = NetUserGetInfo(NULL, username, 0, (LPBYTE*)&info);

    if (result == ERROR_MORE_DATA || result == NERR_BufTooSmall)
    {
        info = (LPUSER_INFO_0)LocalAlloc(LPTR, bufSize);
        if (info != NULL)
        {
            result = NetUserGetInfo(NULL, username, 0, (LPBYTE*)&info);
        }
    }

    if (info != NULL)
    {
        LocalFree(info);
    }

    return result == NERR_Success;
}

Napi::Value IsValidUserWrapper(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    std::string name = (std::string)info[0].ToString();

    int size = MultiByteToWideChar(CP_UTF8, 0, name.c_str(), -1, NULL, 0);
    wchar_t* wideString = new wchar_t[size];
    MultiByteToWideChar(CP_UTF8, 0, name.c_str(), -1, wideString, size);
    LPCWSTR resultStr = wideString;

    BOOL result = IsValidUser(resultStr);
    return Napi::Boolean::New(env, result);

    delete[] wideString;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    Napi::String str = Napi::String::New(env, "isValidUser");
    exports.Set(str, Napi::Function::New(env, IsValidUserWrapper));
    return exports;
}

NODE_API_MODULE(IsValidUser, Init)