#include<iostream>


//(a^2-6b)/a+13		a>b
//16				a==b
//(a^2-4)/b			a<b


double asm_calc(double a, double b, int& error) {

	double result = 0, buff = 0;

	const double six = 6, four = 4, thirteen = 13, sixteen = 16;

	int zero_flag = 0;

	__asm {
		finit

		fld a		;st(0) = a
		fld b		;st(1) = a | st(0) = b
		fcom
		fstsw ax
		sahf
		ja less
		jb bigger

		fld sixteen
		jmp endcalc

		bigger:
			fstp buff		;st(0) = a
			fld a			;st(1) = a | st(0) = a
			fmul			;st(0) = a^2
			fld six			;st(1) = a^2 | st(0) = 6
			fld b			;st(2) = a^2 | st(1) = 6 | st(0) = b
			fmul			;st(1) = a^2 | st(0) = 6b
			fsub			;st(0) = a^2 - 6b
			fld a			;st(1) = a^2 - 6b | st(0) = a

			ftst
			fstsw ax
			sahf
			jz zero_error

			fdiv			;st(0) = (a^2 - 6b)/a
			fld thirteen	;st(1) = (a^2 - 6b)/a | st(0) = 13
			fadd			;st(0) = (a^2 - 6b)/a + 13
			
			jmp endcalc

		less:
			fstp buff		;st(0) = a
			fld a			;st(1) = a | st(0) = a
			fmul			;st(0) = a^2
			fld four		;st(1) = a^2 | st(0) = 4
			fsub			;st(0) = a^2 - 4
			fld b			;st(0) = a^2 - 4 | st(0) = b

			ftst
			fstsw ax
			sahf
			jz zero_error

			fdiv			;st(0) = (a^2 - 4)/b
			jmp endcalc

		zero_error:
			mov zero_flag, 1
			jmp pr_exit

		endcalc:
			fstp result
			jmp pr_exit

		pr_exit:

	}

	if (zero_flag) {
		std::cout << "Asm div by zero error" << std::endl;
		error = 1;
	}

	return result;

}


double cpp_calc(double a, double b, int& error) {
	double result = 0;
	if (a > b) {
		if (a == 0) {
			std::cout << "C++ div by zero error" << std::endl;
			error = 1;
		}
		else {
			result = (a * a - 6 * b) / a + 13;
		}
	}
	else if (a < b) {
		if (b == 0) {
			std::cout << "C++ div by zero error" << std::endl;
			error = 1;
		}
		else {
			result = (a * a - 4) / b;
		}
	}
	else {
		result = 16;
	}
	return result;
}


int main() {

	double a;
	double b;

	std::cin >> a;
	std::cin >> b;

	int asm_error = 0;
	int cpp_error = 0;

	double result_asm = asm_calc(a, b, asm_error);
	double result_cpp = cpp_calc(a, b, cpp_error);

	if (!cpp_error) {
		std::cout << "Cpp result : " << result_cpp << std::endl;
	}

	if (!asm_error) {
		std::cout << "Asm result : " << result_asm << std::endl;
	}
}