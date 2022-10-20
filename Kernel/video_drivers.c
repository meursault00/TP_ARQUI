#include <video_driver.h>
#include <fonts.h>
//pr
typedef struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels resolution X
	uint16_t height;			// height in pixels resolution Y
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;
 
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
 
	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed)) VbeModeInfo;

 VbeModeInfo *info= (VbeModeInfo*) 0x0000000000005C00; // en sysvar.asm linea 21 se carga el struct en el bootloader


void put_pixel(uint32_t x , uint32_t y, uint32_t color){
	uint32_t pixel_offset =(y) * (info->pitch) + ((x) * ((info->bpp)/8)) ;
	uint8_t* screen=(uint8_t*) info->framebuffer;

	screen[pixel_offset]=(uint8_t)color & 0xFF; // B 
	screen[pixel_offset+1]=(uint8_t)((color>>8) & 0xFF); // G
	screen[pixel_offset+2]=(uint8_t)((color>>16) & 0xFF); // R

}
void put_square(uint32_t x , uint32_t y,uint32_t tam, uint32_t color){
	for(int i=0;i<tam;i++)
		for(int j =0;j<tam;j++)
			put_pixel(x+i,y+j,color);
}

// entre "A" 65 - 33


/* parametros: 
	letra 
	x -> posicion horizontal inicial
	y -> posicion vertical inicial
	tamaño de la letra
	color
*/
int put_letter( char letter,  uint32_t x , uint32_t y,uint32_t tam, uint32_t color){
	int a = x;
	int start = letter -33;
	if ( letter == ' ' ){
		return a + tam*8;
	}
	for ( int i = 0; i < 33; i++ ){
		if ( i % 2 == 0 && i != 0){
			y+= tam;
			a = x;
		}
		font[i]&(char)0x01 ? put_square(a,y,tam,color) : 0 ;
		a+=tam;
        ((uint8_t)font[i+ (start*32)]&(uint8_t)0x02)>>1? put_square(a,y,tam,color) : 0 ;
		a+=tam;
        ((uint8_t)font[i+ (start*32)]&(uint8_t)0x04)>>2? put_square(a,y,tam,color) : 0 ;
		a+=tam;
        ((uint8_t)font[i+ (start*32)]&(uint8_t)0x08)>>3? put_square(a,y,tam,color) : 0 ;
		a+=tam;
        ((uint8_t)font[i+ (start*32)]&(uint8_t)0x10)>>4? put_square(a,y,tam,color) : 0 ;
		a+=tam;
        ((uint8_t)font[i+ (start*32)]&(uint8_t)0x20)>>5? put_square(a,y,tam,color) : 0 ;
		a+=tam;
        ((uint8_t)font[i+ (start*32)]&(uint8_t)0x40)>>6? put_square(a,y,tam,color) : 0 ;
		a+=tam;
		((uint8_t)font[i+ (start*32)]&(uint8_t)0x80)>>7 ? put_square(a,y,tam,color) : 0 ; 
	}
	return a+tam; //posicion horizontal final 
}

void put_word( char * string, uint32_t x , uint32_t y,uint32_t tam, uint32_t color){
	int accum;
	for ( int i = 0; string[i] != 0; i++ ){
		accum=  i*tam*8;
		put_letter(string[i], x + accum, y, tam, color);

	}

}

