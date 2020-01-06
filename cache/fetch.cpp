#include "cache.hpp"
extern add_type value;
extern mem_type mem[MEM_SIZE];
extern cache_mem_type cache_mem [INDEX_SIZE][OFFSET_SIZE];
extern offset_type offset;

void fetch(tag_type tag_a,ind_type ind_a){
	add_type f_a=0;
	value=0;
	offset_type off_i=(offset>>2);
	f_a =((((add_type)tag_a)<<INDEX_LENGTH)| (add_type)ind_a)<<OFFSET_LENGTH;
	for (int i=0;i<OFFSET_SIZE;i++){
		cache_mem[ind_a][i]=mem[f_a+i];
		if(off_i==(i>>2)){
			value=value<<8;
			value=value|mem[f_a+i];
		}
		//printf("value: %x\n",(uint32_t)value);
//	if (i==offset)
//		value=cache_mem[ind_a][i];
	}
}





