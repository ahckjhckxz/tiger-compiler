set PATH=%WindowsSdkDir%bin\x86;%PATH%
set INCLUDE=%WindowsSdkDir%include\%WindowsSDKVersion%shared;%WindowsSdkDir%include\%WindowsSDKVersion%um;%WindowsSdkDir%include\%WindowsSDKVersion%winrt;%INCLUDE%
set LIB=%WindowsSdkDir%lib\%WindowsSDKLibVersion%um\x86;%LIB%
set LIBPATH=%WindowsLibPath%;%ExtensionSDKDir%\Microsoft.VCLibs\14.0\References\CommonConfiguration\neutral;%LIBPATH%
cl.exe out.c