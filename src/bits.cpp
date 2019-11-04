#include "bits.h"

Bits::Bits()
{

}

Bits::Bits(const int &size)
{
	m_size = size;
	m_data = new unsigned char[m_size / 8];
	nullable();
}

Bits::Bits(const Bits &number) : Bits(number.m_size)
{
	for (int i = 0; i < m_size / 8; i++)
	{
		m_data[i] = number.m_data[i];
	}
}

Bits::Bits(const int &size, const std::string &number) : Bits(size)
{
	for (int i = 0; i < number.size(); i++)
	{
		bool value = number[number.size() - 1 - i] == '1';
		setDischarge(i, value);
	}
}

Bits::Bits(const std::string &number) : Bits(number.size() + (8 - number.size() % 8), number)
{ }

Bits::~Bits()
{ }

void Bits::add(const Bits &number)
{
	bool ca = false;
	for (int i = 0; i < m_size; i++)
	{
		bool c1 = getDischarge(i);
		bool c2 = number.getDischarge(i);


		if (c1 && c2)
		{
			setDischarge(i, ca);
			ca = true;
		}
		else if (!c1 && !c2)
		{
			setDischarge(i, ca);
			ca = false;
		}
		else if (c1 && !c2)
		{
			setDischarge(i, !ca);
		}
		else if (!c1 && c2)
		{
			setDischarge(i, !ca);
		}

		/*if (ca)
			{
				if (c1 && c2)
				{
					setDischarge(i, true);
					ca = true;
				}
				else if (!c1 && !c2)
				{
					setDischarge(i, true);
					ca = false;
				}
				else if (c1 && !c2)
				{
					setDischarge(i, false);
					ca = true;
				}
				else if (!c1 && c2)
				{
					setDischarge(i, false);
					ca = true;
				}
			}
			else
			{
				if (c1 && c2)
				{
					setDischarge(i, false);
					ca = true;
				}
				else if (!c1 && !c2)
				{
					setDischarge(i, false);
					ca = false;
				}
				else if (c1 && !c2)
				{
					setDischarge(i, true);
					ca = false;
				}
				else if (!c1 && c2)
				{
					setDischarge(i, true);
					ca = false;
				}
			}*/
	}
}

void Bits::sub(const Bits &number)
{
	bool ca = false;
	for (int i = 0; i < m_size; i++)
	{
		bool c1 = getDischarge(i);
		bool c2 = number.getDischarge(i);

		if (ca)
		{
			if (!c1)
			{
				c1 = true;
			}
			else
			{
				ca = false;
				c1 = false;
			}
		}

		if (c1 == c2)
		{
			setDischarge(i, false);
		}
		else if (c1 != c2)
		{
			setDischarge(i, true);
			if (!c1)
				ca = true;
		}

		/*if (ca)
			{
				if (!c1)
				{
					c1 = true;
				}
				else
				{
					ca = false;
					c1 = false;
				}
			}

			if (c1 && c2)
			{
				setDischarge(i, false);
			}
			else if (!c1 && !c2)
			{
				setDischarge(i, false);
			}
			else if (c1 && !c2)
			{
				setDischarge(i, true);
			}
			else if (!c1 && c2)
			{
				setDischarge(i, true);
				ca = true;
			}*/
	}
}

void Bits::mult(const Bits &number)
{
	if (number == Bits("0"))
	{
		*this = Bits("0");
		return;
	}
	if (number == Bits("1")) return;

	Bits temp_number = *this;
	*this = Bits("0");
	bool ca = false;
	for (int i = 0; i < m_size; i++)
	{
		bool c2 = number.getDischarge(i);
		if (!c2)
			continue;
		Bits n = temp_number;
		n <<= i;
		*this = *this + n;
	}
}

void Bits::div(const Bits &number) // FIXIT
{
	if (number == Bits("0")) throw "Divide by zero";
	if (number == Bits("1")) return;
	if (*this < number) { *this = Bits("0"); return; }
	if (*this == number) { *this = Bits("0"); return; }
	int temp_size = m_size > number.m_size ? m_size : number.m_size;
	int temp_real_size = realSize() > number.realSize() ? realSize() : number.realSize();


	int currentDischarge = realSize() - 1;
	Bits result = *this;
	this->nullable();
	while(result >= number)
	{
		result -= number;
		++*this;
	}
//	Bits result = *this;
//	Bits currentDiv = getDischarge(currentDischarge) == 1 ? Bits("1") : Bits("0");
//
//	while (currentDischarge != 0)
//	{
//		if (currentDiv < number)
//		{
//			result <<= 1;
//			currentDiv <<= 1;
//			currentDiv.setDischarge(0, getDischarge(--currentDischarge));
//		}
//		else
//		{
//			currentDiv -= number;
//			result <<= 1;
//			result.setDischarge(0, 1);
//			if (currentDischarge != 0)
//			{
//				currentDiv <<= 1;
//				currentDiv.setDischarge(0, getDischarge(--currentDischarge));
//			}
//		}
//	} OLD OLD OLD OLD OLD OLD
//	if (currentDiv != Bits("0"))
	//		result <<= 1;
}

Bits Bits::operator =(const Bits &number)
{
	Bits result(number);
	return result;
}

Bits &Bits::operator ++()
{
	this->add(Bits(m_size, "1"));
	return *this;
}

Bits Bits::operator ++(int)
{
	Bits result = *this;
	this->add(Bits(m_size, "1"));
	return result;
}

Bits &Bits::operator --()
{
	this->sub(Bits(m_size, "1"));
	return *this;
}

Bits Bits::operator --(int)
{
	Bits result = *this;
	this->sub(Bits(m_size, "1"));
	return result;
}

Bits Bits::operator +(const Bits &numberR) const
{
	Bits result = bitsFromMaxSize(*this, numberR);
	result.add(bitsFromMinSize(*this, numberR));
	return result;
}

Bits Bits::operator -(const Bits &numberR) const
{
	Bits result = bitsFromMaxSize(*this, numberR);
	result.sub(bitsFromMinSize(*this, numberR));
	return result;
}

Bits Bits::operator *(const Bits &numberR) const
{
	Bits result = bitsFromMaxSize(*this, numberR);
	result.mult(bitsFromMinSize(*this, numberR));
	return result;
}

Bits Bits::operator /(const Bits &numberR) const
{
	Bits result = bitsFromMaxSize(*this, numberR);
	result.div(bitsFromMinSize(*this, numberR));
	return result;
}

Bits &Bits::operator +=(const Bits &numberR)
{
	this->add(numberR);
	return *this;
}

Bits &Bits::operator -=(const Bits &numberR)
{
	this->sub(numberR);
	return *this;
}

Bits &Bits::operator *=(const Bits &numberR)
{
	this->mult(numberR);
	return *this;
}

Bits &Bits::operator /=(const Bits &numberR)
{
	this->div(numberR);
	return *this;
}

Bits Bits::operator&(const Bits &bits) const
{
	Bits result (m_size);
	int temp_size = m_size > bits.m_size ? m_size : bits.m_size;
	for(int i = 0; i < temp_size; i++)
	{
		bool lValue = getDischarge(i), rValue = bits.getDischarge(i);
		result.setDischarge(i, lValue & rValue);
	}
	return result;
}

Bits Bits::operator|(const Bits &bits) const
{
	Bits result (m_size);
	int temp_size = m_size > bits.m_size ? m_size : bits.m_size;
	for(int i = 0; i < temp_size; i++)
	{
		bool lValue = getDischarge(i), rValue = bits.getDischarge(i);
		result.setDischarge(i, lValue | rValue);
	}
	return result;
}

Bits Bits::operator^(const Bits &bits) const
{
	Bits result (m_size);
	int temp_size = m_size > bits.m_size ? m_size : bits.m_size;
	for(int i = 0; i < temp_size; i++)
	{
		bool lValue = getDischarge(i), rValue = bits.getDischarge(i);
		result.setDischarge(i, lValue ^ rValue);
	}
	return result;
}

Bits Bits::operator~() const
{
	Bits result (m_size);
	for(int i = 0; i < m_size; i++)
	{
		bool value = getDischarge(i);
		result.setDischarge(i, !value);
	}
	return result;
}

Bits &Bits::operator <<=(const int &numbers)
{
	*this = *this << numbers;
	return *this;
}

Bits &Bits::operator >>=(const int &numbers)
{
	*this = *this >> numbers;
	return *this;
}

bool Bits::operator ==(const Bits &number) const
{
	int r1 = realSize(), r2 = number.realSize();
	if (r1 != r2)
		return false;
	for (int i = 0; i < realSize(); i++)
	{
		if (getDischarge(i) != number.getDischarge(i))
			return false;
	}
	return true;
}

bool Bits::operator >(const Bits &number) const
{
	int temp_read_size = realSize() > number.realSize() ? realSize() : number.realSize();
	for (int i = temp_read_size; i >= 0; i--)
	{
		bool c1 = getDischarge(i),
				c2 = number.getDischarge(i);
		if (c1 != c2)
			return c1 > c2;
	}
	return false;
}

bool Bits::operator >=(const Bits &number) const
{
	int temp_read_size = realSize() > number.realSize() ? realSize() : number.realSize();
	for (int i = temp_read_size; i >= 0; i--)
	{
		bool c1 = getDischarge(i),
				c2 = number.getDischarge(i);
		if (c1 != c2)
			return c1 > c2;
	}
	return true;
}

Bits Bits::operator <<(const int &numbers) const
{
	Bits result = *this;
	for (int i = m_size - 1; i >= 0; i--)
	{
		if (i >= numbers)
			result.setDischarge(i, getDischarge(i - numbers));
		else
			result.setDischarge(i, 0);
	}
	return result;
}

Bits Bits::operator >>(const int &numbers) const
{
	Bits result = *this;
	for (int i = 0; i < m_size; i++)
	{
		if (i + numbers < m_size)
			result.setDischarge(i, getDischarge(i + numbers));
		else
			result.setDischarge(i, 0);
	}
	return result;
}

Bits Bits::pow(const int &n) const
{
	if (n == 0)
		return Bits("1");
	if (n == 1)
		return *this;
	Bits result = *this;
	for (int i = 1; i < n; i++)
	{
		result *= *this;
	}
	return result;
}

Bits Bits::sqrt() const
{
	Bits two = Bits::fromNumber("10", 2);
	Bits result = two.pow(this->realSize() / 2);
	return result;
}

int Bits::realSize() const
{
	int result = 0;
	for (int i = 0; i < m_size; i++)
	{
		if (getDischarge(i))
			result = i + 1;
	}
	return result;
}

std::string Bits::toString(const int &n) const
{
	std::string str;
	if (n == 2)
	{
		for (int i = m_size - 1; i >= 0; i--)
		{
			bool d = getDischarge(i);
			if (!d && str.size() == 0)
				continue;
			str += (getDischarge(i) ? '1' : '0');
		}
	}
	else if (n == 10)
	{
		double n = 0,
				to = m_size;
		for (int i = 0; i < to; i++)
		{
			if (!getDischarge(i))
				continue;
			n += std::pow(2, i);
		}
		str = std::to_string(n);
	}
	if(str == "")
		return "0";
	return str;
}
#include <iostream>

Bits Bits::fromNumber(const std::string &number, const int &ss)
{
	if(ss == 2)
		return Bits(number);
	if(ss == 10)
	{
		Bits result ("0");
		for(unsigned long long j = 0, i = number.size() - 1; j < number.size() ; j++, i--)
		{
			Bits temp;
			switch (number[i])
			{
				case '0': temp = Bits::fromNumber("0", 2); break;
				case '1': temp = Bits::fromNumber("1", 2); break;
				case '2': temp = Bits::fromNumber("10", 2); break;
				case '3': temp = Bits::fromNumber("11", 2); break;
				case '4': temp = Bits::fromNumber("100", 2); break;
				case '5': temp = Bits::fromNumber("101", 2); break;
				case '6': temp = Bits::fromNumber("110", 2); break;
				case '7': temp = Bits::fromNumber("111", 2); break;
				case '8': temp = Bits::fromNumber("1000", 2); break;
				case '9': temp = Bits::fromNumber("1001", 2); break;
			}
			Bits ten = Bits::fromNumber("1010", 2);
			temp *= ten.pow(static_cast<int>(j));
			result += temp;
		}
		return result;
	}
}

void Bits::setDischarge(const int &n, const bool &value)
{
	int numberByte = n / 8, numberBit = n % 8;
	unsigned char* temp_data = &m_data[numberByte];
	if (value)
	{
		*temp_data |= (1 << numberBit);
	}
	else
	{
		*temp_data &= ~(1 << numberBit);
	}
}

void Bits::nullable()
{
	for (int i = 0; i < m_size / 8; i++)
		m_data[i] = 0;
}
