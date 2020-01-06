#include "datapath.hpp"
extern pc_type pc;
int error;
r_type alu(opcode_type opcode, func7_type func7, func3_type func3, r_type op1, r_type op2)
{
	//printf("executing in alu..");
	r_type rd_val;
	error=0;
	switch(opcode){
		case OP_AL_R: //R type istruction
			switch(func7){
				 case FUNC7_0:
					switch(func3){
						 case ADD: rd_val = op1 + op2; /*printf("ADD\n")*/;break;
						 case SLL: rd_val = op1 << op2;/*printf("SLL\n");*/break;
						 case SLT: if (op1 < op2) rd_val = 1; else rd_val=0;/*printf("SLT\n");*/break;
						 case SLTU: if ((pc_type)op1 < (pc_type)op2) rd_val = 1; else rd_val=0;/*printf("SLTU\n");*/break;
						 case XOR: rd_val = op1 ^ op2;/*printf("XOR\n");*/break;
						 case SRL: rd_val = (pc_type)op1 >> op2;/*printf("SRL\n");*/break;
						 case OR: rd_val = op1 | op2;/*printf("OR\n");*/break;
						 case AND: rd_val = op1 & op2;/*printf("AND\n");*/break;
						 } break;
				 case FUNC7_I_E:
					switch(func3){
						 case SUB: rd_val = op1 - op2; /*printf("SUB\n");*/break;
						 case SRA: rd_val = op1 >> op2;/*printf("SRA\n");*/break;
						 default: error=1;
						 } break;
				 default: error=1;;
				} break;
		case AUIPC: rd_val=op1+op2; pc=rd_val; break;
		case OP_AL_I://I type instruction
			switch(func3){
				case ADD: rd_val = op1 + op2; /*printf("ADDI\n");*/break; //ADDI
				case SLL: op2= op2 & R_MASK; rd_val = op1 << op2;/*printf("SLLI\n");*/break; //SLLI
				case SLT: if (op1 < op2) rd_val = 1; else rd_val=0;/*printf("SLTI\n");*/break; //SLTI
				case SLTU: if ((pc_type)op1 < (pc_type)op2) rd_val = 1; else rd_val=0;/*printf("SLTIU\n");*/break; //SLTIU
				case XOR: rd_val = op1 ^ op2;/*printf("XORI\n");*/break; //XORI
				case OR: rd_val = op1 | op2;/*printf("ORI\n");*/break;  //ORI
				case AND: rd_val = op1 & op2;/*printf("ANDI\n");*/break; //ANDI
				case SRL:
					switch(func7) {
						case FUNC7_0:op2= (rf_pntr_type)op2 & R_MASK;rd_val = (ap_uint<32>)op1 >> op2;/*printf("SRLI\n");*/break; //SRLI
						case FUNC7_I_E:op2= (rf_pntr_type)op2 & R_MASK;rd_val = op1 >> op2;/*printf("SRAI\n");*/break; //SRAI
						default: error=1;
					}break;
				} break;

		default: error=1;
	}

	return rd_val;
}

















