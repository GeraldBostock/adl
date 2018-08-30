SET(_PF86 "PROGRAMFILES(X86)")
SET( RTTR_SEARCH_PATHS
	${RTTR_ROOT_DIR}					# RTTR!
	./dependencies/rttr
	$ENV{PROGRAMFILES}/rttr				# WINDOWS
	"$ENV{_PF86}/RTTR"					# WINDOWS
	~/Library/Frameworks				# MAC
	/Library/Frameworks					# MAC
	/usr/local							# LINUX/MAC/UNIX
	/usr								# LINUX/MAC/UNIX
	/opt								# LINUX/MAC/UNIX
)

FIND_PATH( RTTR_INCLUDE_DIRS
	NAMES
		rttr/library.h
	PATHS
		${RTTR_SEARCH_PATHS}
	PATH_SUFFIXES
		include
	DOC
		"The directory where GL/glew.h resides"
)

FIND_LIBRARY( RTTR_LIBRARIES
	NAMES
		rttr_core_d.lib
	PATHS
		${RTTR_SEARCH_PATHS}
	PATH_SUFFIXES
		lib
		lib64
		lib/Release/Win32
		lib/Release/x64
	DOC
		"The GLEW library"
)

# Check if we found it!
IF ( RTTR_INCLUDE_DIRS AND RTTR_LIBRARIES )
	SET( RTTR_FOUND TRUE )
	MESSAGE( STATUS "Looking for RTTR - found" )
ELSE ( RTTR_INCLUDE_DIRS AND RTTR_LIBRARIES )
	SET( RTTR_FOUND FALSE )
	MESSAGE( STATUS "Looking for RTTR - not found" )
ENDIF ( RTTR_INCLUDE_DIRS AND RTTR_LIBRARIES )