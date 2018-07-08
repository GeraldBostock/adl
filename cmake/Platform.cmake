if(UNIX)
	add_definitions(
		-DADL_TARGET_SYSTEM_UNIX
		)
endif(UNIX)

if(WIN32)
	add_definitions(
		-DADL_TARGET_SYSTEM_WINDOWS
	)
endif(WIN32)