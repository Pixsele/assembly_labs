#include<iostream>


int asm_calc(int a, int b, int c) {


	int out_of_size = 0;
	int result;
	__asm {

		mov eax, b; eax = b
		imul eax, 2; eax = eax * 2
		jo overflow_flag

		mov ebx, a; ebx = a
		sub eax, ebx; eax = 2 * b - a
		jo overflow_flag

		push eax;

		mov eax, b;eax = b
		mov ebx, c;eax = c
		cmp ebx, 0; ebx == 0 ?
		je zero_flag
		cdq
		idiv ebx;eax = eax/c
		jo overflow_flag

		pop ebx; ebx = (2*b-a)
		add eax,ebx; eax = (2*b-a+b/c)
		jo overflow_flag

		push eax

		mov eax,c; eax = c
		mov ebx,4;ebx = 4
		cdq
		idiv ebx; eax = eax/ebx
		jo overflow_flag

		inc eax; eax + 1
		jo overflow_flag

		mov ebx,eax; ebx = eax
		pop eax; eax = (2*b-a+b/c)
		cdq
		idiv ebx;eax = (2*b-a+b/c)/(c/4+1)
		jo overflow_flag
		
		jmp answer

		answer:
			mov result,eax; result = eax
			jmp exit_ass

		zero_flag:
			jmp exit_ass

		overflow_flag:
			mov out_of_size, 0
			jmp exit_ass

		exit_ass:
				xor eax, eax;
	}
	return result;
}

int calc(int a, int b, int c) {

	int result = 0;

	int temp = c / 4 + 1;

	if (c == 0 || temp == 0) {
		std::cout << "???";
	}
	else {
		result = (2 * b - a + b / c) / temp;
	}

	return result;
}

int main() {


//(2*b - a + b/c)/(c/4 + 1);

	int a, b, c;
	std::cin >> a;
	std::cin >> b;
	std::cin >> c;

	int result_1 = asm_calc(a, b, c);
	int result_2 = calc(a, b, c);

	std::cout << "Ass res: " << result_1 << std::endl;
	std::cout << "Res: " << result_2 << std::endl;

}



