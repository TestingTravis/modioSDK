mkdir dynamic_build
cd dynamic_build
cmake -D test=on -G "Visual Studio 15" c:\projects\source
cmake --build . --config "Release"

if %APPVEYOR_REPO_TAG% == true (
  echo "Release tag detected"
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
  7z a Windows.zip dynamic_build\Release\* static_build\Release\* dynamic_build_64bits\Release\* static_build_64bits\Release\*
) else (
  echo "Release tag not detected"
)