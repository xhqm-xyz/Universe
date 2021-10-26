
class plural  //n元复数
{
public:
	measure var;
	Data var_i;

	plural() { var = 0; };
	plural(measure mea) { var = mea; };
	plural(measure mea, measure mea_i) { var = mea; var_i.push_back(mea_i); };
	plural(measure mea, Data complex_i) :var(mea), var_i(complex_i) {};

	plural operator= (const measure mea);
	plural operator= (const plural mea);


	bool operator == (const plural mea);
	bool operator != (const plural mea);

	plural operator += (const plural mea);
	plural operator -= (const plural mea);
	plural operator *= (const plural mea);
	plural operator /= (const plural mea);
																  
	friend plural operator + (const plural& A, const plural& B);
	friend plural operator - (const plural& A, const plural& B);
	friend plural operator * (const plural& A, const plural& B);
	friend plural operator / (const plural& A, const plural& B);
};

class complex
{
public:
	complex();
	~complex();

private:

};

complex::complex()
{
}

complex::~complex()
{
}







class integer :public complex //整数
{
public:
	integer() {};
};
