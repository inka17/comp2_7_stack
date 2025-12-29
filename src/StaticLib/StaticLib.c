#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h>

#include "../include/lib_func.h"


// mem_size の容量でスタック用のメモリを確保する
void initialize(STACK* s, size_t mem_size)
{
	if (s == NULL) return;

	// ToDo: mem_sizeでメモリを確保しよう
	s->stack_pointer = NULL;
	s->stack_memory = NULL;
	s->end = NULL;
	
	if (mem_size < sizeof(int)) return;

	s->stack_memory = (int*)malloc(mem_size);
	if (!s->stack_memory) return;

	s->stack_pointer = s->stack_memory;
	s->end = s->stack_memory + (mem_size / sizeof(int));
}


// 確保したメモリを解放する
void finalize(STACK* s)
{
	if (!s) return;

	free(s->stack_memory);

	s->stack_pointer = NULL;
	s->stack_memory = NULL;
	s->end = NULL;
}


// valの値をスタックに積む。実行の成否を返す
bool push(STACK* s, int val)
{
	if (!s || !s->stack_memory) return false;
	if (s->stack_pointer >= s->end) return false;

	*s->stack_pointer++ = val;
	return true;
}


// addrから始まるnum個の整数をスタックに積む。実行の成否を返す
bool push_array(STACK* s, int* addr, int num)
{
	if (!s || !s->stack_memory || !addr || num <= 0) return false;
	if (s->end - s->stack_pointer < num) return false;

	for (int i = num; i > 0; i--)
	{
		*(s->stack_pointer) = addr[i - 1];
		s->stack_pointer++;
	}

	return true;
}

// スタックから一つの要素を取り出す
int pop(STACK* s)
{
	if (!s || !s->stack_memory) return 0;
	if (s->stack_pointer <= s->stack_memory) return 0;

	s->stack_pointer = s->stack_pointer - 1;
	return *(s->stack_pointer);
}

// addrにスタックからnumの要素を取り出す。取り出せた個数を返す
int pop_array(STACK* s, int* addr, int num)
{
	if (!s || !s->stack_memory || !addr || num <= 0) return 0;

	int count = 0;

	while (count < num && s->stack_pointer > s->stack_memory)
	{
		s->stack_pointer--;
		addr[count] = *(s->stack_pointer);
		count++;
	}

	return count;
}