//Fraction - описываем простую дробь
#pragma warning (disable:4326)
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
class Fraction;
Fraction operator*(Fraction right, Fraction left);
Fraction operator/(Fraction right, Fraction left);
class Fraction
{
	int integer;		//Целая часть
	int numerator;		//Числитель
	int denominator;	//Знаменатель
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

	//					Constructors:
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstructor:\t" << this << endl;
	}
	explicit Fraction(int integer)
	{
		//Single-argument constructor - Конструктор с одним параметром.
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "SingleArgConstructor:" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor\t" << this << endl;
	}
	explicit Fraction(double dec)
	{
		dec += 1e-11;
		integer = dec;
		dec -= integer;
		denominator = 1e+9;
		numerator = dec * denominator;
		reduce();
		
	}

	//				Operators:
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this * other;
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}
	//Increment/Decrement 
		Fraction & operator++() // Prefix increment
	{
		to_proper();
		integer++;
		return *this;
	}
		Fraction& operator++(int)
		{
			Fraction old = *this;// сохраняем текущее состояние объекта
			to_proper();
			integer++;
			return old;	
		} 
		                            // TYPE-CAST OPERATORS:
		explicit operator int()
		{
			return integer;
		}
		operator double() const
		{
			return integer+(double)numerator/denominator;
		}

	//				Methods:
	Fraction& to_proper()
	{
		//Переводит дробь в правильную - выделяет целую часть:
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction& to_improper()
	{
		//Переводит дробь в НЕправильную - интегрирует целую часть в числитель:
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& invert()
	{
		to_improper();
		int buffer = numerator;
		numerator = denominator;
		denominator = buffer;
		return *this;
	}
	Fraction& reduce()
	{
		if (numerator == 0)
		{
			denominator = 1;
			return *this;
		}
		//Сокращает дробь:
		int more; // большее
		int less; // меньшее
		int rest;
		if (numerator > denominator)
		{
			more = numerator;
			less = denominator;
		}
		else
		{
			less = numerator;
			more = denominator;
		}
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more; // Greates Common Divisor(Наибольший общий делитель)
		numerator /= GCD;
		denominator /= GCD;
		return to_proper();

	}
	void print()
	{
		if (integer)cout << integer;	//Если есть целая часть, выводим ее на экран
		if (numerator)
		{
			if (integer)cout << "(";
			cout << numerator << "/" << denominator;
			if (integer)cout << ")";
		}
		else if (integer == 0)cout << 0;
		cout << endl;
	}
	Fraction& operator+=(const Fraction& other)
	{
		return *this = *this * other;
	}
};
ostream& operator <<(ostream& os, const Fraction& obj)
{
	if (obj.get_integer())cout << obj.get_integer();	//Если есть целая часть, выводим ее на экран
	if (obj.get_numerator())
	{
		if (obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	else if (obj.get_integer() == 0)os << 0;
	return os;
}
Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
#ifdef DEBUG
	Fraction result;
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
		);
	//result.set_numerator(left.get_numerator()* right.get_numerator());
	//result.set_denominator(left.get_denominator()* right.get_denominator());
	result.to_proper();
	return result;
#endif // DEBUG
	// Явно вызываем конструктор прямо в return-е
	// этот конструктор создаёт временный безымянный объект, который return сразу же возвращает на место вызова:
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
}
#ifdef operator
Fraction operator/(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator() * right.get_denominator(),
		left.get_denominator() * right.get_numerator()
	).to_proper();
}
#endif // operator
Fraction operator/(Fraction left, Fraction right)
{
	return left * right.invert();
}
//                     COmparisom operators:
bool operator==(Fraction left, Fraction right)
{
#ifdef DEBUG
	left.to_improper();
	right.to_improper();
	if (left.get_numerator() * right.get_denominator() == right.get_numerator() * left.get_denominator())
		return true;
	else
		return false;
#endif // DEBUG
	//return left.get_numerator()* right.get_denominator() == right.get_numerator() * left.get_denominator();
	return left.to_improper().get_numerator() * right.get_denominator() == right.to_improper().get_numerator() * left.get_denominator();
}
bool operator!=(const Fraction left, const Fraction right)
{
	return !(left == right);
}
bool operator>(Fraction left, Fraction right)
{
	return 
		left.to_improper().get_numerator() * right.get_denominator() > right.to_improper().get_numerator() * left.get_denominator();
}
bool operator<(Fraction left, Fraction right)
{
	return 
		left.to_improper().get_numerator() * right.get_denominator() < right.to_improper().get_numerator() * left.get_denominator();
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	//return left > right || left == right;
	return !(left < right);
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	//return left < right || left == right;
	return !(left > right);
}

//#define ostream_check
//#define CONSTRUCTORS_CHECK
//#define arithmetical_operator_check
//#define comparisom_operators
//#define TYPE_CONVERSION_BASICS
//#define conversion_from_other_to_class
void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	Fraction A;		//Default constructor
	A.print();
	Fraction B = 5;	//Single-argument constructor (Конструктор с одним параметром).
	B.print();
	Fraction C(1, 2);
	C.print();
	Fraction D(2, 3, 4);
	D.print();
#endif // CONSTRUCTORS_CHECK

#ifdef ostream_check
	Fraction A(14, 4);
	A.to_proper();
	A.print();
	A.to_improper();
	cout << A << endl;
#endif // ostream_check
#ifdef arithmetical_operators_check
	int a = 2;
	int b = 3;
	int c = a * b;
	Fraction A(1, 2, 3);
	Fraction B(2, 4, 5);
	cout << A << endl;
	cout << B << endl;
	Fraction C = A * B;
	cout << C << endl;
	Fraction D = A / B;
	cout << D << endl;
	A *= B;
	cout << A << endl;
	A /= B;
	cout << A << endl;
	cout << ++A << endl;
	A = B++;
	cout << A << endl;
	cout << B << endl;
#endif // arithmetical_operators_check
#ifdef comparisom_operators
	Fraction A(1, 5, 10);
	Fraction B(1, 100, 220);
	cout << (A == B) << endl;
	cout << (A != B) << endl;
	cout << (A > B) << endl;
	cout << (A < B) << endl;
	cout << (A >= B) << endl;
	cout << (A <= B) << endl;
#endif // comparisom_operators
#ifdef CONVERSION_
	int a = 2;    // no conversions
	double b = 3; // conversion from int to double
				  //              from less more
	int c = b;    // conversion from double to int without data loss
	int d = 4.5;  // conversion from double to int with data loss
				  // from more to less with data loss
	cout << d << endl;
#endif // TYPE_CONVERSION_BASICS
#ifdef conversion_from_other_to_class
	double a = 2; // FROM INT TO DOUBLE(from less to more)
	Fraction A = Fraction(5);// FROM INT TO FRACTION( FROM LESS TO MORE)
	cout << A << endl;
	cout << "\n------------------------------------------------\n";
	Fraction B;
	cout << "\n------------------------------------------------\n";
	B = Fraction(8);
	cout << "\n------------------------------------------------\n";
	cout << B << endl;
#endif // conversion_from_other_to_class
	/*
	* --------------------
	* operator type()
	* {
	//conversion is here
	.....
	return ...;
	  }
	*/
	Fraction A(2, 3, 4);
	cout << A << endl;
	int a = A;
	cout << a << endl;
	double b = A;
	cout << b << endl;
	Fraction C = (Fraction)b;
	cout << C << endl;
	Fraction D(1, 3);
	cout << D * 3 << endl;
}