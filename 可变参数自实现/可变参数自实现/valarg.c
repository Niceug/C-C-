#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//�ɱ������ʵ��,������в���.
void test(int first, ...) {
	printf("��һ�������ĵ�ַ��%p\n", &first);
	printf("�ڶ��������ĵ�ַ��%p\n", &first + 1);
	printf("�ڶ���������ֵ��%d\n", *(&first + 1));
}
void my_args(int first, ...) {

	//������һ������
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

//ʵ��printf()����,���Ը�ʽ��%c, %d||%i, %o, %x, %s
void my_printf(char* format, ...) {
	
	//������һ��format������������ǲ����б�,����ƫ��4���ֽ�
	int* args = (char*)&format + 4;

	//������һ������,�ҳ����е�%d,%s...
	while (*format != '\0') {

		if (*format == '%')
		{
			//���������%�����ڶ����ַ�
			if (*(format + 1) == 'c') {
				putc((char)args, stdout);
				(char*)args++;
			}
			else if (*(format + 1) == 'd' || *(format + 1) == 'i')
			{
				char buffer[64] = { 0 };
				//ȡ���������
				int i = *args;
				//ʹ��itoa������ת�����ַ�
				itoa(i, buffer, 10);
				char *pstr = buffer;
				while (*pstr) putc(*pstr++, stdout);
				args += 1;
				
			}
			else if (*(format + 1) == 'o')
			{
				char buffer[64] = { 0 };
				//ȡ���������
				int i = *args;
				//ʹ��itoa������ת�����ַ�
				itoa(i, buffer, 8);
				char *pstr = buffer;
				while (*pstr) putc(*pstr++, stdout);
				args += 1;
			}
			else if (*(format + 1) == 'x')
			{
				char buffer[64] = { 0 };
				//ȡ���������
				int i = *args;
				//ʹ��itoa������ת�����ַ�
				itoa(i, buffer, 16);
				char *pstr = buffer;
				while (*pstr) putc(*pstr++, stdout);
				args += 1;
			}
			else if (*(format + 1) == 's')
			{
				//ȡ������ַ�
				char* str = *args;
				while (*str) putc(*str++, stdout);
				args += 1;
			}
			else 
			{
				//�����������
				putc(*format, stdout);
				format++;
				continue;
			}
			format += 2;
		}
		else 
		{
			//ֱ�����
			putc(*format++, stdout);
		}
	}
}



//ʵ��printf()����������ļ�

void my_printf1(char* format, ...) {

	//������һ��format������������ǲ����б�,����ƫ��4���ֽ�
	int* args = (char*)&format + 4;

	//�����txt�ļ�
	FILE* pfwrite = fopen("1.txt", "w");

	if (pfwrite == NULL) {
		perror("file open for write");
		exit();
	}

	//������һ������,�ҳ����е�%d,%s...
	while (*format != '\0') {

		if (*format == '%')
		{
			//���������%�����ڶ����ַ�
			if (*(format + 1) == 'c') {
				putc((char)args, stdout);
				(char*)args++;
			}
			else if (*(format + 1) == 'd' || *(format + 1) == 'i')
			{
				char buffer[64] = { 0 };
				//ȡ���������
				int i = *args;
				//ʹ��itoa������ת�����ַ�
				itoa(i, buffer, 10);
				char *pstr = buffer;
				while (*pstr) putc(*pstr++, pfwrite);
				args += 1;

			}
			else if (*(format + 1) == 'o')
			{
				char buffer[64] = { 0 };
				//ȡ���������
				int i = *args;
				//ʹ��itoa������ת�����ַ�
				itoa(i, buffer, 8);
				char *pstr = buffer;
				while (*pstr) putc(*pstr++, pfwrite);
				args += 1;
			}
			else if (*(format + 1) == 'x')
			{
				char buffer[64] = { 0 };
				//ȡ���������
				int i = *args;
				//ʹ��itoa������ת�����ַ�
				itoa(i, buffer, 16);
				char *pstr = buffer;
				while (*pstr) putc(*pstr++, pfwrite);
				args += 1;
			}
			else if (*(format + 1) == 's')
			{
				//ȡ������ַ�
				char* str = *args;
				while (*str) putc(*str++, pfwrite);
				args += 1;
			}
			else
			{
				//�����������
				putc(*format, pfwrite);
				format++;
				continue;
			}
			format += 2;
		}
		else
		{
			//ֱ�����
			putc(*format++, pfwrite);
		}
	}
	fclose(pfwrite);
}

int main() {
	my_printf1("%ʮ���ƣ�%d, �ַ�����%s, 8���ƣ�%o, 16���ƣ�%x\n", 20, "String", 20, 20);
	return 0;
}