#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

class pin
{
public:
	fstream file;
	bool leg;
	int wr;
};



class micro
{
protected:
	uint8_t reg[4];
	pin pins[6];
	uint8_t ram[16];
	int8_t cf;
	vector<string> rom;
	uint8_t pc;

	void mov(uint8_t* a, uint8_t* b);	
	void add(uint8_t* a, uint8_t* b);	
	void sub(uint8_t* a, uint8_t* b);	
	void mul(uint8_t* a, uint8_t* b);	
	void div(uint8_t* a, uint8_t* b);	
	void mod(uint8_t* a, uint8_t* b);	
	void and(uint8_t* a, uint8_t* b);	
	void or (uint8_t* a, uint8_t* b);	
	void xor(uint8_t* a, uint8_t* b);	
	void shl(uint8_t* a, uint8_t* b);	
	void shr(uint8_t* a, uint8_t* b);	
	void cmp(uint8_t* a, uint8_t* b);	
	void jg(uint8_t* a);	
	void jge(uint8_t* a);	
	void jl(uint8_t* a);	
	void jle(uint8_t* a);	
	void jmp(uint8_t* a);	
	bool getPin(size_t i);	
	void setPin(size_t i, bool s);	

	void setRom(string f);
	void setDefPin();	
	void getDefPin();	
	void next();
public:
	micro();
	~micro();			
	bool getcommands();	
};