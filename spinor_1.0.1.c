#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "spinor.h"

short get_trigger(spinor_cr *sp)
{
	return sp->api_trg;
}
void init_trigger(spinor_cr *sp)
{
	sp->api_trg=0;
}
void sig_trigger(spinor_cr *sp)
{
	sp->api_trg=1;
}

void init_spinor 
(spinor_t *ini,float delay,short int *trig,FILE *stream,void (*ini_anim) (FILE *)) 
{
	if(ini_anim == NULL)
		ini->spinor_fun = boo;
	else
		ini->spinor_fun = ini_anim;	
	if(stream == NULL)
		ini->spinor_stream=stdout;
	else
		ini->spinor_stream=stream;

	if((int)delay <= 0 || (int)delay > 999)
		ini->spinor_delay=200;
	else
		ini->spinor_delay = delay;

	ini->spinor_trigger = trig;
}
void rev_cur(FILE *out,int back)
{
	int i;
	for(i=0;i<back;i++)
		fprintf(out,"\b");
	fflush(out);
}
void swap_char(char *a,char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}
void boo(FILE *out)
{
	static short i = 0;
	static _Bool remember = 0;
	char pat[]="ooooooooo";
	if(!remember)
		remember = 1;
	else
		rev_cur(out,strlen(pat));

	pat[i]='0';
	fprintf(out,"%s",pat);
	fflush(out);
	i = (i+1) % strlen(pat);
        	
}
void upper(FILE *out)
{
	static short i = 0;
	static _Bool remember = 0;
	char pat[]="please wait";
	if(!remember)
		remember = 1;
	else
		rev_cur(out,strlen(pat));
	if(!(pat[i]== ' '))
		pat[i]-=32;
	fprintf(out,"%s",pat);
	fflush(out);
	i = (i+1) % strlen(pat);
        	
}

void roll(FILE *out)
{
	static short i = 0;
	static _Bool remember = 0;
	char pat[]="-\\|/";
	if(!remember)
		remember = 1;
	else
		rev_cur(out,1);
	fprintf(out,"%c",pat[i]);
	fflush(out);
	i = (i+1) % strlen(pat);
}

void ceasor(FILE *out)
{
	static short i = 0;
	static _Bool remember = 0;
	char pat[]="...........";
	static char x = '\\',y = '/';
	if(!remember)
		remember = 1;
	else
		rev_cur(out,strlen(pat));
	if(i==0||i==strlen(pat)/2)
		swap_char(&x,&y);
	pat[i]=x;pat[strlen(pat)-1-i]=y;

	if(i==strlen(pat)/2)
		pat[i] = '|';

	fprintf(out,"%s",pat);
	fflush(out);
	i = (i+1) % strlen(pat);
}


void *spinor(void *sp_random) 
{
	struct timespec elp,rem;
	spinor_t sp_parse;
	sp_parse = *((spinor_t *) sp_random);
	float delay = sp_parse.spinor_delay;
	FILE *out = sp_parse.spinor_stream;
	void (*anim)(FILE *) = sp_parse.spinor_fun;

	elp.tv_sec=0;elp.tv_nsec=(long int)(1000000*delay);
	while(!*(sp_parse.spinor_trigger)) {
		if(out!=stdout)
			flockfile(out);
		flockfile(stdout);

		anim(out);

		funlockfile(stdout);
		if(out!=stdout)
			funlockfile(out);

		nanosleep(&elp,&rem);

	}
	fprintf(out,"\n");
	return NULL;
}

