#include "DEFMACRO"
#include "LiteAction.h"
//#include"./tool/list.h"
#include "math/measure.h"
#include "math/Matrix.h"
#include "math/Gather.h"
#include "space/SpaceD.h"
#include "tool/TMatrix.h"
#include "info/CMySQL.h"
#include "info/CSocket.h"
#include <iostream>
using namespace::std;
//#pragma warning(disable : 4996)


void showinfo(vector<map<string, string>> &data) {
	if (data.size() == 0)
		return;
	for (auto j : data[0])
		cout << j.first << "\t";
	cout << endl;
	for (int i = 0; i < data.size(); i++) {
		for (auto j : data[i])
			cout << j.second << "\t";
		cout << endl;
	}
}






void fun(char* mes, int ret) {
	mes[ret] = '\0';
	printf("%s", mes);
}


int main() {
	//cout << LiteAction::GetFileTime("d:/123.txt");
	//int n = 0;
	//string str;
	//Sock_DealFun Fun = fun;
	//CSocket_Server server(8787);
	//while (1) {
	//	if (server.GetClientIPlist().size() != 0) {
	//		cout << "find ip" << n++ << "=" << server.GetClientIPlist()[0] << endl;
	//		server.Ssend(to_string(n).c_str(), server.GetClientIPlist()[0]);
	//	}
	//}
	//std::cin >> str;


	Mysql_info mysqlinfo;
	mysqlinfo.ip = "192.168.1.8";
	mysqlinfo.username = "xhqm";
	mysqlinfo.password = "xhqm";

	CMySQL mysql;
	mysql.UpMySQLInfo(mysqlinfo);
	cout << mysql.MySQLCommandError();
	mysql.SelectDataBase("money");
	cout << mysql.MySQLCommandError();
	mysql.ShowDataBase("money");
	cout << mysql.MySQLCommandError();




	//vector<map<string, string>> data;
	//mysql.Select("test", "time,id,time", &data);
	//showinfo(data);



	return 0;
}






//GatherS signs;
//signs + 'a';
//signs + 'B';
//signs + '0';
//string str = string(&signs[1]) + string(&signs[1]) + string(&signs[1]);

//sure a = 0.99999999999999999;
//cout << a<< (int)a << endl;
//cout << str << endl;

////cout<< ;// <<  << signs[3] << endl;

////cout << "////" << oned2<dou>.size();


////SpaceD A(THRD);
//
//TMatrix<int> A(3,3);

//std::cout << "\n";
//std::cout << "\n";


//TMatrix<double> P(3, 3);
//P[0][0] = 1, P[0][1] = 2, P[0][2] = 3;
//P[1][0] = 2, P[1][1] = 3, P[1][2] = 1;
//P[2][0] = 3, P[2][1] = 1, P[2][2] = 2;

//TMatrix<double> P1(3, 3);
//P1[0][0] = 3, P1[0][1] = 2, P1[0][2] = -1;
//P1[1][0] = 1, P1[1][1] = 3, P1[1][2] = -2;
//P1[2][0] = 2, P1[2][1] = 1, P1[2][2] = -3;

//TMatrix<double> X(3, 3);
////X = A.GetRotateY(Pi/2);
//X = P * P1;


////if (X == P1)
//	for (int i = 0; i < X.GetDn(); i++) {
//		for (int j = 0; j < X.GetDm(); j++)
//			std::cout << X[i][j] << "\t";
//		std::cout << "\n";
//	}

/**/

/*
	for (nume i = 0; i < Z.GetPotential(); i++, Z++)
		std::cout << Z.GetElement()->Getdata() << "\n";
	*/


/*
Matrix matrix(3, 3);
Line l1, l2, l3;

l1.push_back(1);
l1.push_back(2);
l1.push_back(3);

l2.push_back(2);
l2.push_back(3);
l2.push_back(1);

l3.push_back(3);
l3.push_back(1);
l3.push_back(2);

matrix.SetMatrixLine(l1, 0);
matrix.SetMatrixLine(l2, 1);
matrix.SetMatrixLine(l3, 2);



Matrix matrix2 = matrix ^ -1;
Matrix matrix3 = matrix2 + matrix + matrix;
std::cout << matrix.GetDete() << "\n";
for (nume i = 0; i < matrix.GetDn(); i++) {
	for (nume j = 0; j < matrix.GetDm(); j++)
		std::cout << matrix3[i][j] << "\t";
	std::cout << "\n";
}*/

/*
GatherZ Z;
GatherZ Z1;
GatherZ Z2;

for (nume i = 2; i < 5; i++)
	Z1.AddOneElement(i);
for (nume i = 3; i < 9; i++)
	Z2.AddOneElement(i);

Z += Z2;

for (nume i = 0; i < Z.GetPotential(); i++, Z++)
	std::cout << Z.GetElement()->Getdata() << "\n";
*/
