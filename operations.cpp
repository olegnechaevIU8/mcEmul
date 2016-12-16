#include "micro.h"


void micro::mov(uint8_t* a, uint8_t* b)
{
	*a = *b;
	cout << "moved" << endl;
}

void micro::add(uint8_t* a, uint8_t* b)
{
	*a += *b;
	cout << "+" << endl;
}

void micro::sub(uint8_t* a, uint8_t* b)
{
	*a -= *b;
	cout << "-" << endl;
}

void micro::mul(uint8_t* a, uint8_t* b)
{
	*a *= *b;
	cout << "-" << endl;
}

void micro::div(uint8_t* a, uint8_t* b)
{
	*a /= *b;
	cout << "//" << endl;
}

void micro::mod(uint8_t* a, uint8_t* b)
{
	*a %= *b;
	cout << "%" << endl;
}

void micro:: and (uint8_t* a, uint8_t* b)
{
	*a &= *b;
	cout << "&" << endl;
}

void micro:: or (uint8_t* a, uint8_t* b)
{
	*a |= *b;
	cout << "|" << endl;
}

void micro:: xor (uint8_t* a, uint8_t* b)
{
	*a ^= *b;
	cout << "^" << endl;
}

void micro::shl(uint8_t* a, uint8_t* b)
{
	*a <<= *b;
	cout << "<<" << endl;
}

void micro::shr(uint8_t* a, uint8_t* b)
{
	*a >>= *b;
	cout << ">>" << endl;
}

void micro::cmp(uint8_t* a, uint8_t* b)
{
	if (*a == *b)
		cf = 0;
	else
	{
		if (*a > *b)
			cf = 1;
		else
			cf = -1;
	}
	cout << "cmp" << endl;
}

void micro::jg(uint8_t* a)
{
	if (*a > rom.size())
		throw exception("trying going to wrong memmory!");
	if (cf == 1)
		pc = *a;
	cout << "jg" << endl;
}

void micro::jge(uint8_t* a)
{
	if (*a > rom.size())
		throw exception("trying going to wrong memmory!");
	if ((cf == 1) || (cf == 0))
		pc = *a;
	cout << "jge" << endl;
}

void micro::jl(uint8_t* a)
{
	if (*a > rom.size())
		throw exception("trying going to wrong memmory!");
	if (cf == -1)
		pc = *a;
	cout << "jl" << endl;
}

void micro::jle(uint8_t* a)
{
	if (*a > rom.size())
		throw exception("trying going to wrong memmory!");
	if ((cf == -1) || (cf == 0))
		pc = *a;
	cout << "jle" << endl;
}

void micro::jmp(uint8_t* a)
{
	if (*a > rom.size())
		throw exception("trying going to wrong memmory!");
	pc = *a;
	cout << "jmp" << endl;
}
