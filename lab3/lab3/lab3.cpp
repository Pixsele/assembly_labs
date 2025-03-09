#include<iostream>

//Вариант 5
//(a^2-6b)/a+13		a>b
//16				a==b
//(a^2-4)/b			a<b

int asm_calc(int a, int b) {
	int out_of_size = 0;
	int div_zero = 0;
	int result;
	__asm {

		mov ebx, a			;eax = ? | ebx = a | ecx = ? | edx = ?
		mov ecx, b			;eax = ? | ebx = a | ecx = b | edx = ?
		
		cmp ebx, ecx
		jg big				;a > b
		jl small			;a < b

		mov eax,16			;eax = 16 | ebx = a | ecx = b | edx = ?
		jmp answer

	big:
		imul ebx, ebx		;eax = ? | ebx = a*a | ecx = b | edx = ?
		jo overflow_flag

		imul ecx, 6			;eax = ? | ebx = a * a | ecx = 6*b | edx = ?
		jo overflow_flag

		sub ebx, ecx		;eax = ? | ebx = (a * a - 6*b) | ecx = 6 * b | edx = ?
		jo overflow_flag
		mov eax, ebx		;eax = (a * a - 6 * b) | ebx = (a * a - 6 * b) | ecx = 6 * b | edx = ?
		mov ebx, a			;eax = (a * a - 6 * b) | ebx = a | ecx = 6 * b | edx = ?
		jo overflow_flag

		cdq
		cmp ebx, 0
		je zero_flag
		idiv ebx			;eax = (a * a - 6 * b)/a | ebx = a | ecx = 6 * b | edx = ?

		add eax,13			; eax = (a * a - 6 * b) / a + 13 | ebx = a | ecx = 6 * b | edx = ?
		jo overflow_flag

		jmp answer

	small:
		imul ebx, ebx		;eax = ? | ebx = a * a | ecx = b | edx = ?
		jo overflow_flag

		sub ebx, 4			;eax = ? | ebx = (a * a-4) | ecx = b | edx = ?
		jo overflow_flag

		mov eax, ebx		;eax = (a * a - 4) | ebx = (a * a - 4) | ecx = b | edx = ?
		cdq
		cmp ecx, 0
		je zero_flag

		idiv ecx			;eax = (a * a - 4)/b | ebx = (a * a - 4) | ecx = b | edx = ?

		jmp answer

	answer :
		mov result, eax		;result = eax
		jmp exit_asm

	zero_flag :
		mov div_zero, 1
		mov result, 0
		jmp exit_asm

	overflow_flag :
		mov out_of_size, 1
		mov result, 0
		jmp exit_asm

	exit_asm :


	}

	if (div_zero) {
		std::cout << "Assembly div by zero error" << std::endl;
	}
	if (out_of_size) {
		std::cout << "Assembly out of size error" << std::endl;
	}
	return result;
}

int calc(int a, int b) {
	int result = 0;
	if (a > b) {
		if (a == 0) {
			std::cout << "C++ div by zero error" << std::endl;
		}
		else {
			result = (a * a - 6 * b) / a + 13;
		}
	}
	else if (a < b) {
		if (b == 0) {
			std::cout << "C++ div by zero error" << std::endl;
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
	int a, b;
	std::cin >> a;
	std::cin >> b;

	int result_1 = asm_calc(a, b);
	int result_2 = calc(a, b);

	std::cout << "Ass res: " << result_1 << std::endl;
	std::cout << "C++ res: " << result_2 << std::endl;

}