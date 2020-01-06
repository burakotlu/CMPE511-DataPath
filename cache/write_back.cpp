#include "cache.hpp"

extern mem_type mem[MEM_SIZE];
extern cache_mem_type cache_mem [INDEX_SIZE][OFFSET_SIZE];


void write_back(tag_type tag,ind_type ind){
	add_type w_a=0;
	w_a =((((w_a | (add_type)tag)<<(INDEX_LENGTH))| (add_type)ind)<<OFFSET_LENGTH);
	//printf("writing block back to the memory..\n");
	//printf("data block in cache to write back into memory:\n");
	for (int i=0;i<OFFSET_SIZE;i++){
		//printf("offset %d is 0x%x\n",i,cache_mem[ind][i]);
		mem[w_a+i]=cache_mem[ind][i];
	}

}
