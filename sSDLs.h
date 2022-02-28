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
void hline(	SDL_Surface *surfaces,int x,int y,int x2,int b,int g,int r){
	int ccolor;
	char *ppixel;
	int xx=x;
	int yy=y;
	int count1=1;
	int nexts1=1;
	char *pixels=(char *) surfaces->pixels;
	if(xx<0)xx=0;
	if(yy<0)yy=0;
	if(xx>=surfaces->w)xx=surfaces->w-1;
	if(yy>=surfaces->h)yy=surfaces->h-1;
	count1=x2-xx;
	if (count1+xx>=surfaces->w)count1=surfaces->w-1-xx;
	if(xx<0)xx=0;
	if(yy<0)yy=0;
	ppixel=pixels+(yy*surfaces->w+xx);
	ccolor=(b/85)|((g/85)<<3)|((r/85)<<6);
	vlineA(ppixel,0,count1,1,ccolor);
}
void clears(SDL_Surface *surfaces,int b,int g,int r){
	int ccolor;
	char *ppixel;
	char *pixels=(char *) surfaces->pixels;
	ppixel=pixels+(0*surfaces->w+0);
	ccolor=(b/85)|((g/85)<<3)|((r/85)<<6);
	vlineA(ppixel,0,surfaces->h*surfaces->w,1,ccolor);
}
void boxA(char *address,int intoh,int intov,int addss,int value){
		int var0=0;
		asm volatile("boxasmxxx:\n\t"
			"mov r1,#0\n\t"
			"boxasm:\n\t"
			"mov r2,#0\n\t"
			"boxasmxx:\n\t"
				"strb %[value],[%[address]]\n\t"
				"add %[address],%[address],#1\n\t"	
				"add r2,r2,#1\n\t"
				"cmp r2,%[intoh]\n\t"
				"bls boxasmxx\n\t"
			"add %[address],%[address],%[addss]\n\t"	
			"add r1,r1,#1\n\t"
			"cmp r1,%[intov]\n\t"
			"bls boxasm\n\t"
			"mov %[var0],%[value]\n\t"
		     	:[var0] "=r" (var0) 
		     	:[address] "r" (address) 
		     	,[intoh] "r" (intoh) 
		     	,[intov] "r" (intov)
		     	,[addss]"r" (addss)
		     	,[value] "r" (value)
			:"r1","r2","memory" , "cc");
}
void box(SDL_Surface *surfaces,int x,int y,int x2,int y2,int b,int g,int r){
	int ccolor;
	int xx=x;
	int yy=y;
	int count1=1;
	int count2=1;
	int nexts1=1;
	int nexts2=1;
	char *ppixel;
	char *pixels=(char *) surfaces->pixels;
	if(xx<0)xx=0;
	if(yy<0)yy=0;
	if(xx>=surfaces->w)xx=surfaces->w-1;
	if(yy>=surfaces->h)yy=surfaces->h-1;
	count1=x2;
	count2=y2;
	ccolor=(b/85)|((g/85)<<3)|((r/85)<<6);
	if (count1+xx>=surfaces->w)count1=surfaces->w-1-xx;
	if (count2+yy>=surfaces->h)count2=surfaces->h-1-yy;
	ppixel=pixels+(yy*surfaces->w+xx);
	boxA(ppixel,count2,count1,surfaces->w-count1-1,ccolor);
}
