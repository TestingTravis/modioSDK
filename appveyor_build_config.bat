echo %APPVEYOR_REPO_TAG%

if %APPVEYOR_REPO_TAG% == false (
  echo "not set"
  echo "not set2"
) else (
  echo "set"
  echo "set2"
)

mkdir dynamic_build
cd dynamic_build
cmake -G "Visual Studio 15" c:\projects\source
cmake --build . --config "Release"
mkdir ..\static_build
cd ..\static_build
cmake -D mode=static -G "Visual Studio 15" c:\projects\source
cmake --build . --config "Release"
mkdir ..\dynamic_build_64bits
cd ..\dynamic_build_64bits
cmake -G "Visual Studio 15 Win64" c:\projects\source
cmake --build . --config "Release"
mkdir ..\static_build_64bits
cd ..\static_build_64bits
cmake -D mode=static -G "Visual Studio 15 Win64" c:\projects\source
cmake --build . --config "Release"
cd ..