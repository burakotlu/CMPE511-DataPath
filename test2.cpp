#include  "datapath.hpp"
#include  "cache.hpp"
#include  <stdio.h>

extern r_type rf[32];
extern mem_type mem[2048];

uint8_t prog[]={0x00,0xC1,0x81,0x93,   0x06,0xC1,0xA0,0x83,
		        0x06,0x41,0xA1,0x03,   0x06,0x41,0x91,0x03,
				0x06,0x41,0x81,0x03,   0x00,0x30,0x63,0xB3,
				0x06,0x11,0xA2,0x23,   0x06,0x11,0x94,0x23,
				0x01,0x80,0xD3,0x13,   0x06,0x52,0x02,0x03,
				0x00,0x41,0x82,0xB3,   0x02,0x53,0x00,0x63,
				0xFF,0x22,0x82,0x93,   0x01,0x02,0x82,0x93,
				0xFE,0x9F,0xF5,0x6F,   0xFF,0xFF,0xFF,0xFF,
				0x30,0x31,0x32,0x33};


uint8_t data[]={0x00,0x01,0x02,0x03,   0x04,0x05,0x06,0x07,
                0x08,0x09,0x10,0x11,   0xAA,0xBB,0xCC,0xDD,
                0x16,0x17,0x18,0x19,   0x11,0x22,0x33,0x44,};
int main(){
	//rf[3]=12;
	//rf[1]=0x11223344;
	printf("inst1:  0x00C18193 ADDI rd(3) rs1(0) imm(12)\n");
	printf("inst2:  0x06C1A083 LW rd(1) rs(3) off(108)\n");
    printf("inst3:  0x0641A103 LW rd(2) rs(3) off(100)\n");
    printf("inst4:  0x06419103 LH rd(2) rs(3) off(100)\n");
    printf("inst5:  0x06418103 LB rd(2) rs(3) off(100)\n");
    printf("inst6:  0x003063B3 OR rd(7) rs1(0) rs2(3)\n");
    printf("inst7:  0x0611A223 SW rs2(1) rs1(3) off(100)\n");
    printf("inst8:  0x06119423 SH rs2(1) rs1(3) off(104)\n");
    printf("inst9:  0x0180D313 SRLI rs1(1) rd(6) imm(24)\n");
    printf("inst10: 0x06520203 LB rd(4) rs(4) imm(101)\n");
    printf("inst11: 0x004182B3 ADD rd(5) rs1(3) rs2(4)\n");
    printf("inst12: 0x02530063 BEQ rs1(5) rs2(6) off(16)\n");
    printf("inst13: 0xFF228293 ADDI rd(5) rs1(5) imm(-14)\n");
    printf("inst14: 0x01028293 ADDI rd(5) rs1(5) imm(16)\n");
    printf("inst15: 0xFE9FF56F JAL rd(10) off(-12)\n");
	int plen=sizeof(prog)/sizeof(prog[0]);
	int dlen=sizeof(data)/sizeof(data[0]);
	printf("registers:");
	for(int j=0;j<32;j++) printf("0x%x ",(uint32_t)rf[j]);
	printf("\n");
	printf("-------------------------prog_mem-------------------\n");
	printf("1024,1025,...\n");
    for(int i=0;i<plen;i++){
        mem[1024+i]=prog[i];
		if(15<mem[1024+i]) printf("0x");
		else printf("0x0");
        printf("%x  ",(uint32_t)mem[1024+i]);
        if((i%8+1)==8) printf("\n");
    }printf("\n");
    printf("-------------------------data_mem-------------------\n");
    printf("100,101,...\n");
	for(int i=0;i<dlen;i++){
        mem[100+i]=data[i];
		if(15<mem[100+i]) printf("0x");
		else printf("0x0");
        printf("%x  ",(uint32_t)mem[100+i]);
        if((i%10+1)==10) printf("\n");
	}printf("\n------------------------------------------------------\n");

	
	datapath(1024);


    printf("-------------------------data_mem-------------------\n");
    printf("100,101,...\n");
	for(int i=0;i<dlen;i++){
		if(15<mem[100+i]) printf("0x");
		else printf("0x0");
		printf("%x  ",(uint32_t)mem[100+i]);
		if((i%10+1)==10) printf("\n");
	}
	/*int retval=0;
	FILE *fp;
	fp=fopen("result.dat","w");
	retval = system("diff --brief -w result.dat result.golden.dat");
    if (retval != 0) {
        printf("Test failed  !!!\n");
        retval=1;
    } else
        printf("Test passed !\n");*/
    return 0;
}
