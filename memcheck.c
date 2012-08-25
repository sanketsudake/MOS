#include"mem.h"
int main(){
	MEM *memory=NULL;
	memory=mem_init(memory);
	printf("%c\n",mem_getchar(memory,4,4));
	printf("%c\n",meml_getchar(memory,5));
	return 0;
}
