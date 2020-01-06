#include  "datapath.hpp"
#include  "cache.hpp"
pc_type pc;
i_type curr_inst;
extern mem_type mem[MEM_SIZE];
int datapath(pc_type start_pc){
	//printf("start of the program\n");
	initiate_cache();
	//printf("cache has been initiated.\n");
	pc=start_pc;
	//printf("**********************************\n");
	//printf("current pc: %d\n",(uint32_t)pc);
	curr_inst=cache(pc);
	//printf("curr_inst: %x\n",(uint32_t)curr_inst);
	if(curr_inst==HLT) {
		//printf("first instruction in the program is HLT!");
		return 0;
	}
	do{
		decoder(curr_inst);
		//printf("**********************************\n");
		//printf("current pc: %d\n",(uint32_t)pc);
		curr_inst=cache(pc);
		//printf("curr_inst: %x\n",(uint32_t)curr_inst);
		//if(curr_inst==HLT) printf("halt instruction.\n");
	}while(curr_inst!=HLT);
	//program halted
	//printf("end of the program.\n");
	return 1;
}
