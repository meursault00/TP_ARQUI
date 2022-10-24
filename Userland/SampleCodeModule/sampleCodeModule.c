/* sampleCodeModule.c */
#include <system_calls.h>

int main() {
	char buffer[2]={0};
	sys_write(1,"nashe",6);
	buffer[0]=getchar();
	sys_write(1,buffer,2);
	return 0;
}