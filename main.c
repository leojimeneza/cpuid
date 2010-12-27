#include "prefix.h"

#include "cache.h"
#include "cpuid.h"
#include "feature.h"
#include "handlers.h"
#include "util.h"
#include "state.h"
#include "vendor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dump_cpuid(struct cpuid_state_t *state)
{
	uint32_t i;
	struct cpu_regs_t cr_tmp;

	for (i = 0; i <= state->stdmax; i++) {
		ZERO_REGS(&cr_tmp);
		cr_tmp.eax = i;
		state->cpuid_call(&cr_tmp, state);
		if (HAS_HANDLER(std_dump_handlers, i))
			std_dump_handlers[i](&cr_tmp, state);
		else
			printf("CPUID %08x, results = %08x %08x %08x %08x | %s\n",
				state->last_leaf.eax,
				cr_tmp.eax,
				cr_tmp.ebx,
				cr_tmp.ecx,
				cr_tmp.edx,
				reg_to_str(&cr_tmp));
	}
	
	for (i = 0x80000000; i <= state->extmax; i++) {
		ZERO_REGS(&cr_tmp);
		cr_tmp.eax = i;
		state->cpuid_call(&cr_tmp, state);
		if (HAS_HANDLER(ext_dump_handlers, i - 0x80000000))
			ext_dump_handlers[i - 0x80000000](&cr_tmp, state);
		else
			printf("CPUID %08x, results = %08x %08x %08x %08x | %s\n",
				state->last_leaf.eax,
				cr_tmp.eax,
				cr_tmp.ebx,
				cr_tmp.ecx,
				cr_tmp.edx,
				reg_to_str(&cr_tmp));
	}

	for (i = 0x40000000; i <= state->hvmax; i++) {
		ZERO_REGS(&cr_tmp);
		cr_tmp.eax = i;
		state->cpuid_call(&cr_tmp, state);
		if (HAS_HANDLER(vmm_dump_handlers, i - 0x40000000))
			vmm_dump_handlers[i - 0x40000000](&cr_tmp, state);
		else
			printf("CPUID %08x, results = %08x %08x %08x %08x | %s\n",
				state->last_leaf.eax,
				cr_tmp.eax,
				cr_tmp.ebx,
				cr_tmp.ecx,
				cr_tmp.edx,
				reg_to_str(&cr_tmp));
	}
	printf("\n");
}

void run_cpuid(struct cpuid_state_t *state)
{
	uint32_t i;
	struct cpu_regs_t cr_tmp;

	for (i = 0; i <= state->stdmax; i++) {
		ZERO_REGS(&cr_tmp);
		cr_tmp.eax = i;
		state->cpuid_call(&cr_tmp, state);
		if (HAS_HANDLER(std_handlers, i))
			std_handlers[i](&cr_tmp, state);
	}
	
	for (i = 0x80000000; i <= state->extmax; i++) {
		ZERO_REGS(&cr_tmp);
		cr_tmp.eax = i;
		state->cpuid_call(&cr_tmp, state);
		if (HAS_HANDLER(ext_handlers, i - 0x80000000))
			ext_handlers[i - 0x80000000](&cr_tmp, state);
	}

	for (i = 0x40000000; i <= state->hvmax; i++) {
		ZERO_REGS(&cr_tmp);
		cr_tmp.eax = i;
		state->cpuid_call(&cr_tmp, state);
		if (HAS_HANDLER(vmm_handlers, i - 0x40000000))
			vmm_handlers[i - 0x40000000](&cr_tmp, state);
	}
}

int main(int argc, char **argv)
{
	struct cpuid_state_t state;

	INIT_CPUID_STATE(&state);
	if (argc > 1) {
		cpuid_load_from_file(argv[1], &state);
		state.cpuid_call = cpuid_pseudo;
	}
	dump_cpuid(&state);
	FREE_CPUID_STATE(&state);

	INIT_CPUID_STATE(&state);
	if (argc > 1) {
		cpuid_load_from_file(argv[1], &state);
		state.cpuid_call = cpuid_pseudo;
	}
	run_cpuid(&state);
	FREE_CPUID_STATE(&state);

	return 0;
}
