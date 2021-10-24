#include "LiteAction.h"

void LiteAction::tosl(char num, char* txtdata) {
	int _num = num - 0xffffff00;
	int num_0 = _num / 16;
	int num_1 = _num % 16;
	num_0 %= 16;
	if (num_0 < 10)
		txtdata[0] = '0' + num_0;
	else
		txtdata[0] = 'A' + (num_0 - 10);
	if (num_1 < 10)
		txtdata[1] = '0' + num_1;
	else
		txtdata[1] = 'A' + (num_1 - 10);
	txtdata[2] = '\0';
}

void LiteAction::tonu(char* txtdata, char&num){
	num = 0;
	if (txtdata[1] < 'A')
		num |= txtdata[1] - '0';
	else
		num |= txtdata[1] - 'A' + 10;
	if (txtdata[0] < 'A')
		num |= ((txtdata[0] - '0') << 4);
	else
		num |= ((txtdata[0] - 'A' + 10) << 4);
}

std::string LiteAction::StringTo_ASICLL16(const std::string str){
	std::string asistr = "";
	char asi[3] = { '0','0','\0' };
	long long len = str.length();
	for (long long j = 0; j < len; j++) {
		tosl(str.c_str()[j], asi);
		asistr = asistr + std::string(asi);
	}return asistr;
}

std::string LiteAction::ASICLL16To_String(const std::string asistr){
	std::string str = "";
	char txtdata[4] = { '0','0','\0','\0' };
	long long len = asistr.length();
	for (long long j = 0; j < len; j++) {
		txtdata[0] = asistr[j++], txtdata[1] = asistr[j], txtdata[2] = '\0';
		tonu(txtdata, txtdata[2]);
		str = str + txtdata[2];
	}return str;
}

bool LiteAction::FILE_BINtoBXT(const std::string BINpath, const std::string BXTpath){
	FILE* fil;
	FILE* bxt;
	char txtdata[3] = { '0','0',' ' };
	if ((fil = fopen(BINpath.c_str(), "rb")) != NULL) {
		bxt = fopen(BXTpath.c_str(), "w");
		do {
			tosl(fgetc(fil), txtdata);
			txtdata[2] = ' ';
			fwrite(txtdata, 3, 1, bxt);
			fgetc(fil);
			if (feof(fil) != 0)
				break;
			fseek(fil, -1, SEEK_CUR);
		} while (!feof(fil));//(true);//
		fclose(fil);
		fclose(bxt);
		return true;
	}return false;
}

bool LiteAction::FILE_BXTtoBIN(const std::string BXTpath, const std::string BINpath){
	FILE* bxt;
	FILE* fil;
	char txtdata[4] = { ' ',' ','0' };
	if ((bxt = fopen(BXTpath.c_str(), "rb")) != NULL) {
		fil = fopen(BINpath.c_str(), "w");
		do {
			txtdata[0] = fgetc(bxt);
			txtdata[1] = fgetc(bxt);
			txtdata[2] = fgetc(bxt);
			if (txtdata[0] == -1)
				break;
			tonu(txtdata, txtdata[2]);
			fputc(txtdata[2], fil);
		} while (!feof(bxt));
		fclose(fil);
		fclose(bxt);
		return true;
	}return false;
}




#ifdef WIN
std::string LiteAction::WinNowTime(){
	SYSTEMTIME st;
	GetLocalTime(&st);
	return std::to_string(st.wHour) + ":" + std::to_string(st.wMinute) + ":" + std::to_string(st.wSecond) + "." + std::to_string(st.wMilliseconds);
}
std::string LiteAction::GetFileInfo(const std::string path){
	struct _stat tmpInfo;
	if (_stat(path.c_str(), &tmpInfo) != 0)
		return "null";
	int iCreateTime = static_cast<int>(tmpInfo.st_ctime);
	int iModifyTime = static_cast<int>(tmpInfo.st_mtime);
	int iAccessTime = static_cast<int>(tmpInfo.st_atime);
	int iFileLen = static_cast<int>(tmpInfo.st_size);
	return "创建时间" + std::to_string(iCreateTime) + "\n修改时间" + std::to_string(iModifyTime) + "\n访问时间" + std::to_string(iAccessTime) + "\n文件长度" + std::to_string(iFileLen) + "byte\n";
}
std::vector<std::string> LiteAction::FindFileList(std::string path, int ford, std::string type){
	std::vector<std::string> FileList;
	_finddata_t file;
	long long HANDLE = {};
	int k = 0;
	if (path[path.size() - 1] != '/' && path[path.size() - 1] != '\\')
		path += "/";
	if (type == "")
		HANDLE = _findfirst((path + "*").c_str(), &file);
	else if(type[0] == '.')
		HANDLE = _findfirst((path + "*" + type).c_str(), &file);
	else if (type[0] != '.')
		HANDLE = _findfirst((path + "*." + type).c_str(), &file);
	for (k = HANDLE; k != -1; k = _findnext(HANDLE, &file))
		if((file.attrib & ford) || ford == 0)
			FileList.push_back(file.name);
	_findclose(HANDLE);
	return FileList;
}
std::string LiteAction::UTF8_To_string(const std::string& str) {
	int nwLen = ::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	memset(pwBuf, 0, nwLen * 2 + 2);
	::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);
	int nLen = ::WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char* pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);
	::WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
	std::string retStr = pBuf;
	delete[]pBuf;
	delete[]pwBuf;
	pBuf = NULL;
	pwBuf = NULL;
	return retStr;
}
std::string LiteAction::string_To_UTF8(const std::string& str) {
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	ZeroMemory(pwBuf, nwLen * 2 + 2);
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);
	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
	std::string retStr(pBuf);
	delete[]pwBuf;
	delete[]pBuf;
	pwBuf = NULL;
	pBuf = NULL;
	return retStr;
}
#endif

