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

void rebound(FILE *out)
{
	static short i = 1;
	char pat[] = "[------------]";
	static _Bool dir = 0;

	pat[i]='<';pat[i+1]='>';
	fprintf(out,"%s",pat);
	rev_cur(out,strlen(pat));
	fflush(out);

	dir==0 ? i++ : i--;
	if(i==1 || i == strlen(pat)-3)
		dir^=1;
}

void boo(FILE *out)
{
	static short i = 0;
	char pat[]="---------";

	pat[i]='>';
	fprintf(out,"%s",pat);
	rev_cur(out,strlen(pat));
	fflush(out);
	i = (i+1) % strlen(pat);
        	
}
void upper(FILE *out)
{
	static short i = 0;
	char pat[]="please wait";
	short size = strlen(pat);	
	
	if(pat[i] != ' ')
		pat[i]-=32;
	if(pat[(i+1)%size] != ' ')
		pat[(i+1)%size]-=32;
	if(pat[(i+2)%size] != ' ')
		pat[(i+2)%size]-=32;

	fprintf(out,"%s",pat);
	rev_cur(out,strlen(pat));
	fflush(out);
	i = (i+1) % strlen(pat);
        	
}

void roll(FILE *out)
{
	static short i = 0;
	char pat[]="-\\|/";
	fprintf(out,"%c",pat[i]);
	rev_cur(out,1);
	fflush(out);
	i = (i+1) % strlen(pat);
}

void ceasor(FILE *out)
{
	static short i = 0;
	char pat[]="...........";
	static char x = '\\',y = '/';
	
	if(i==0||i==strlen(pat)/2)
		swap_char(&x,&y);
	pat[i]=x;pat[strlen(pat)-1-i]=y;

	if(i==strlen(pat)/2)
		pat[i] = '|';

	fprintf(out,"%s",pat);
	rev_cur(out,strlen(pat));
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

