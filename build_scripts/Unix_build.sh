BUILT_TARGET="Release"

#First parameter, if any, is used as build target.
#If no parameter is given, then default to Release
if [ "$#" == 0 ]; then
	BUILD_TARGET="Release"
else
	BUILD_TARGET="$1"
fi

#All remaining parameters are used as parameters to CMake

cd ..

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE="$BUILD_TARGET" "${@:1}" ../
make -j 4
