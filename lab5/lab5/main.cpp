#include<iostream>


//(2*b - a + b/c)/(c/4 + 1)


double asm_calc(double a, double b, double c, int& error) {

	double result = 0;
	 
	const double two = 2, four = 4, one = 1;

	int zero_flag  = 0;

	__asm {

		finit

		fld two			;st(0) = 2
		fld b			;st(1) = 2 | st(0) = b
		fmul			;st(0) = 2*b
		fld a			;st(1) = 2*b | st(0) = a
		fsub			;st(0) = 2*b - a
		fld b			;st(1) = 2*b - a | st(0) = b
		fld c			;st(2) = 2*b - a | st(1) = b | st(0) = c

		ftst
		fstsw ax
		sahf
		jz zero_error

		fdiv			;st(1) = 2*b - a | st(0) = b/c
		fadd			;st(0) = 2*b - a + b/c

		fld c			;st(1) = 2*b - a + b/c | st(0) = c
		fld four		;st(2) = 2*b - a + b/c | st(1) = c | st(0) = 4
		fdiv			;st(1) = 2*b - a + b/c | st(0) = c/4
		fld one			;st(2) = 2*b - a + b/c | st(1) = c/4 | st(0) = 1
		fadd			;st(1) = 2*b - a + b/c | st(0) = c/4 + 1
		
		ftst
		fstsw ax
		sahf
		jz zero_error

		fdiv			;st(0) = (2*b - a + b/c)/(c/4 + 1)

		jmp write_result

		zero_error:
			mov zero_flag, 1
			jmp pr_exit

		write_result:
			fstp result
			

		pr_exit:


	}
	if (zero_flag) {
		std::cout << "Asm div by zero error" << std::endl;
		error = 1;
	}

	return result;

}

double cpp_calc(double a, double b, double c, int& error) {
	double result = 0;

	double temp = c / 4 + 1;

	if (c == 0 || temp == 0) {
		std::cout << "C++ div by zero error" << std::endl;
		error = 1;
	}
	else {
		result = (2 * b - a + b / c) / temp;
	}

	return result;
}


int main() {

	double a;
	double b;
	double c;

	std::cin >> a;
	std::cin >> b;
	std::cin >> c;

	int asm_error = 0;
	int cpp_error = 0;

	double result_asm = asm_calc(a, b, c, asm_error);
	double result_cpp = cpp_calc(a, b, c, cpp_error);

	if (!cpp_error) {
		std::cout << "Cpp result : " << result_cpp << std::endl;
	}

	if (!asm_error) {
		std::cout << "Asm result : " << result_asm << std::endl;

	}
}