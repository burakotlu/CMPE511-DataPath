#include  "datapath.hpp"
#include  "cache.hpp"
extern int error;
extern r_type rf[32];
extern mem_type mem[MEM_SIZE];
//mem_type mem[1000];

void lsu(lsu_type op, func3_type width,rf_pntr_type des, rf_pntr_type src,imm12_type offset){

	add_type data,temp;
	int flag;
	if(op==L){
		switch(width){
			case BYTE:	data=cache(rf[src]+(add_type)offset)&BYTE_MASK;temp=data;flag=((temp<<24)>>31);
						if (flag==1) data=data|0xFFFFFF00;//sign extend
						rf[des]=data;
						break;
			case HALF:	data=cache(rf[src]+(add_type)offset)&HALF_MASK;temp=data;flag=((temp<<16)>>31);
						if (flag==1) data=data|0xFFFF0000;//sign extend
						rf[des]=data;
						break;
 		    case WORD:rf[des]=cache(rf[src]+(add_type)offset);break;
			case UBYTE:rf[des]=cache(rf[src]+(add_type)offset)&BYTE_MASK;break;
			case UHALF:rf[des]=cache(rf[src]+(add_type)offset)&HALF_MASK;break;
		}
	}
	else if(op==S){
		switch(width){
			case BYTE: data=cache(rf[des]+(add_type)offset);
					   data=data&0xFFFFFF00;
					   temp=rf[src]&BYTE_MASK;
					   data=temp|data;
					   cache_write(rf[des]+(add_type)offset,data);
					   break;
			case HALF: data=cache(rf[des]+(add_type)offset);
					   data=data&0xFFFF0000;
					   temp=rf[src]&HALF_MASK;
					   data=temp|data;
					   cache_write(rf[des]+(add_type)offset,data);
					   break;
			case WORD: cache_write(rf[des]+(add_type)offset,rf[src]);
			   	   	   break;
		}
	}
	else
		error=1;
}
