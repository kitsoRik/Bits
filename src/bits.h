#ifndef BITS_H
#define BITS_H

#include <string>
#include <cmath>

class Bits
{
	int m_size;
	unsigned char* m_data;
public:
	Bits();
	Bits(const int& size);
	Bits(const Bits& number);
	Bits(const int& size, const std::string& number);
	Bits(const std::string& number);

	~Bits();

	void add(const Bits& number);
	void sub(const Bits& number);
	void mult(const Bits& number);
	void div(const Bits& number);

	Bits operator =(const Bits &number);

	Bits& operator ++();
	Bits operator ++(int);
	Bits& operator --();
	Bits operator --(int);

	Bits operator +(const Bits & numberR) const;
	Bits operator -(const Bits & numberR) const;
	Bits operator *(const Bits & numberR) const;
	Bits operator /(const Bits & numberR) const;
	Bits& operator +=(const Bits & numberR);
	Bits& operator -=(const Bits & numberR);
	Bits& operator *=(const Bits & numberR);
	Bits& operator /=(const Bits & numberR);

	Bits operator&(const Bits & bits) const;
	Bits operator|(const Bits & bits) const;
	Bits operator^(const Bits & bits) const;

	Bits& operator&=(const Bits & bits) { *this = *this & bits; return *this; }
	Bits& operator|=(const Bits & bits) { *this = *this | bits; return *this; }
	Bits& operator^=(const Bits & bits) { *this = *this ^ bits; return *this; }

	Bits operator~() const;

	Bits operator <<(const int& numbers) const;
	Bits operator >>(const int& numbers) const;

	Bits& operator <<=(const int& numbers);
	Bits& operator >>=(const int& numbers);

	bool operator ==(const Bits & number) const;
	inline bool operator != (const Bits & number) const { return !(*this == number); }
	bool operator >(const Bits & number) const;
	inline bool operator < (const Bits & number) const { return !(*this >= number); }
	bool operator >= (const Bits & number) const;
	inline bool operator <= (const Bits & number) const { return !(*this > number); }

	Bits pow(const int& n) const;
	Bits sqrt() const;

	int realSize() const;

	std::string toString(const int& n = 10) const;

	static Bits fromNumber(const std::string &number, const int &ss);

private:
	void setDischarge(const int& n, const bool& value);

	inline bool getDischarge(const int& n) const
	{
		int numberByte = n / 8, numberBit = n % 8;
		return m_data[numberByte] & (1 << numberBit);
	}

	void nullable();

	static inline const Bits& bitsFromMaxSize(const Bits &l, const Bits &r)
	{ return l.m_size > r.m_size ? l : r; }

	static inline const Bits& bitsFromMinSize(const Bits &l, const Bits &r)
	{ return l.m_size <= r.m_size ? l : r; }
};

#endif // BITS_H
