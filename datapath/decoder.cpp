#include  "datapath.hpp"

//extern void lsu(lsu_type op, func3_type width,rf_pntr_type des, rf_pntr_type src,imm12_type offset);
//extern r_type alu(opcode_type opcode, func7_type func7, func3_type func3, r_type op1, r_type op2);

r_type rf[32];
//#pragma HLS array_partition variable=rf block factor=2
//#pragma HLS pipeline II=1
rf_pntr_type rs1,rs2,rd;
extern pc_type pc;
extern int error;
void decoder(i_type instruction){

	//printf("decoding..");
	opcode_type 	opc ;
	func3_type 		funct3 ;
	func7_type 		funct7 ;
	r_type 			op1,op2;
	imm20_type 		imm_31_12,off_J;
	imm12_type		imm_11_0,off_S,off_B;

	opc = (opcode_type)(instruction >> OPCODE_SHAMT) & OPCODE_MASK ;
	rd = (rf_pntr_type)(instruction >> RD_SHAMT) & R_MASK ;
	rs1 = (rf_pntr_type)(instruction >> RS1_SHAMT) & R_MASK ;
	rs2 = (rf_pntr_type)(instruction >> RS2_SHAMT) & R_MASK ;
	funct3 = (func3_type)(instruction >> FUNC3_SHAMT) & FUNC3_MASK ;
	funct7 = (func7_type)(instruction >> FUNC7_SHAMT) & FUNC7_MASK ;
	imm_11_0=(imm12_type) (instruction>>IMM_11_0_SHAMT) & IMM_11_0_MASK;
	imm_31_12=(imm20_type) (instruction>>IMM_31_12_SHAMT)& IMM_31_12_MASK;
	off_S=(imm12_type)(rd|(funct7<<5));
	lsu_type imm12=(instruction>>31)&BIT_MASK;
	lsu_type imm11=rd&BIT_MASK;
	lsu_type imm20=(instruction>>31)&BIT_MASK;
	lsu_type imm11_J=rs2&BIT_MASK;
	imm12_type imm10_5=((imm12_type)((func7_type)(funct7<<1)))<<3;
	imm20_type imm10_5_J=((imm20_type)((func7_type)(funct7<<1)))<<3;
	off_B=(imm12_type)((((imm12_type)imm12)<<11)|(((imm12_type)imm11)<<10)|(rd>>1)|imm10_5);
	off_J=(imm20_type)((((imm20_type)imm20)<<19)|(((imm20_type)rs1)<<14)|(((imm20_type)funct3)<<11)|(((imm20_type)imm11_J)<<10)|(imm10_5_J)|(rs2>>1));

	switch(opc){
			case OP_AL_R:	op1=rf[rs1];
							op2=rf[rs2];
							rf[rd]=alu(opc,funct7,funct3,op1,op2);
							//printf("R format instruction..");
							pc=pc+4;
							break;
			case OP_AL_I: 	op1=rf[rs1]; op2=(r_type)imm_11_0;
							rf[rd]=alu(opc,funct7,funct3,op1,op2);
							//printf("I format instruction..");
							pc=pc+4;
							break;
			case AUIPC:   	op1=(r_type)pc;
							op2=(r_type)imm_31_12;
							funct3=ADD;rf[rd]=alu(opc,funct7,funct3,op1,op2);
							//printf("AUIPC format instruction..");
							break;//We will use ADD of Datapath.
			case LOAD:	  	//printf("load instruction..");
							switch(funct3){
								case BYTE: /*printf("BYTE \n");*/lsu(L,BYTE,rd,rs1,imm_11_0);pc=pc+4;break;
								case HALF: /*printf("HALF \n");*/lsu(L,HALF,rd,rs1,imm_11_0);pc=pc+4;break;
								case WORD: /*printf("WORD \n");*/lsu(L,WORD,rd,rs1,imm_11_0);pc=pc+4;break;
								case UBYTE:/*printf("UBYTE \n");*/lsu(L,UBYTE,rd,rs1,imm_11_0);pc=pc+4;break;
								case UHALF:/*printf("UHALF \n");*/lsu(L,UHALF,rd,rs1,imm_11_0);pc=pc+4;break;
							}break;
			case STORE:	  	//printf("store instruction..");
							switch(funct3){
								case BYTE: /*printf("BYTE \n");*/lsu(S,BYTE,rs1,rs2,off_S);pc=pc+4;break;
								case HALF: /*printf("HALF \n");*/lsu(S,HALF,rs1,rs2,off_S);pc=pc+4;break;
								case WORD: /*printf("WORD \n");*/lsu(S,WORD,rs1,rs2,off_S);pc=pc+4;break;
							}break;
			case BRANCH:  	//printf("branch instruction..");
							switch(funct3){
								case BEQ:	//printf("type: BEQ \n");
											if(rf[rs1]==rf[rs2]) pc=pc+(r_type)off_B;
											else pc=pc+4;
											break;
								case BNE:	//printf("type: BNE \n");
											if(rf[rs1]!=rf[rs2]) pc=pc+(r_type)off_B;
											else pc=pc+4;
											break;
								case BLT:	//printf("type: BLT \n");
											if(rf[rs1]<rf[rs2]) pc=pc+(r_type)off_B;
											else pc=pc+4;
											break;
								case BGE:	//printf("type: BGE \n");
											if(rf[rs1]>=rf[rs2]) pc=pc+(r_type)off_B;
											else pc=pc+4;
											break;
								case BLTU:	//printf("type: BLTU \n");
											if((pc_type)rf[rs1]<(pc_type)rf[rs2]) pc=pc+(r_type)off_B;
											else pc=pc+4;
											break;
								case BGEU:	//printf("type: BGEU \n");
											if((pc_type)rf[rs1]>=(pc_type)rf[rs2]) pc=pc+(r_type)off_B;
											else pc=pc+4;
											break;
							}break;
			case JAL: 		//printf("JAL operation..");
							rf[rd]=pc+4;
							pc=pc+off_J;
							//printf("pc: %d\n",(uint32_t)pc);
							break;
			case JALR: 		//printf("JALR operation..");
							rf[rd]=pc+4;
							pc=(pc_type)(rf[rs1]+(pc_type)imm_11_0)&(-2);
							break;
			default: error=1;
			}
	//printf("op1: %x op2: %x\n",(uint32_t)op1,(uint32_t)op2);
	//printf("execution done.\n");
	//printf("registers:\n");
	//for(int j=0;j<32;j++) {printf("0x%x ",(uint32_t)rf[j]);if(j==15)printf("\n");}
	//printf("\n");
}
