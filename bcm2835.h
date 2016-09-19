struct GPIO_REGISTERS
{
typedef enum
{
	redDisable  = 0x0,
	redOn       = 0x1
}red_status;

struct 
{
	red_status REN0     :1;
	red_status REN1     :1;
	red_status REN2     :1;
	red_status REN3     :1;
	red_status REN4     :1;
	red_status REN5     :1;
	red_status REN6     :1;
	red_status REN7     :1;
	red_status REN8     :1;
	red_status REN9     :1;
	red_status REN10    :1;
	red_status REN11    :1;
	red_status REN12    :1;
	red_status REN13    :1;
	red_status REN14    :1;
	red_status REN15    :1;
	red_status REN16    :1;
	red_status REN17    :1;
	red_status REN18    :1;
	red_status REN19    :1;
	red_status REN20	:1;
	red_status REN21     :1;
	red_status REN22     :1;
	red_status REN23     :1;
	red_status REN24     :1;
	red_status REN25     :1;
	red_status REN26     :1;
	red_status REN27     :1;
	red_status REN28     :1;
	red_status REN29     :1;
	red_status REN30     :1;
	red_status REN31     :1;
}   GPREN0;

struct 
{
	
	red_status REN32	:1;
	red_status REN33	:1;
	red_status REN34	:1;
	red_status REN35	:1;
	red_status REN36	:1;
	red_status REN37	:1;
	red_status REN38	:1;
	red_status REN39	:1;
	red_status REN40    :1;
	red_status REN41    :1;
	red_status REN42    :1;
	red_status REN43    :1;
	red_status REN44    :1;
	red_status REN45    :1;
	red_status REN46    :1;
	red_status REN47    :1;
	red_status REN48    :1;
	red_status REN49    :1;
	red_status REN50    :1;
	red_status REN51    :1;
	red_status REN52    :1;
	red_status REN53    :1;
	unsigned			:10;
}   GPREN1;
unsigned	:32;

typedef enum
{
	fedDisable  = 0x0,
	fedOn       = 0x1
} fed_status; 

struct 
{
	fed_status LEN0     :1;
	fed_status LEN1     :1;
	fed_status LEN2     :1;
	fed_status LEN3     :1;
	fed_status LEN4     :1;
	fed_status LEN5     :1;
	fed_status LEN6     :1;
	fed_status LEN7     :1;
	fed_status LEN8     :1;
	fed_status LEN9     :1;
	fed_status LEN10    :1;
	fed_status LEN11    :1;
	fed_status LEN12    :1;
	fed_status LEN13    :1;
	fed_status LEN14    :1;
	fed_status LEN15    :1;
	fed_status LEN16    :1;
	fed_status LEN17    :1;
	fed_status LEN18    :1;
	fed_status LEN19    :1;
	fed_status LEN20	:1;
	fed_status LEN21     :1;
	fed_status LEN22     :1;
	fed_status LEN23     :1;
	fed_status LEN24     :1;
	fed_status LEN25     :1;
	fed_status LEN26     :1;
	fed_status LEN27     :1;
	fed_status LEN28     :1;
	fed_status LEN29     :1;
	fed_status LEN30     :1;
	fed_status LEN31     :1;
}   GPLEN0;

struct 
{
	
	fed_status LEN32	:1;
	fed_status LEN33	:1;
	fed_status LEN34	:1;
	fed_status LEN35	:1;
	fed_status LEN36	:1;
	fed_status LEN37	:1;
	fed_status LEN38	:1;
	fed_status LEN39	:1;
	fed_status LEN40    :1;
	fed_status LEN41    :1;
	fed_status LEN42    :1;
	fed_status LEN43    :1;
	fed_status LEN44    :1;
	fed_status LEN45    :1;
	fed_status LEN46    :1;
	fed_status LEN47    :1;
	fed_status LEN48    :1;
	fed_status LEN49    :1;
	fed_status LEN50    :1;
	fed_status LEN51    :1;
	fed_status LEN52    :1;
	fed_status LEN53    :1;
	unsigned			:10;
}   GPLEN1;

unsigned	:32;

typedef enum
{
	hdDisable  = 0x0,
	hdOn       = 0x1
} hd_status; 

struct 
{
	hd_status HEN0     :1;
	hd_status HEN1     :1;
	hd_status HEN2     :1;
	hd_status HEN3     :1;
	hd_status HEN4     :1;
	hd_status HEN5     :1;
	hd_status HEN6     :1;
	hd_status HEN7     :1;
	hd_status HEN8     :1;
	hd_status HEN9     :1;
	hd_status HEN10    :1;
	hd_status HEN11    :1;
	hd_status HEN12    :1;
	hd_status HEN13    :1;
	hd_status HEN14    :1;
	hd_status HEN15    :1;
	hd_status HEN16    :1;
	hd_status HEN17    :1;
	hd_status HEN18    :1;
	hd_status HEN19    :1;
	hd_status HEN20		:1;
	hd_status HEN21     :1;
	hd_status HEN22     :1;
	hd_status HEN23     :1;
	hd_status HEN24     :1;
	hd_status HEN25     :1;
	hd_status HEN26     :1;
	hd_status HEN27     :1;
	hd_status HEN28     :1;
	hd_status HEN29     :1;
	hd_status HEN30     :1;
	hd_status HEN31     :1;
}   GPHEN0;

struct 
{
	
	hd_status HEN32	:1;
	hd_status HEN33	:1;
	hd_status HEN34	:1;
	hd_status HEN35	:1;
	hd_status HEN36	:1;
	hd_status HEN37	:1;
	hd_status HEN38	:1;
	hd_status HEN39	:1;
	hd_status HEN40    :1;
	hd_status HEN41    :1;
	hd_status HEN42    :1;
	hd_status HEN43    :1;
	hd_status HEN44    :1;
	hd_status HEN45    :1;
	hd_status HEN46    :1;
	hd_status HEN47    :1;
	hd_status HEN48    :1;
	hd_status HEN49    :1;
	hd_status HEN50    :1;
	hd_status HEN51    :1;
	hd_status HEN52    :1;
	hd_status HEN53    :1;
	unsigned			:10;
}   GPHEN1;

unsigned	:32;

typedef enum
{
	ldDisable  = 0x0,
	ldOn       = 0x1
} ld_status; 

struct 
{
	ld_status LEN0     :1;
	ld_status LEN1     :1;
	ld_status LEN2     :1;
	ld_status LEN3     :1;
	ld_status LEN4     :1;
	ld_status LEN5     :1;
	ld_status LEN6     :1;
	ld_status LEN7     :1;
	ld_status LEN8     :1;
	ld_status LEN9     :1;
	ld_status LEN10    :1;
	ld_status LEN11    :1;
	ld_status LEN12    :1;
	ld_status LEN13    :1;
	ld_status LEN14    :1;
	ld_status LEN15    :1;
	ld_status LEN16    :1;
	ld_status LEN17    :1;
	ld_status LEN18    :1;
	ld_status LEN19    :1;
	ld_status LEN20		:1;
	ld_status LEN21     :1;
	ld_status LEN22     :1;
	ld_status LEN23     :1;
	ld_status LEN24     :1;
	ld_status LEN25     :1;
	ld_status LEN26     :1;
	ld_status LEN27     :1;
	ld_status LEN28     :1;
	ld_status LEN29     :1;
	ld_status LEN30     :1;
	ld_status LEN31     :1;
}   GPLEN0;

struct 
{
	
	ld_status LEN32	:1;
	ld_status LEN33	:1;
	ld_status LEN34	:1;
	ld_status LEN35	:1;
	ld_status LEN36	:1;
	ld_status LEN37	:1;
	ld_status LEN38	:1;
	ld_status LEN39	:1;
	ld_status LEN40    :1;
	ld_status LEN41    :1;
	ld_status LEN42    :1;
	ld_status LEN43    :1;
	ld_status LEN44    :1;
	ld_status LEN45    :1;
	ld_status LEN46    :1;
	ld_status LEN47    :1;
	ld_status LEN48    :1;
	ld_status LEN49    :1;
	ld_status LEN50    :1;
	ld_status LEN51    :1;
	ld_status LEN52    :1;
	ld_status LEN53    :1;
	unsigned			:10;
}   GPLEN1;

unsigned	:32;

typedef enum
{
	aredDisable  = 0x0,
	aredOn       = 0x1
} ared_status; 

struct 
{
	ared_status AREN0     :1;
	ared_status AREN1     :1;
	ared_status AREN2     :1;
	ared_status AREN3     :1;
	ared_status AREN4     :1;
	ared_status AREN5     :1;
	ared_status AREN6     :1;
	ared_status AREN7     :1;
	ared_status AREN8     :1;
	ared_status AREN9     :1;
	ared_status AREN10    :1;
	ared_status AREN11    :1;
	ared_status AREN12    :1;
	ared_status AREN13    :1;
	ared_status AREN14    :1;
	ared_status AREN15    :1;
	ared_status AREN16    :1;
	ared_status AREN17    :1;
	ared_status AREN18    :1;
	ared_status AREN19    :1;
	ared_status AREN20	:1;
	ared_status AREN21     :1;
	ared_status AREN22     :1;
	ared_status AREN23     :1;
	ared_status AREN24     :1;
	ared_status AREN25     :1;
	ared_status AREN26     :1;
	ared_status AREN27     :1;
	ared_status AREN28     :1;
	ared_status AREN29     :1;
	ared_status AREN30     :1;
	ared_status AREN31     :1;
}   GPAREN0;

struct 
{
	
	ared_status AREN32	:1;
	ared_status AREN33	:1;
	ared_status AREN34	:1;
	ared_status AREN35	:1;
	ared_status AREN36	:1;
	ared_status AREN37	:1;
	ared_status AREN38	:1;
	ared_status AREN39	:1;
	ared_status AREN40    :1;
	ared_status AREN41    :1;
	ared_status AREN42    :1;
	ared_status AREN43    :1;
	ared_status AREN44    :1;
	ared_status AREN45    :1;
	ared_status AREN46    :1;
	ared_status AREN47    :1;
	ared_status AREN48    :1;
	ared_status AREN49    :1;
	ared_status AREN50    :1;
	ared_status AREN51    :1;
	ared_status AREN52    :1;
	ared_status AREN53    :1;
	unsigned			:10;
}   GPAREN1;

unsigned	:32;

typedef enum
{
	afedDisable  = 0x0,
	afedOn       = 0x1
} afed_status; 

struct 
{
	afed_status AFEN0     :1;
	afed_status AFEN1     :1;
	afed_status AFEN2     :1;
	afed_status AFEN3     :1;
	afed_status AFEN4     :1;
	afed_status AFEN5     :1;
	afed_status AFEN6     :1;
	afed_status AFEN7     :1;
	afed_status AFEN8     :1;
	afed_status AFEN9     :1;
	afed_status AFEN10    :1;
	afed_status AFEN11    :1;
	afed_status AFEN12    :1;
	afed_status AFEN13    :1;
	afed_status AFEN14    :1;
	afed_status AFEN15    :1;
	afed_status AFEN16    :1;
	afed_status AFEN17    :1;
	afed_status AFEN18    :1;
	afed_status AFEN19    :1;
	afed_status AFEN20		:1;
	afed_status AFEN21     :1;
	afed_status AFEN22     :1;
	afed_status AFEN23     :1;
	afed_status AFEN24     :1;
	afed_status AFEN25     :1;
	afed_status AFEN26     :1;
	afed_status AFEN27     :1;
	afed_status AFEN28     :1;
	afed_status AFEN29     :1;
	afed_status AFEN30     :1;
	afed_status AFEN31     :1;
}   GPAFEN0;

struct 
{
	
	afed_status AFEN32	:1;
	afed_status AFEN33	:1;
	afed_status AFEN34	:1;
	afed_status AFEN35	:1;
	afed_status AFEN36	:1;
	afed_status AFEN37	:1;
	afed_status AFEN38	:1;
	afed_status AFEN39	:1;
	afed_status AFEN40    :1;
	afed_status AFEN41    :1;
	afed_status AFEN42    :1;
	afed_status AFEN43    :1;
	afed_status AFEN44    :1;
	afed_status AFEN45    :1;
	afed_status AFEN46    :1;
	afed_status AFEN47    :1;
	afed_status AFEN48    :1;
	afed_status AFEN49    :1;
	afed_status AFEN50    :1;
	afed_status AFEN51    :1;
	afed_status AFEN52    :1;
	afed_status AFEN53    :1;
	unsigned			:10;
}   GPAFEN1;

unsigned	:32;

typedef enum
{
	pudOff 				=0x0, // disable pull-up/down
	pudEnablePullDown 	=0x1, // Enable Pull Down control
	pudEnablePullUp		=0x2, // Enable Pull Up control 
	pudReserved			=0x3  // Reserved
} pin_pull_updown;

struct //GPIO Pull-up/down Register (GPPUD) 
{
	pin_pull_updown	PUD	:2;
	unsigned			:30;
}	GPPUD;

typedef enum
{
	clockNoEffect 		 = 0x0,
	clockAssertOnLine    = 0x1
} pud_clock; 

struct 
{
	pud_clock PUDCLK0     :1;
	pud_clock PUDCLK1     :1;
	pud_clock PUDCLK2     :1;
	pud_clock PUDCLK3     :1;
	pud_clock PUDCLK4     :1;
	pud_clock PUDCLK5     :1;
	pud_clock PUDCLK6     :1;
	pud_clock PUDCLK7     :1;
	pud_clock PUDCLK8     :1;
	pud_clock PUDCLK9     :1;
	pud_clock PUDCLK10    :1;
	pud_clock PUDCLK11    :1;
	pud_clock PUDCLK12    :1;
	pud_clock PUDCLK13    :1;
	pud_clock PUDCLK14    :1;
	pud_clock PUDCLK15    :1;
	pud_clock PUDCLK16    :1;
	pud_clock PUDCLK17    :1;
	pud_clock PUDCLK18    :1;
	pud_clock PUDCLK19    :1;
	pud_clock PUDCLK20		:1;
	pud_clock PUDCLK21     :1;
	pud_clock PUDCLK22     :1;
	pud_clock PUDCLK23     :1;
	pud_clock PUDCLK24     :1;
	pud_clock PUDCLK25     :1;
	pud_clock PUDCLK26     :1;
	pud_clock PUDCLK27     :1;
	pud_clock PUDCLK28     :1;
	pud_clock PUDCLK29     :1;
	pud_clock PUDCLK30     :1;
	pud_clock PUDCLK31     :1;
}   GPPUDCLK0;

struct 
{
	
	pud_clock PUDCLK32	:1;
	pud_clock PUDCLK33	:1;
	pud_clock PUDCLK34	:1;
	pud_clock PUDCLK35	:1;
	pud_clock PUDCLK36	:1;
	pud_clock PUDCLK37	:1;
	pud_clock PUDCLK38	:1;
	pud_clock PUDCLK39	:1;
	pud_clock PUDCLK40    :1;
	pud_clock PUDCLK41    :1;
	pud_clock PUDCLK42    :1;
	pud_clock PUDCLK43    :1;
	pud_clock PUDCLK44    :1;
	pud_clock PUDCLK45    :1;
	pud_clock PUDCLK46    :1;
	pud_clock PUDCLK47    :1;
	pud_clock PUDCLK48    :1;
	pud_clock PUDCLK49    :1;
	pud_clock PUDCLK50    :1;
	pud_clock PUDCLK51    :1;
	pud_clock PUDCLK52    :1;
	pud_clock PUDCLK53    :1;
	unsigned			:10;
}   GPPUDCLK1;

unsigned	:32;
unsigned	:32;
unsigned	:32;
unsigned	:32;

unsigned	Test	:4;
};