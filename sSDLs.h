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
void setPixel(SDL_Surface *surfaces,int x,int y,int b,int g,int r){
	char *pixels=(char *) surfaces->pixels;
	if(x<surfaces->w-1 && y<surfaces->h-1 && y>-1 && x>-1){
		pixels[y*surfaces->w+x]=(char)(b/85)|((g/85)<<3)|((r/85)<<5);
	}

}
void lineR(SDL_Surface *surfaces, int x,int y,int x2,int y2,char bc,char g,char r){
long l1=0,l2=0,l3=0,l4=0,l5=0;
	int i4=0;
	int xx=x;
	int yy=y;
	int xxx=x2;
	int yyy=y2;
	int c=0;
	int c2=0;
	if (xx>xxx){
		i4=xxx;
		xxx=xx;
		xx=i4;
	}
	if (yy>yyy){
		i4=yyy;
		yyy=yy;
		yy=i4;
	}

	int i1=xxx-xx;
	int i2=yyy-yy;
	int i3;
	int i5;
	int i6;
	int i8;
	int b=0;
	int ty=0;
	if (i1>i2){
		l1=(long)i1;
		l2=(long)i2;
		if(l1==0){
			l1=1;
		}
		l4=(l2*10000/l1);
		l3=0;
		i6=0;
		c=0;
		c2=0;
		for(i5=0;i5<i1+1;i5++){
			l5=l3/10000;
			i3=(int)l5;
			setPixel(surfaces,xx+i5,y+(i3),bc,g,r);
			l3=l3+l4;
		}
	}else{
		l1=(long)i1;
		l2=(long)i2;
		if(l2==0){
			l2=1;
		}
		l4=(l1*10000/l2);
		l3=0;
		i6=0;
		c=0;
		c2=0;
		for(i5=0;i5<i2+1;i5++){
		l5=l3/10000;
		i3=(int)l5;
		setPixel(surfaces,xx+i3,y+(i5),bc,g,r);
		l3=l3+l4;
	
		} 
	}
}

void lineL(SDL_Surface *surfaces,int x,int y,int x2,int y2,char bc,char g,char r){
	long l1=0,l2=0,l3=0,l4=0,l5=0;
	int i4=0;
	int xx=x;
	int yy=y;
	int xxx=x2;
	int yyy=y2;
	int c=0;
	int c2=0;
	if (xx>xxx){
		i4=xxx;
		xxx=xx;
		xx=i4;
	}
	if (yy<yyy){
		i4=yyy;
		yyy=yy;
		yy=i4;
	}

	int i1=xxx-xx;
	int i2=yy-yyy;
	int i3;
	int i5;
	int i6;
	int i8;
	int b=0;
	int ty=0;
	if (i1>i2){
		l1=(long)i1;
		l2=(long)i2;
		if(l1==0){
			l1=1;
		}
		
		l4=(l2*10000/l1);
		l3=0;
		i6=0;
		c=0;
		c2=0;
		for(i5=0;i5<i1+1;i5++){
			l5=l3/10000;
			i3=(int)l5;
			setPixel(surfaces,xx+i5,y-(i3),bc,g,r);
			l3=l3+l4;
		}
	}else{
		l1=(long)i1;
		l2=(long)i2;
		if(l2==0){
			l2=1;
		}
		l4=(l1*10000/l2);
		l3=0;
		i6=0;
		c=0;
		c2=0;
		for(i5=0;i5<i2+1;i5++){
			l5=l3/10000;
			i3=(int)l5;
			setPixel(surfaces,xx+i3,yy-i5,bc,g,r);
			l3=l3+l4;
		}
	} 
}

void line(SDL_Surface *surfaces,int x,int y,int x2,int y2,char b,char g,char r){
	int i=-1;
	if(x>x2 && y<y2)i=5;
	if(x>x2 && y>y2)i=4;
	if(x<x2 && y<y2)i=3;
	if(x<x2 && y>y2)i=2;
	if(y==y2 && x2>x)i=0;
	if(x==x2 && y2>y)i=1;
	if(y==y2 && x>x2)i=7;
	if(x==x2 && y>y2)i=6;
	if (i==0)hline(surfaces,x,y,x2,b,g,r);
	if (i==1)vline(surfaces,x,y,y2,b,g,r);
	if (i==2)lineL(surfaces,x,y,x2,y2,b,g,r);
	if (i==3)lineR(surfaces,x,y,x2,y2,b,g,r);
	if (i==4)lineR(surfaces,x2,y2,x,y,b,g,r);
	if (i==5)lineL(surfaces,x2,y2,x,y,b,g,r);
	if (i==7)hline(surfaces,x2,y,x,b,g,r);
	if (i==6)vline(surfaces,x,y2,y,b,g,r);

}
