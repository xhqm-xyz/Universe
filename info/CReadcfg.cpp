#include "CReadcfg.h"

CReadcfg::CReadcfg(std::string path)
{
	cfg.open(path,std::ios::in| std::ios::out);
}

CReadcfg::~CReadcfg()
{
	cfg.close();
}

Ecfgs CReadcfg::Read(std::string ele)
{	
	Ecfgs ecfg;
	std::string info;
	std::string star = "@" + ele + "@";
	std::string end = "@end" + ele + "@";
	cfg.seekg(0);
	for (;;) {
		cfg >> info;
		if (info == star)
			for (int i = 0;; i++) {
				cfg >> info;
				if (info == end)
					break;
				Lcfgs lcfg;
				if (info != "") {
					for (int i = 0;; i++) {
						std::string data = "";
						const char* str = strchr(info.c_str(), ',');
						if (str != NULL) {
							int num = std::string(str).length();
							data = info.substr(0, info.length() - num);
							lcfg.push_back(data.substr(1, data.length() - 2));
							info.erase(0, info.length() - num + 1);
						}
						else {
							data = info;
							lcfg.push_back(data.substr(1, data.length() - 2));
							break;
						}
					}ecfg.push_back(lcfg);
				}
			}
		if (info == "@end@")
			break;
	}return ecfg;
}

Acfgs CReadcfg::Read(Lcfgs element)
{
	Acfgs acfg;
	for (auto& ele : element)
		acfg.push_back(Read(ele));
	return acfg;
}

void CReadcfg::Write(std::string ele, Lcfgs &lcfg)
{
	std::string info;
	std::string star = "@" + ele + "@";
	std::string end = "@end" + ele + "@";
	cfg.seekg(0);
	for (;;) {
		cfg >> info;
		if (info == star) {
			for (auto data = lcfg.begin(); data != lcfg.end(); data++)
				cfg << "\"" + *data + "\"" << (data == lcfg.end() - 1 ? "," : "\n");
			return;
		}
		if (info == "@end@")
			break;
	}cfg.seekg(0);
	for (;;) {
		cfg >> info;
		if (info == "@@") {
			cfg << star << std::endl;
			for (auto data = lcfg.begin(); data != lcfg.end(); data++)
				cfg << "\"" + *data + "\"" << (data == lcfg.end() - 1 ? "," : "\n");
			cfg << end << std::endl;
			cfg.close();
			return;
		}
	}
}

void CReadcfg::Write(std::string ele, Ecfgs &ecfg)
{
	for (auto& lcfg : ecfg)
		Write(ele, lcfg);
}
