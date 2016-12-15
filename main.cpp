#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "micro.h"
using namespace std;


//4 reg
//8 pin rx tx
//64b ram
//compare flag

int main()
{
	cout << "Microcontroller simulation:" << endl;
	micro pic;
	bool ex = 1;
	while (ex)
	{
		cout << ">";
		ex = pic.getcommands();
	}
	cout << "Quitting..." << endl;
	system("pause");
	return 0;
}
