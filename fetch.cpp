#include "cache.hpp"
extern add_type value;
extern mem_type mem[MEM_SIZE];
extern cache_mem_type cache_mem [INDEX_SIZE][OFFSET_SIZE];
extern offset_type offset;

void fetch(tag_type tag_a,ind_type ind_a){
	add_type f_a=0;
	value=0;
	f_a =((((f_a | (add_type)tag_a)<<(INDEX_LENGTH))| (add_type)ind_a)<<OFFSET_LENGTH);
	//printf("fetching block from memory..");
	//printf("f_a: %d\n",(uint32_t)f_a);
	for (int i=0;i<OFFSET_SIZE;i++){
		value=value<<8;
		cache_mem[ind_a][i]=mem[f_a+i];
		value=value|mem[f_a+i];
		//printf("value: %x\n",(uint32_t)value);
//	if (i==offset)
//		value=cache_mem[ind_a][i];
	}
}





