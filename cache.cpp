#include "cache.hpp"


mem_type mem[MEM_SIZE];
cache_mem_type cache_mem [INDEX_SIZE][OFFSET_SIZE]; //1 Kbyte*4 cache memory creation
valid_type valid[INDEX_SIZE]; // valid array creation
tag_type tag[INDEX_SIZE]; // tag array creation

tag_type tag_add;
ind_type index;
offset_type offset;
add_type value;

add_type cache (add_type address) {
	value=0;
	index= (ind_type) (address >> INDEX_SHAMT) & INDEX_MASK ;
	tag_add= (tag_type) (address >> TAG_SHAMT) & TAG_MASK ;
	offset= (offset_type) address & TAG_MASK ;

	if (valid[index]==N){
		//printf("miss.."); // case "cache miss"
		fetch(tag_add,index);// fetch corresponding block from memory
		valid[index]=Y; //set valid to Yes
		tag[index]=tag_add;
	}
	else if (valid[index]==Y){ // valid is Yes
		if(tag[index]==tag_add){ //tag is the same --> case "cache hit"
			//printf("hit..fetching block from cache..");
			for (int i=0;i<OFFSET_SIZE;i++){
				value=value<<8;
				value=value|cache_mem[index][i]; // read value from cache
				//printf("value: %x\n",(uint32_t)value);
			}

		}
		else{ //valid is Yes, tag is different--> case "cache miss", content must be replaced
			//printf("miss..replace the content of the cache from memory..");
			write_back(tag[index],index);
			fetch(tag_add,index); // fetch corresponding block from memory
			tag[index]=tag_add; // change tag with current tag
		}
	}
	return value; // returns byte in the address to CPU
}




