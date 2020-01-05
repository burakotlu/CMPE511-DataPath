#include <ap_int.h>
#include <stdio.h>

#define HLT  0xFFFFFFFF
#define XLEN 32
#define OPCODE_WIDTH 7
#define OPCODE_SHAMT 0
#define OPCODE_MASK 0b1111111

#define FUNC3_WIDTH 3
#define FUNC3_SHAMT 12
#define FUNC3_MASK 0b111

#define FUNC7_WIDTH 7
#define FUNC7_SHAMT 25
#define FUNC7_MASK 0b1111111
#define RF_PNTR_WIDTH 5
#define RD_SHAMT 7
#define RS1_SHAMT 15
#define RS2_SHAMT 20
#define R_MASK 0b11111
#define IMM_11_0_SHAMT 20
#define IMM_31_12_SHAMT 12
#define IMM_11_0_MASK 0b111111111111
#define IMM_31_12_MASK 0b11111111111111111111
//load store masks
#define BIT_MASK 0x1
#define BYTE_MASK 0xFF
#define HALF_MASK 0xFFFF

//definition of opcode types
#define OP_AL_R 0b0110011
#define OP_AL_I 0b0010011
#define OP_BR   0b1100011
#define AUIPC   0b0010111
#define LOAD    0b0000011
#define STORE   0b0100011
#define BRANCH  0b1100011
#define JAL	    0b1101111
#define JALR    0b1100111
//definition of load/store types
#define BYTE 0b000
#define HALF 0b001
#define WORD 0b010
#define UBYTE 0b100
#define UHALF 0b101
#define L     0b0
#define S     0b1
//definition of  instructions
#define ADD		0b000 //same for ADDI
#define SUB		0b000
#define SLL 	0b001 //same for SLLI
#define SLT 	0b010 //same for SLTI
#define SLTU 	0b011 //same for SLTIU
#define XOR 	0b100 //same for XORI
#define SRL 	0b101 //same for SRLI
#define SRA     0b101 //same for SRAI
#define OR 		0b110 //same for ORI
#define AND 	0b111 //same for ANDI
//definition of  branch  types
#define BEQ		0b000
#define BNE		0b001
#define BLT		0b100
#define BGE		0b101
#define BLTU	0b110
#define BGEU	0b111
//definition of possible func7 values
#define FUNC7_0 	0b0000000
#define FUNC7_I_E   0b0100000
//definition of offset lengths
#define IMM_11_0_LENGTH 12
#define IMM_31_12_LENGTH 20
//definition of types
typedef ap_uint<1>					lsu_type;
typedef ap_int<XLEN>				r_type;
typedef ap_uint<XLEN>				i_type ;
typedef ap_uint<RF_PNTR_WIDTH>		rf_pntr_type ;
typedef ap_uint<OPCODE_WIDTH>		opcode_type ;
typedef ap_uint<FUNC3_WIDTH>		func3_type ;
typedef ap_uint<FUNC7_WIDTH>		func7_type ;
typedef ap_int<IMM_11_0_LENGTH>		imm12_type;
typedef ap_int<IMM_31_12_LENGTH>	imm20_type;
typedef ap_uint<XLEN>				pc_type;
//typedef ap_int<XLEN>				mem_type;

int datapath(pc_type start_pc);
r_type alu(opcode_type opcode, func7_type func7, func3_type func3, r_type op1, r_type op2);
void decoder(i_type instruction);
void lsu(lsu_type op, func3_type width,rf_pntr_type des, rf_pntr_type src,imm12_type offset);

