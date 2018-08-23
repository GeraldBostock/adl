SET(_PF86 "PROGRAMFILES(X86)")
SET( STBIMAGE_SEARCH_PATHS
	${STBIMAGE_ROOT_DIR}					# ASSIMP!
	./dependencies/stb
	$ENV{PROGRAMFILES}/stb		# WINDOWS
	"$ENV{_PF86}/stbimage"				# WINDOWS
	~/Library/Frameworks				# MAC
	/Library/Frameworks					# MAC
	/usr/local							# LINUX/MAC/UNIX
	/usr								# LINUX/MAC/UNIX
	/opt								# LINUX/MAC/UNIX
)

FIND_PATH( STBIMAGE_INCLUDE_DIRS
	NAMES
		stb_image.h
	PATHS
		${STBIMAGE_SEARCH_PATHS}
	PATH_SUFFIXES
		include
	DOC
		"The directory where assimp/mesh.h resides"
)

# Check if we found it!
IF ( STBIMAGE_INCLUDE_DIRS )
	SET( STBIMAGE_FOUND TRUE )
	MESSAGE(STATUS "Looking for stb_image - found")
ELSE ( STBIMAGE_INCLUDE_DIRS )
	SET( STBIMAGE_FOUND FALSE )
	MESSAGE(STATUS "Looking for stb_image - not found")
ENDIF ( STBIMAGE_INCLUDE_DIRS  )