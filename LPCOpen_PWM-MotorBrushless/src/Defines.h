/*
 * Variables globales y puertos para controlar motores.
 *
 * PORT_Qa y PIN_Qa -> PWM
 * PORT_Qb y PIN_Qb -> Encendido digital
 */
//#include "board.h"
//#include "chip.h"
//DEFINICIONES PUERTOS SALIDAS ENTRADAS
//-----------------------------------------------------------------------------------------------
#define PORT_Q1		1
#define PORT_Q2		0		//1
#define PORT_Q3		1
#define PORT_Q4		1
#define PORT_Q5		1
#define PORT_Q0		0		//1
#define PIN_Q0		27		//24
#define PIN_Q1		26
#define PIN_Q2		28		//21
#define PIN_Q3		23
#define PIN_Q4		18
#define PIN_Q5		20
#define PULS1 		18
#define PULS2 		1
#define PULS_PORT 	0
#define PORT_Z1		1
#define PORT_Z2		1
#define PORT_Z3		1
#define PIN_Z1		19
#define PIN_Z2		22
#define PIN_Z3		25
#define REBOTE_ 	100000
#define SALIDA		1

//GLOBALES
//-----------------------------------------------------------------------------------------------
uint32_t Match_Cnt=0, Cycle=0, AntiRebo=REBOTE_,
PORT_Qa[3]={PORT_Q1,PORT_Q3,PORT_Q5},
PIN_Qa[6]={PIN_Q1,PIN_Q3,PIN_Q5},
PORT_Qb[6]={PORT_Q0,PORT_Q2,PORT_Q4},
PIN_Qb[6]={PIN_Q0,PIN_Q2,PIN_Q4},
PORT_Z[3]={PORT_Z1, PORT_Z2, PORT_Z3},
PIN_Z[3]={PIN_Z1, PIN_Z2, PIN_Z3};

volatile uint8_t CruceZero[3]={0,0,0}, CruceZero0[3]={0,0,0};

struct StartParams_s {		// params for startup seq.
	long duration; 			// duration of accel phase of startup, us
	long periodRange[2]; 	// commutation period range for startup, us
	float powerRange[2];  	// frac of full power over startup accel
} start= { 150,   {360, 60},   {10, 160} };	//Cantidad de pasos, período inicial y final, pwm inicial y final para startup 240,120
												//-----> 50*20microseg = 1mSeg
long StepPeriod;     			// step duration, us
uint16_t DutyCycle, DutyCycle0; 	// fraction of period hi pins are high

volatile int StepID=0;  		// commutation step counter, 0..5
long Count=0;  					// no full commutation cycles completed

//FUNCIONES
//-----------------------------------------------------------------------------------------------
void PWM1_IRQHandler(void);
void InitPWM(void);
void InitGPIO(void);
void Stop_and_Default(void);
void Start_Up_Brushless(void);
void NextPWM(void);
void Zero_Detect(void);
