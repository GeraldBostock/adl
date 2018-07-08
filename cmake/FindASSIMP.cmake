SET(_PF86 "PROGRAMFILES(X86)")
SET( ASSIMP_SEARCH_PATHS
	${ASSIMP_ROOT_DIR}					# ASSIMP!
	./dependencies/assimp
	$ENV{PROGRAMFILES}/assimp			# WINDOWS
	"$ENV{_PF86}/assimp"				# WINDOWS
	~/Library/Frameworks				# MAC
	/Library/Frameworks					# MAC
	/usr/local							# LINUX/MAC/UNIX
	/usr								# LINUX/MAC/UNIX
	/opt								# LINUX/MAC/UNIX
)

FIND_PATH( ASSIMP_INCLUDE_DIRS
	NAMES
		assimp/mesh.h
	PATHS
		${ASSIMP_SEARCH_PATHS}
	PATH_SUFFIXES
		include
		assimp
	DOC
		"The directory where assimp/mesh.h resides"
)

FIND_LIBRARY( ASSIMP_LIBRARIES
	NAMES
		assimp ASSIMP
	PATHS
		${ASSIMP_SEARCH_PATHS}
	PATH_SUFFIXES
		lib
		lib64
		lib/x86
		lib/x64
	DOC
		"The ASSIMP library"
)

# Check if we found it!
IF ( ASSIMP_INCLUDE_DIRS AND ASSIMP_LIBRARIES )
	SET( ASSIMP_FOUND TRUE )
	MESSAGE(STATUS "Looking for ASSIMP - found")
ELSE ( ASSIMP_INCLUDE_DIRS AND ASSIMP_LIBRARIES )
	SET( ASSIMP_FOUND FALSE )
	MESSAGE(STATUS "Looking for ASSIMP - not found")
ENDIF ( ASSIMP_INCLUDE_DIRS AND ASSIMP_LIBRARIES )