#include "micro.h"

int micro::getPin(size_t i)
{
	if (pins[i].wr != 0)
		throw exception("trying to read not input pin!");
	cout << "getted" << endl;
	return pins[i].leg;
}

void micro::setPin(size_t i, bool s)
{
	if (pins[i].wr != 1)
		throw exception("trying to write not output pin!");
	pins[i].leg = s;
	cout << "setted" << endl;
}

void micro::setRom(string f)
{
	fstream file(f);
	//string s;
	if (!file.is_open() || file.eof())
		throw exception("bad rom file!");
	while (!file.eof())
	{
		string s;
		getline(file, s);
		rom.push_back(s);
	}
	file.close();
	if (rom.size() > 255)
	{
		cout << "abort instalation, rom too big!!!";
		rom.clear();
		return;
	}
	cout << "rom installed!" << endl;
}

void micro::setDefPin()
{
	for (int i = 0;i < 6;i++)
		if (pins[i].wr == 0)
		{
			if (pins[i].file.eof())
				throw exception("End of file!");
			pins[i].file >> pins[i].leg;
			cout << "pinne " << i << " inputted!" << endl;
		}
}

void micro::getDefPin()
{
	for (int i = 0;i < 6;i++)
		if (pins[i].wr == 1)
		{
			pins[i].file << '!' << pins[i].leg << endl;
			cout << "pinne " << i << " outputted!" << endl;
		}
}

void micro::help()
{
	cout << "--- tx [pin] - read from pin" << endl;
	cout << "--- rx [pin] - write to pin" << endl;
	cout << "--- rom [file] - get rom" << endl;
	cout << "--- run - \\ " << endl;
	cout << "--- adv - \\debug " << endl;
}

void micro::advhelp()
{
	cout << "--- next - next command" << endl;
	cout << "--- show_rom - \\" << endl;
	cout << "--- next_rom - show next command" << endl;
	cout << "--- reg - show registers " << endl;
	cout << "--- pin - show pins " << endl;
	cout << "--- ram - show ram" << endl;
	cout << "--- fin - do all commands to finish" << endl;
	cout << "--- exuc - exit debug" << endl;
}

micro::micro() : pc(0)
{
	for (int i = 0;i < 6;i++)
	{
		pins[i].wr = -1;
		pins[i].leg = 0;
	}
}

micro::~micro()
{
	for (int i = 0;i < 6;i++)
		pins[i].file.close();
	rom.clear();
}

void micro::next() try
{
	string com;
	stringstream ss(rom[pc]);
	ss >> com;
	if (com == "mov")
	{
		string fo, so;
		ss >> fo >> so;
		if (fo[0] == '$')
		{
			if (so[0] == '$')
				mov(reg + (fo[1] - '0'), reg + (so[1] - '0'));
			else
				mov(reg + (fo[1] - '0'), ram + stoi(so));
		}
		else
		{
			if (so[0] == '$')
				mov(ram + stoi(fo), reg + (so[1] - '0'));
			else
				mov(ram + stoi(fo), ram + stoi(so));
		}
	}
	else if (com == "new")
	{
		string fo, so;
		ss >> fo >> so;
		uint8_t a = stoi(so);
		mov(reg + (fo[1] - '0'), &a);
	}
	else if (com == "add")
	{
		string fo, so;
		ss >> fo >> so;
		if (so[0] == '$')
			add(reg + (fo[1] - '0'), reg + (so[1] - '0'));
		else
			add(reg + (fo[1] - '0'), ram + stoi(so));
	}
	else if (com == "sub")
	{
		string fo, so;
		ss >> fo >> so;
		if (so[0] == '$')
			sub(reg + (fo[1] - '0'), reg + (so[1] - '0'));
		else
			sub(reg + (fo[1] - '0'), ram + stoi(so));
	}
	else if (com == "mul")
	{
		string fo, so;
		ss >> fo >> so;
		if (so[0] == '$')
			mul(reg + (fo[1] - '0'), reg + (so[1] - '0'));
		else
			mul(reg + (fo[1] - '0'), ram + stoi(so));
	}
	else if (com == "div")
	{
		string fo, so;
		ss >> fo >> so;
		if (so[0] == '$')
			div(reg + (fo[1] - '0'), reg + (so[1] - '0'));
		else
			div(reg + (fo[1] - '0'), ram + stoi(so));
	}
	else if (com == "mod")
	{
		string fo, so;
		ss >> fo >> so;
		if (so[0] == '$')
			mod(reg + (fo[1] - '0'), reg + (so[1] - '0'));
		else
			mod(reg + (fo[1] - '0'), ram + stoi(so));
	}
	else if (com == "and")
	{
		string fo, so;
		ss >> fo >> so;
		if (so[0] == '$')
			and (reg + (fo[1] - '0'), reg + (so[1] - '0'));
		else
			and (reg + (fo[1] - '0'), ram + stoi(so));
	}
	else if (com == "or")
	{
		string fo, so;
		ss >> fo >> so;
		if (so[0] == '$')
			or (reg + (fo[1] - '0'), reg + (so[1] - '0'));
		else
			or (reg + (fo[1] - '0'), ram + stoi(so));
	}
	else if (com == "xor")
	{
		string fo, so;
		ss >> fo >> so;
		if (so[0] == '$')
			xor (reg + (fo[1] - '0'), reg + (so[1] - '0'));
		else
			xor (reg + (fo[1] - '0'), ram + stoi(so));
	}
	else if (com == "shl")
	{
		string fo, so;
		ss >> fo >> so;
		if (so[0] == '$')
			shl(reg + (fo[1] - '0'), reg + (so[1] - '0'));
		else
			shl(reg + (fo[1] - '0'), ram + stoi(so));
	}
	else if (com == "shr")
	{
		string fo, so;
		ss >> fo >> so;
		if (so[0] == '$')
			shr(reg + (fo[1] - '0'), reg + (so[1] - '0'));
		else
			shr(reg + (fo[1] - '0'), ram + stoi(so));
	}
	else if (com == "cmp")
	{
		string fo, so;
		ss >> fo >> so;
		if (so[0] == '$')
			cmp(reg + (fo[1] - '0'), reg + (so[1] - '0'));
		else
			cmp(reg + (fo[1] - '0'), ram + stoi(so));
	}
	else if (com == "jg")
	{
		string fo;
		ss >> fo;
		if (fo[0] == '$')
			jg(reg + (fo[1] - '0'));
		else
			jg(ram + stoi(fo));
	}
	else if (com == "jge")
	{
		string fo;
		ss >> fo;
		if (fo[0] == '$')
			jge(reg + (fo[1] - '0'));
		else
			jge(ram + stoi(fo));
	}
	else if (com == "jl")
	{
		string fo;
		ss >> fo;
		if (fo[0] == '$')
			jl(reg + (fo[1] - '0'));
		else
			jl(ram + stoi(fo));
	}
	else if (com == "jle")
	{
		string fo;
		ss >> fo;
		if (fo[0] == '$')
			jle(reg + (fo[1] - '0'));
		else
			jle(ram + stoi(fo));
	}
	else if (com == "jmp")
	{
		string fo;
		ss >> fo;
		if (fo[0] == '$')
			jmp(reg + (fo[1] - '0'));
		else
			jmp(ram + stoi(fo));
	}
	else if (com == "get")
	{
		string fo, so;
		ss >> fo >> so;
		*(reg + (fo[1] - '0')) = (getPin(stoi(so)) | (*(reg + (fo[1] - '0')) & 254));
	}
	else if (com == "set")
	{
		string fo, so;
		ss >> fo >> so;
		setPin(stoi(so), *(reg + (fo[1] - '0')) & 1);
		//*(reg + (fo[1] - '0')) = getPin(stoi(so));
	}
	else cout << "wrong rom command!" << endl;
}
catch (exception ex) { cout << ex.what() << endl; }

bool micro::getcommands() try
{
	string line;
	getline(cin, line);
	stringstream ss(line);
	ss >> line;

	if (line == "rx")//vuvod
	{
		string fo;
		ss >> fo;
		string a;
		a = "pins/" + fo + ".txt";
		pins[stoi(fo)].file.open(a);
		//pins[stoi(fo)].file.clear();
		pins[stoi(fo)].wr = 1;
	}
	else if (line == "tx")//vvod
	{
		string fo;
		ss >> fo;
		string a;
		a = "pins/" + fo + ".txt";
		pins[stoi(fo)].file.open(a);
		pins[stoi(fo)].wr = 0;
	}
	else if (line == "adv")//
	{
		pc = 0;
		setDefPin();
		while (pc < rom.size())
		{
			advanced();
			//pc++;
		}
		getDefPin();
	}
	else if (line == "rom")//prosh
	{
		string fo;
		ss >> fo;
		setRom(fo);
	}
	else if (line == "run")
	{
		pc = 0;
		setDefPin();
		while (pc < rom.size())
		{
			next();
			pc++;
		}
		getDefPin();
	}
	else if (line == "help")
	{
		help();
	}
	else if (line == "exit")
		return false;

	else cout << "wrong command!" << endl;
	return true;
}
catch (exception ex) 
{ 
	cout << ex.what() << endl; 
	return true; 
}

void micro::advanced() try
{
	cout << ">>";
	string line;
	getline(cin, line);
	stringstream ss(line);
	ss >> line;
	if (line == "next")
	{
		next();
		pc++;
	}
	else if (line == "show_rom")
	{
		for (auto i : rom)
		{
			cout << i << endl;
		}
	}
	else if (line == "next_rom")
	{
		cout << rom[pc] << endl;
	}
	else if (line == "reg")
	{
		for (int i = 0;i < 4;i++)
		{
			printf("%d %d \n", i, reg[i]);
		}
	}
	else if (line == "pin")
	{
		for (int i = 0;i < 6;i++)
		{
			printf("%d %d \n", i, pins[i].leg);
		}
	}
	else if (line == "exuc")
	{
		pc = rom.size();
		return;
	}
	else if (line == "ram")
	{
		for (int i = 0;i < 16;i++)
		{
			printf("%d %d \n", i, ram[i]);
		}
	}
	else if (line == "fin")
	{
		while (pc < rom.size())
		{
			next();
			pc++;
		}
	}
	else if (line == "help")
	{
		advhelp();
	}
	else cout << "wrong command!" << endl;

}
catch (exception ex) { cout << ex.what() << endl; }
