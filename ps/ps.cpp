// ps.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "log.h"
#include "process_tree.h"


int main()
{
	initialize_log(log_mask_all, log_level_debug, log_to_con, nullptr);

	cprocess_tree pst;
	if (true != pst.build_process_tree(true))
	{
		log_err "pst.build_process_tree() failed." log_end;
		return -1;
	}

	pst.iterate_process([](_In_ process& process_info, _In_ DWORD_PTR callback_tag)->bool
	{
		UNREFERENCED_PARAMETER(callback_tag);
		log_info "pid = %u, name = %ws, path = %ws",
			process_info.pid(),
			process_info.process_name(),
			process_info.process_path()
			log_end
			return true;
	},
	0);

	finalize_log();
	
    return 0;
}

