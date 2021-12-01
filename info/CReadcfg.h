#pragma once
#include <vector>
#include <fstream>
#include <sys/stat.h>

typedef std::vector<std::string> Lcfgs;
typedef std::vector<std::vector<std::string>> Ecfgs;
typedef std::vector<std::vector<std::vector<std::string>>> Acfgs;
class CReadcfg
{
public:
	CReadcfg(std::string path);
	~CReadcfg();

	Ecfgs Read(std::string ele);
	Acfgs Read(Lcfgs element);
	void Write(std::string ele, Lcfgs &lcfg);
	void Write(std::string ele, Ecfgs &ecfg);

private:
	std::fstream cfg;
};

