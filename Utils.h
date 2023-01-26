#ifndef UTILS_H_
#define UTILS_H_

/* Set a certain bit in any register */
#define SET_BIT(REG, BIT)			( REG |= (1<<BIT)  )

 /* Clear a certain bit in any register */
#define CLEAR_BIT(REG, BIT)			( REG &= ~(1<<BIT)  )

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG, BIT)		( REG ^= (1<<BIT)  )

/* Return the value of a specific bit */
#define READ_BIT(REG, BIT)			( (REG >> BIT) & 1 )

/**/
#define WRITE_BIT(REG, BIT, VAL)	( CLEAR_BIT( (REG), (BIT) ) | (VAL << BIT) )

/* Rotate right the register value with specific number of rotates */
#define ROR(REG, NUM)           	( REG = (REG >> NUM) | (REG << (sizeof(REG)*8) - NUM) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG, NUM)				( REG = (REG << NUM) | (REG >> (sizeof(REG)*8) - NUM) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG, BIT)		( (REG >> BIT) & 1 )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG, BIT)		( !((REG >> BIT) & 1) )

#endif /* UTILS_H_ */
