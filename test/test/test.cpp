#include <cstdlib>
#include <iostream>

using std::cout; 
using std::endl;


struct Expression
{
    virtual double evaluate() const = 0;
	virtual void visit(Visitor * visitor) const  = 0;
	virtual ~Expression() {/*std::cout << "call Exp destr" << endl;*/};
};

struct Number : Expression
{
    Number(double value)
        : value(value)
    {}

	double evaluate() const{ return value;};
	void visit(Visitor *visitor) const { visitor->visitNumber(this); }

private:
    double value;
public: 
	~Number() {/*std::cout << "call Numb destr" << endl;*/};
};

struct BinaryOperation : Expression
{
    /*
      Здесь op это один из 4 символов: '+', '-', '*' или '/', соответствующих операциям,
      которые вам нужно реализовать.
     */
    BinaryOperation(Expression const * left, char op, Expression const * right)
        : left(left), op(op), right(right)
    { }

	double evaluate() const{
		
		double res = 0;
		char op = this->op;
		switch(op)
		{
		case '+':{
			res = (*(this->left)).evaluate() + (*(this->right)).evaluate();
			break;}
		case '-':{
			res = (*(this->left)).evaluate() - (*(this->right)).evaluate();
			break;}
		case '*':{
			res = (*(this->left)).evaluate() * (*(this->right)).evaluate();
			break;}
		case '/':{
			res = (*(this->left)).evaluate() / (*(this->right)).evaluate();
			break;}
		}

		return res;
	};

	void visit(Visitor * visitor) const { visitor->visitBinaryOperation(this); }

private:
    Expression const * left;
    Expression const * right;
    char op;
public: 
	~BinaryOperation() {
		delete right;
		delete left;
		/*std::cout << "call Binary destr" << endl;*/};
};

struct Visitor {
    virtual void visitNumber(Number const * number) = 0;
    virtual void visitBinaryOperation(BinaryOperation const * binary) = 0;
    virtual ~Visitor() { }
};


bool check_equals(Expression const *left, Expression const *right)
{
	int* vpr_l = *(int**)left;
	int* vpr_r = *(int**)right;

	if(vpr_l == vpr_r)
		return true;
	else
		return false;
}


int main ()
{
	Number* x = new Number(4.5);
	Number* y = new Number(6.2);
	// сначала создаём объекты для подвыражения 4.5 * 5
	Expression * sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
	// потом используем его в выражении для +
	Expression * expr = new BinaryOperation(new Number(3), '+', sube);

	bool a = check_equals(sube, expr);
	bool b = check_equals(sube, x);
	bool c = check_equals(y, x);
	// вычисляем и выводим результат: 25.5
	std::cout << expr->evaluate() << std::endl;

	// тут освобождаются *все* выделенные объекты
	// (например, sube будет правым операндом expr, поэтому его удалять не нужно)
	delete expr;

	return 0;
}