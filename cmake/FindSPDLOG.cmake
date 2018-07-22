SET(_PF86 "PROGRAMFILES(X86)")
SET( SPDLOG_SEARCH_PATHS
	${SPDLOG_ROOT_DIR}					# SPDLOG!
	./dependencies/spdlog
	$ENV{PROGRAMFILES}/spdlog				# WINDOWS
	"$ENV{_PF86}/spdlog"					# WINDOWS
	~/Library/Frameworks				# MAC
	/Library/Frameworks					# MAC
	/usr/local							# LINUX/MAC/UNIX
	/usr								# LINUX/MAC/UNIX
	/opt								# LINUX/MAC/UNIX
)

FIND_PATH( SPDLOG_INCLUDE_DIRS
	NAMES
		spdlog.h
	PATHS
		${SPDLOG_SEARCH_PATHS}
	PATH_SUFFIXES
		include
	DOC
		"The directory where spdlog.h resides"
)

# Check if we found it!
IF ( SPDLOG_INCLUDE_DIRS)
	SET( SPDLOG_FOUND TRUE )
	MESSAGE( STATUS "Looking for SPDLOG - found" )
ELSE ( SPDLOG_INCLUDE_DIRS )
	SET( SPDLOG_FOUND FALSE )
	MESSAGE( STATUS "Looking for SPDLOG - not found" )
ENDIF ( SPDLOG_INCLUDE_DIRS)