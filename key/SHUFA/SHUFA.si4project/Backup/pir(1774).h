#ifndef __PIR_H
#define __PIR_H

#include "stc8h.h" 


sbit PIR_IO =P5^4;
void PIR_INT(void);
void PIR_data_get(void);

#endif  