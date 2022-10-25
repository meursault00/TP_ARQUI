/* sampleCodeModule.c */
#include <system_calls.h>
#include <library.h>
int main() {

	int a = 21;
	float b = 3.6;
	void** parameters = {"Joaquin", &a, &b};
	char * foundation = "Hola me llamo %s, mi edad es %d y mi pito mide %f";
	printf(foundation, parameters);

	return 0;
}