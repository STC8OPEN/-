#ifndef __CDS_H
#define __CDS_H

#include "stc8h.h" 

sbit CDS= P1^7;


void CDS_INT(void);
u8 CDS_GET(void);

#endif  