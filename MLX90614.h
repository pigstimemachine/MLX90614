#ifndef _MLX90614_H
#define _MLX90614_H
#include "sys.h"
u8 ReadTemp(short* Tempdat);
void CALTEMP(u32 TEMP);
short _READ_Tempdata(void);
#endif
