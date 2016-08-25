#include<pthread.h>

typedef struct spinor_custom {
	float spinor_delay;
	short int *spinor_trigger;
	FILE *spinor_stream;
	void (*spinor_fun) (FILE *);
}spinor_t;

typedef struct spinor_api {
	short api_trg;
	pthread_t api_thr;
	spinor_t api_spr;
	void * api_ret;
}spinor_cr;

#define SPINOR_INIT_ALL(st,delay,stream,fun) \
	init_trigger(&st); \
	init_spinor(&st.api_spr,delay,&st.api_trg,stream,fun)		

#define SPINOR_CREATE(st,delay,stream,fun) \
	SPINOR_INIT_ALL(st,delay,stream,fun); \
	pthread_create(&st.api_thr,NULL,spinor,&st.api_spr)

#define SPINOR_DEMO(x) \
	SPINOR_CREATE(x,0,stderr,roll)

#define SPINOR_STOP(x) \
	sig_trigger(&x); \
	pthread_join(x.api_thr,&x.api_ret)

#define SPINOR_SIG(x) \
	sig_trigger(&x)

#define SPINOR_GRACE(x) \
	pthread_join(x.api_thr,&x.api_ret)
//void *spinor_return;
void *spinor(void *);
void init_spinor (spinor_t *,float,short *,FILE*,void (*) (FILE *)); 
void boo(FILE *);
void roll(FILE *);
void ceasor(FILE *);
void upper(FILE *);
void rebound(FILE *);
short get_trigger(spinor_cr*);
void init_trigger(spinor_cr*);
void sig_trigger(spinor_cr*);
