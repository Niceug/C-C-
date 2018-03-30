
#include "exchange.h"
//状态轮转函数
void exchange(FILE* pfread, FILE* pfwrite) {
	enum STATE state = NULL_STATE;
	while (state != END_STATE) {
		switch (state) {
			case NULL_STATE:
				DoNULL_State(pfread, pfwrite, &state);
				break;
			case C_STATE:
				DoC_State(pfread, pfwrite, &state);
				break;
			case CPP_STATE:
				DoCPP_State(pfread, pfwrite, &state);
				break;
		}
	}
}
//处理无状态函数
void DoNULL_State(FILE* pfread, FILE* pfwrite, enum STATE * ps) {

	char first = fgetc(pfread);
	char second = 0;

	switch (first) {
		case '/' :
			second = fgetc(pfread);
			switch (second)
			{
				case '/': 
					*ps = CPP_STATE;
					fputc(first, pfwrite);
					fputc(second, pfwrite);
					break;
				case '*':
					*ps = C_STATE;
					fputc('/', pfwrite);
					fputc('/', pfwrite);
					break;
				default:
					fputc(second, pfwrite);
						break;
			}
			break;
		case EOF:
			*ps = END_STATE;
			break;
		default:
			fputc(first, pfwrite);
			break;
	}

}
//处理c状态函数
void DoC_State(FILE* pfread, FILE* pfwrite, enum STATE * ps) {
	char first = fgetc(pfread);
	char second = 0;
	char third = 0;
	switch (first)
	{
		case '*':
			second = fgetc(pfread);
			switch (second)
			{
				case '/':
					*ps = NULL_STATE;
					third = fgetc(pfread);
					switch (third)
					{
						case '\n':
							fputc(third, pfwrite);
							break;
						case EOF:
							*ps = END_STATE;
							break;
						default:
							fputc('\n', pfwrite);
							fputc(third, pfwrite);
							break;
					}
					break;
				default:
					fputc(first, pfwrite);
					fputc(second, pfwrite);
					break;
			}
			break;
		case '\n':
			fputc(first, pfwrite);
			fputc('/', pfwrite);
			fputc('/', pfwrite);
			break;
		default:
			fputc(first, pfwrite);
			break;
	}
}
//处理cpp状态函数
void DoCPP_State(FILE* pfread, FILE* pfwrite, enum STATE * ps) {
	char first = fgetc(pfread);
	switch (first)
	{
		case '\n':
			*ps = NULL_STATE;
			fputc(first, pfwrite);
			break;
		case EOF:
			*ps = END_STATE;
			break;
		default:
			fputc(first, pfwrite);
			break;
	}
}