//Sâmia Feitosa Silva e Kayky Martins de Lima
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* IMAS memory size (4K X 16) */
#define IMAS_MEM_SIZE 		(4096)

/* IMAS instructions */
#define IMAS_HALT			(0x0) 	/* HALT 			| Stops processor */
#define IMAS_LOAD_M			(0x1)	/* LOAD M(X) 		| AC <= MEMORY[X] */
#define IMAS_LOAD_MQ		(0x2)	/* LOAD MQ 			| AC <= MQ */
#define IMAS_LOAD_MQ_M		(0x3)	/* LOAD MQ, M(X)	| MQ <= MEMORY[X] */
#define IMAS_STOR_M			(0x4)	/* STOR M(X) 		| MEMORY[X] <= AC */
#define IMAS_STA_M			(0x5) 	/* STA M(X) 		| MEMORY[X](11:0) = AC */
#define IMAS_ADD_M			(0x6)	/* ADD M(X) 		| AC <= AC + MEMORY[X] */
#define IMAS_SUB_M			(0x7)	/* SUB M(X) 		| AC <= AC - MEMORY[X] */
#define IMAS_MUL_M			(0x8)	/* MUL M(X) 		| AC(31:16):MQ(15:0) <= MQ * MEMORY[X] */
#define IMAS_DIV_M			(0x9)	/* DIV M(X) 		| MQ <= AC / MEMORY[X], AC <= AC % MEMORY[X] */
#define IMAS_JMP_M			(0xA)	/* JMP M(X) 		| PC = X */
#define IMAS_JZ_M			(0xB) 	/* JZ M(X) 			| PC = (AC == 0) ? X : PC */
#define IMAS_JNZ_M			(0xC) 	/* JNZ M(X) 		| PC = (AC != 0) ? X : PC */
#define IMAS_JPOS_M			(0xD) 	/* JPOS M(X) 		| PC = (AC >= 0) ? X : PC */
#define IMAS_IN				(0xE) 	/* IN 				| AC <= IO */
#define IMAS_OUT			(0xF) 	/* OUT 				| IO <= AC */

/* IMAS registers and memory definitions */
typedef struct imas_t {
	/* UC */
	uint16_t pc;	/* Program Counter */
	uint16_t mar;	/* Memory Address Register */
	uint16_t ibr;	/* Instruction Buffer Register */
	uint16_t ir;	/* Instruction Register */

	/* ULA */
	int16_t mbr;	/* Memory Buffer Register */
	int16_t ac;		/* Accumulator */
	int16_t mq;		/* Multiplier Quocient */

	/* MEMORY */
	uint16_t memory[IMAS_MEM_SIZE];
} imas_t;

/* Executes a read from memory */
void memory_read(imas_t *imas) {
	// TODO ------------------
	imas->mbr = imas->memory[imas->mar];
}

/* Executes a write into memory */
 void memory_write(imas_t *imas, bool modify_address) {
	if(modify_address) {
		// TODO: Write only operand address field -------------
		//4bits opcode | 12bits endereço
		uint16_t og_val = imas->memory[imas->mar];
		uint16_t adds_val = (imas->ac) & 0x0FFF;
		uint16_t sec_val = (og_val & 0xF000) | adds_val;
		imas->memory[imas->mar] = sec_val;
	}
	else {
		// TODO -------------------
		imas->memory[imas->mar] = imas->mbr;
	}
}

/* Reads an integer from user */
void io_read(imas_t *imas) {
	//printf("IN => "); 
	// TODO: scanf("%hd", &<?>); --------
	scanf("%hd", &imas->ac);
}

/* Outputs an integer to user */
void io_write(imas_t *imas) {
	// TODO: printf("OUT => %hd\n", <?>);-------
	printf("%hd\n", imas->ac); 
}

int main(int argc, char *argv[]) {
    int x = 0;
    scanf("%d", &x);
	/* Set breakpoints */
	bool breakpoints[IMAS_MEM_SIZE] = {false};
	for(int i = 0; i < x; i++) {
		int address = 0;
		scanf("%d", &address);
		breakpoints[address] = true;
	}
	
	/* Initiate IMAS registers as zero */
	imas_t imas = {0};

	/* Zero IMAS memory */
	memset(&imas.memory, 0x0000, IMAS_MEM_SIZE);

	/* Fill IMAS memory */
        uint16_t address, buffer;
    while(scanf("%hX %hX%*[^\n]", &address, &buffer) == 2) {
		if(address == 0 && buffer == 0) break;
		imas.memory[address] = buffer;
    }

	/* Processor running */
	bool imas_halt = false;
	do {
		/* PC before modifications */
		uint16_t original_pc = imas.pc;

		/* Fetch subcycle */
		// TODO: Fetch instruction from memory (like in IAS)-----
		imas.mar = imas.pc;		//pc -> mar
		memory_read(&imas);		//le o mar
		imas.pc++;				//incrementa pc
		imas.ibr = imas.mbr;	//pega a instrucao


		/* Decode subcycle */
		// TODO: Put instruction fields in registers-----
		imas.ir = (imas.ibr >> 12) & 0x000F; 	//opcode
		imas.mar = imas.ibr & 0x0FFF;			//endereco

		/* Execute subcycle */
		switch(imas.ir) {
		case IMAS_HALT:
			// TODO-------------------
			imas_halt = true;
			break;
		case IMAS_LOAD_M:
			// TODO ------------------
			memory_read(&imas);
			imas.ac = imas.mbr;
			break;
		case IMAS_LOAD_MQ:
			// TODO ------------------
			imas.ac = imas.mq;
			break;
		case IMAS_LOAD_MQ_M:
			// TODO ------------------
			memory_read(&imas);
			imas.mq = imas.mbr;
			break;
		case IMAS_STOR_M:
			// TODO-------------------
			imas.mbr = imas.ac;
			memory_write(&imas, false);
			break;
		case IMAS_STA_M:
			// TODO-------------------
			imas.mbr = imas.ac;
			memory_write(&imas, true);
			break;
		case IMAS_ADD_M:
			// TODO-------------------
			memory_read(&imas);
			imas.ac = imas.ac + imas.mbr;
			break;
		case IMAS_SUB_M:
			// TODO-------------------
			memory_read(&imas);
			imas.ac = imas.ac - imas.mbr;
			break;
		case IMAS_MUL_M:
			// TODO-------------------
			memory_read(&imas);
			//usand 2 registradores para a multiplicacao
			uint32_t res = (int32_t)imas.mq * (int32_t)imas.mbr;  //!!!
			imas.ac = (res >> 16) & 0xFFFF;
			imas.mq = res & 0xFFFF;
			break;
		case IMAS_DIV_M:
			// TODO-------------------
			memory_read(&imas);
			if(imas.mbr != 0){
				imas.mq = imas.ac / imas.mbr;
				imas.ac = imas.ac % imas.mbr;
			}
			break;
		case IMAS_JMP_M:
			// TODO-------------------
			imas.pc = imas.mar;
			break;
		case IMAS_JZ_M:
			// TODO-------------------
			if(imas.ac == 0) imas.pc = imas.mar;
			break;
		case IMAS_JNZ_M:
			// TODO-------------------
			if(imas.ac != 0) imas.pc = imas.mar;
			break;
		case IMAS_JPOS_M:
			// TODO-------------------
			if(imas.ac >= 0) imas.pc = imas.mar;
			break;
		case IMAS_IN:
			// TODO-------------------
			io_read(&imas);
			break;
		case IMAS_OUT:
			// TODO-------------------
			io_write(&imas);
			break;
		default:
			printf("Invalid instruction %04X!\n", imas.ibr);
			imas_halt = true;
			break;
		}

		/* Breakpoint subcycle */
		if(breakpoints[original_pc]) {
			printf("<== IMAS Registers ==>\n");
			printf("PC = 0x%04hX\n", original_pc);
			printf("PC+ = 0x%04hX\n", imas.pc);
			printf("MAR = 0x%04hX\n", imas.mar);
			printf("IBR = 0x%04hX\n", imas.ibr);
			printf("IR = 0x%04hX\n", imas.ir);
			printf("MBR = 0x%04hX\n", imas.mbr);
			printf("AC = 0x%04hX\n", imas.ac);
			printf("MQ = 0x%04hX\n", imas.mq);
		}

	} while(!imas_halt);

	return 0;
}
	
