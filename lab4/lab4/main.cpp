#include<iostream>


//5)	Найти сумму отрицательных элементов массива A = { a[i] }, удовлетворяющих условию : a[i] <= d.

void show_error() {
		std::cout << "Asm: out of memory";
}


int asm_calc(int* arr, int size_arr, int d, bool& error) {


	int result = 0;
	int out_of_zero = 0;

	__asm {
		xor edx,edx				;eax = ? | ebx = ? | ecx = ? | edx = 0

		mov ebx, arr			;eax = ? | ebx = arr | ecx = ? | edx = 0
		mov ecx, 0				;eax = ? | ebx = arr | ecx = 0 | edx = 0

		For:
			cmp ecx,size_arr
			je Result

			mov eax,[ebx + 4*ecx]			;eax = *(arr+ecx*4) | ebx = arr | ecx = i | edx = ?
			cmp eax,0
			jl Is_neg
			inc ecx							;eax = *(arr + ecx * 4) | ebx = arr | ecx = i+1 | edx = ?
			jmp For


		Is_neg:
			cmp eax,d
			jle Is_less_d
			inc ecx							;eax = *(arr + ecx * 4) | ebx = arr | ecx = i+1 | edx = ?
			jmp For

		Is_less_d:
			add edx,eax						;eax = *(arr + ecx * 4) | ebx = arr | ecx = i | edx = edx + eax
			jo Overflow_flag
			inc ecx							;eax = *(arr + ecx * 4) | ebx = arr | ecx = i + 1 | edx = edx + eax
			jmp For


		Overflow_flag:
			mov out_of_zero, 1
			jmp Exit_asm

		Result:
			mov eax, edx					;eax = edx | ebx = arr | ecx = i + 1 | edx = ?
			mov result,eax
			jmp Exit_asm

		Exit_asm:

	}
	
	if (out_of_zero) {
		show_error();
		error = true;
	}

	return result;
}

int cpp_calc(int* arr, int size_arr, int d) {

	int result = 0;
	for (int i = 0; i < size_arr; i++) {
		if (arr[i] < 0 && arr[i] <= d) {
			result += arr[i];
		}
	}

	return result;
}

int main() {

	int size;
	std::cout << "Enter count of elemetns: ";
	std::cin >> size;

	int* arr = new int[size];
	for (int i = 0; i < size; i++) {

		std::cout << "Element[" << i << "] = ";
		std::cin >> arr[i];
	}

	int d;
	std::cout << "Enter d: ";
	std::cin >> d;

	bool error_asm = 0;
	int asm_result = asm_calc(arr, size, d, error_asm);
	int cpp_result = cpp_calc(arr, size, d);

	if (!error_asm) {
		std::cout << "Asm_result: " << asm_result << std::endl;
		std::cout << "Cpp_result: " << cpp_result << std::endl;
	}
}