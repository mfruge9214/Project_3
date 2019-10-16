

#include <stdint.h>
#include <stdio.h>

#define BIT0_MASK	0x1
#define BIT1_MASK	0x2
#define BIT2_MASK	0x4
#define BIT3_MASK	0x8
#define BIT4_MASK	0x10
#define BIT5_MASK	0x20
#define BIT6_MASK	0x40
#define BIT7_MASK	0x80


void createPattern(size_t len, uint8_t seed, uint8_t* genList);
