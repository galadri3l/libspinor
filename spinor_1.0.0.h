typedef struct spinor_custom {
	float spinor_delay;
	short int *spinor_trigger;
	FILE *spinor_stream;
	void (*spinor_fun) (FILE *);
}spinor_t;

extern void *spinor(void *);
extern void init_spinor (spinor_t *,float,short *,FILE*,void (*) (FILE *)); 
extern void boo(FILE *);
extern void roll(FILE *);
extern void ceasor(FILE *);
extern void upper(FILE *);

