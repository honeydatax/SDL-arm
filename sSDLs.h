#include <SDL/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FONTDATAMAX 2048
#define PI 3.1415927
//----------------------------------------------
void vlineA(char *address,int from,int into,int addss,int value){
		int var0=0;
		asm volatile("vlineasm:\n\t"
			"strb %[value],[%[address]]\n\t"
			"add %[address],%[address],%[addss]\n\t"	
			"add %[from],%[from],#1\n\t"
			"cmp %[from],%[into]\n\t"
			"bls vlineasm\n\t"
			"mov %[var0],%[value]\n\t"
		     	:[var0] "=r" (var0) 
		     	:[address] "r" (address) 
		     	,[from] "r" (from) 
		     	,[into] "r" (into)
		     	,[addss]"r" (addss)
		     	,[value] "r" (value)
			:"memory" , "cc");

}
//----------------------------------------------
void vline(	SDL_Surface *surfaces,int x,int y,int y2,int b,int g,int r){
	int ccolor;
	int var0;
	char *var1;
	int var2;
	int var3;
	int xx=x;
	int yy=y;
	int count1=1;
	int nexts1=1;
	char *ppixel;
	char *pixels=(char *) surfaces->pixels;
	if(xx>=surfaces->w)xx=surfaces->w-1;
	if(yy>=surfaces->h)yy=surfaces->h-1;
	count1=y2-yy;
	if (count1+yy>=surfaces->h)count1=surfaces->h-1-yy;
	if(xx<0)xx=0;
	if(yy<0)yy=0;
	ppixel=pixels+(yy*surfaces->w+xx);
	ccolor=(b/85)|((g/85)<<3)|((r/85)<<6);
	vlineA(ppixel,0,count1,surfaces->w,ccolor);
}
