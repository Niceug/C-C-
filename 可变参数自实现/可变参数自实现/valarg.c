#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//可变参数自实现,输出所有参数.
void test(int first, ...) {
	printf("第一个参数的地址：%p\n", &first);
	printf("第二个参数的地址：%p\n", &first + 1);
	printf("第二个参数的值：%d\n", *(&first + 1));
}
void my_args(int first, ...) {

	//跳过第一个参数
	char *args = NULL;
	args = (char*)&first + 4;
	while (first--) {
		char buffer[64] = {0};
		char *pstr = buffer;
		itoa(*(int *)args, buffer, 10);
		while (*pstr)
			putc(*pstr++, stdout);
		args += 4;
	}
}

//实现printf()函数,可以格式化%c, %d||%i, %o, %x, %s
void my_printf(char* format, ...) {
	
	//跳过第一个format参数，后面才是参数列表,所以偏移4个字节
	int* args = (char*)&format + 4;

	//分析第一个参数,找出其中的%d,%s...
	while (*format != '\0') {

		if (*format == '%')
		{
			//如果遇到了%分析第二个字符
			if (*(format + 1) == 'c') {
				putc((char)args, stdout);
				(char*)args++;
			}
			else if (*(format + 1) == 'd' || *(format + 1) == 'i')
			{
				char buffer[64] = { 0 };
				//取得这个整数
				int i = *args;
				//使用itoa将整数转换成字符
				itoa(i, buffer, 10);
				char *pstr = buffer;
				while (*pstr) putc(*pstr++, stdout);
				args += 1;
				
			}
			else if (*(format + 1) == 'o')
			{
				char buffer[64] = { 0 };
				//取得这个整数
				int i = *args;
				//使用itoa将整数转换成字符
				itoa(i, buffer, 8);
				char *pstr = buffer;
				while (*pstr) putc(*pstr++, stdout);
				args += 1;
			}
			else if (*(format + 1) == 'x')
			{
				char buffer[64] = { 0 };
				//取得这个整数
				int i = *args;
				//使用itoa将整数转换成字符
				itoa(i, buffer, 16);
				char *pstr = buffer;
				while (*pstr) putc(*pstr++, stdout);
				args += 1;
			}
			else if (*(format + 1) == 's')
			{
				//取得这个字符
				char* str = *args;
				while (*str) putc(*str++, stdout);
				args += 1;
			}
			else 
			{
				//处理其他情况
				putc(*format, stdout);
				format++;
				continue;
			}
			format += 2;
		}
		else 
		{
			//直接输出
			putc(*format++, stdout);
		}
	}
}



//实现printf()函数输出到文件

void my_printf1(char* format, ...) {

	//跳过第一个format参数，后面才是参数列表,所以偏移4个字节
	int* args = (char*)&format + 4;

	//输出到txt文件
	FILE* pfwrite = fopen("1.txt", "w");

	if (pfwrite == NULL) {
		perror("file open for write");
		exit();
	}

	//分析第一个参数,找出其中的%d,%s...
	while (*format != '\0') {

		if (*format == '%')
		{
			//如果遇到了%分析第二个字符
			if (*(format + 1) == 'c') {
				putc((char)args, stdout);
				(char*)args++;
			}
			else if (*(format + 1) == 'd' || *(format + 1) == 'i')
			{
				char buffer[64] = { 0 };
				//取得这个整数
				int i = *args;
				//使用itoa将整数转换成字符
				itoa(i, buffer, 10);
				char *pstr = buffer;
				while (*pstr) putc(*pstr++, pfwrite);
				args += 1;

			}
			else if (*(format + 1) == 'o')
			{
				char buffer[64] = { 0 };
				//取得这个整数
				int i = *args;
				//使用itoa将整数转换成字符
				itoa(i, buffer, 8);
				char *pstr = buffer;
				while (*pstr) putc(*pstr++, pfwrite);
				args += 1;
			}
			else if (*(format + 1) == 'x')
			{
				char buffer[64] = { 0 };
				//取得这个整数
				int i = *args;
				//使用itoa将整数转换成字符
				itoa(i, buffer, 16);
				char *pstr = buffer;
				while (*pstr) putc(*pstr++, pfwrite);
				args += 1;
			}
			else if (*(format + 1) == 's')
			{
				//取得这个字符
				char* str = *args;
				while (*str) putc(*str++, pfwrite);
				args += 1;
			}
			else
			{
				//处理其他情况
				putc(*format, pfwrite);
				format++;
				continue;
			}
			format += 2;
		}
		else
		{
			//直接输出
			putc(*format++, pfwrite);
		}
	}
	fclose(pfwrite);
}

int main() {
	my_printf1("%十进制：%d, 字符串：%s, 8进制：%o, 16进制：%x\n", 20, "String", 20, 20);
	return 0;
}