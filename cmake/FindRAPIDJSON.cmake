SET(_PF86 "PROGRAMFILES(X86)")
SET( RAPIDJSON_SEARCH_PATHS
	${RAPIDJSON_ROOT_DIR}					# SPDLOG!
	./dependencies/rapidjson
	$ENV{PROGRAMFILES}/rapidjson				# WINDOWS
	"$ENV{_PF86}/rapidjson"					# WINDOWS
	~/Library/Frameworks				# MAC
	/Library/Frameworks					# MAC
	/usr/local							# LINUX/MAC/UNIX
	/usr								# LINUX/MAC/UNIX
	/opt								# LINUX/MAC/UNIX
)

FIND_PATH( RAPIDJSON_INCLUDE_DIRS
	NAMES
		rapidjson.h
	PATHS
		${RAPIDJSON_SEARCH_PATHS}
	PATH_SUFFIXES
		include
	DOC
		"The directory where rapidjson.h resides"
)

# Check if we found it!
IF ( RAPIDJSON_INCLUDE_DIRS)
	SET( RAPIDJSON_FOUND TRUE )
	MESSAGE( STATUS "Looking for RAPIDJSON - found" )
ELSE ( SPDLOG_INCLUDE_DIRS )
	SET( RAPIDJSON_FOUND FALSE )
	MESSAGE( STATUS "Looking for rapidjson - not found" )
ENDIF ( RAPIDJSON_INCLUDE_DIRS)