#include<iostream>

//Вариант 5
//(2*b - a + b/c)/(c/4 + 1);

int asm_calc(int a, int b, int c) {
	int out_of_size = 0;
	int div_zero = 0;
	int result;
	__asm {

		mov eax, b					;eax = b | ebx = ? | ecx = ? | edx = ?
		mov ebx, c					;eax = b | ebx = c | ecx = ? | edx = ?
		cmp ebx, 0					;ebx == 0 ?
		je zero_flag
		cdq
		idiv ebx					;eax = b / c | ebx = c | ecx = ? | edx = ?
		jo overflow_flag

		mov ecx, eax				;eax = b / c | ebx = c | ecx = b / c | edx = ?

		mov eax, b					;eax = b | ebx = c | ecx = b / c | edx = ?
		imul eax, 2					;eax = eax * 2 | ebx = c | ecx = b / c | edx = ?
		jo overflow_flag

		mov ebx, a					;eax = b | ebx = a | ecx = b / c | edx = ?
		sub eax, ebx				;eax = (2 * b - a) | ebx = a | ecx = b / c | edx = ?
		jo overflow_flag

		add eax, ecx				;eax = (2 * b - a + b / c) | ebx = a | ecx = b / c | edx = ?
		jo overflow_flag

		mov ecx, eax				;eax = (2 * b - a + b / c) | ebx = a | ecx = (2 * b - a + b / c) | edx = ?

		mov eax, c					;eax = c | ebx = a | ecx = (2 * b - a + b / c) | edx = ?
		mov ebx, 4					;eax = c | ebx = 4 | ecx = (2 * b - a + b / c) | edx = ?
		cdq
		idiv ebx					;eax = c / 4 | ebx = 4 | ecx = (2 * b - a + b / c) | edx = ?
		jo overflow_flag

		inc eax						;eax = c / 4 + 1 | ebx = 4 | ecx = (2 * b - a + b / c) | edx = ?
		jo overflow_flag

		mov ebx, eax				;eax = c / 4 + 1 | ebx = c / 4 + 1 | ecx = (2 * b - a + b / c) | edx = ?
		mov eax, ecx				;eax = (2 * b - a + b / c) | ebx = c / 4 + 1 | ecx = (2 * b - a + b / c) | edx = ?
		cdq
		idiv ebx					;eax = (2*b-a+b/c)/(c/4+1) | ebx = c / 4 + 1 | ecx = (2 * b - a + b / c) | edx = ?
		jo overflow_flag
		
		jmp answer

		answer :
			mov result, eax; result = eax
			jmp exit_asm

		zero_flag:
			mov div_zero, 1
			mov result, 0
			jmp exit_asm

		overflow_flag:
			mov out_of_size, 1
			mov result ,0
			jmp exit_asm

		exit_asm:
			

	}

	if (div_zero) {
		std::cout << "Assembly div by zero error" << std::endl;
	}
	if (out_of_size) {
		std::cout << "Assembly out of size error" << std::endl;
	}
	return result;
}

int calc(int a, int b, int c) {

	int result = 0;

	int temp = c / 4 + 1;

	if (c == 0 || temp == 0) {
		std::cout << "C++ div by zero error" << std::endl;
	}
	else {
		result = (2 * b - a + b / c) / temp;
	}

	return result;
}

int main() {
	int a, b, c;
	std::cin >> a;
	std::cin >> b;
	std::cin >> c;

	int result_1 = asm_calc(a, b, c);
	int result_2 = calc(a, b, c);

	std::cout << "Ass res: " << result_1 << std::endl;
	std::cout << "C++ res: " << result_2 << std::endl;

}