#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <interrupts.h>
#include <sound_driver.h>
#include <video_driver.h>
#include <tron.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000; //punteros a user land
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	//char buffer[10];
/*
	videoPrintWord("[x64BareBones]");
	videoNewLine();

	videoPrintWord("CPU Vendor:");
	videoPrintWord(cpuVendor(buffer));
	videoNewLine();

	videoPrintWord("[Loading modules]");
	videoNewLine();
*/
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	
	loadModules(&endOfKernelBinary, moduleAddresses);
	/*
	videoPrintWord("[Done]");
	videoNewLine();
	videoNewLine();

	videoPrintWord("[Initializing kernel's binary]");
	videoNewLine();
 */
	clearBSS(&bss, &endOfKernel - &bss);
/*
	videoPrintWord("  text: 0x");
	videoPrintHexa((uint64_t)&text);
	videoNewLine();
	videoPrintWord("  rodata: 0x");
	videoPrintWord((uint64_t)&rodata);
	videoNewLine();
	videoPrintWord("  data: 0x");
	videoPrintHexa((uint64_t)&data);
	videoNewLine();
	videoPrintWord("  bss: 0x");
	videoPrintHexa((uint64_t)&bss);
	videoNewLine();
	*/
	load_idt();
/*
	videoPrintWord("[Done]");
	videoNewLine();
	videoNewLine();
	*/
	return getStackBase();
}

int main()
{	
	load_idt();
	soviet_anthem(); //hola
	((EntryPoint) sampleCodeModuleAddress)(); //nos vamos para user land amigos

	while (1);


	return 0;
}
