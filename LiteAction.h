#pragma once
#include "DEFMACRO"
#pragma warning(disable : 4996)
#include <string>
#include <vector>

#ifdef WIN
#include <windows.h>
#include <corecrt_io.h>
#endif // WIN


class LiteAction
{
public:
	static void tosl(char num, char* txtdata);
	static void tonu(char* txtdata, char&num);
	static std::string StringTo_ASICLL16(const std::string str);
	static std::string ASICLL16To_String(const std::string asi);
	static bool FILE_BINtoBXT(const std::string BINpath, const std::string BXTpath);
	static bool FILE_BXTtoBIN(const std::string BXTpath, const std::string BINpath);


#ifdef MACX64
#endif
#ifdef MACX86
#endif
#ifdef WIN
	static std::string WinNowTime();
	static std::string GetFileInfo(const std::string path);
	static std::vector<std::string> FindFileList(std::string path,int ford = _A_NORMAL| _A_RDONLY| _A_HIDDEN| _A_SYSTEM| _A_SUBDIR| _A_ARCH, std::string type = "");
	static std::string UTF8_To_string(const std::string& str);
	static std::string string_To_UTF8(const std::string& str);
#endif
#ifdef WINX64
#endif
#ifdef WINX86
#endif
	
};

