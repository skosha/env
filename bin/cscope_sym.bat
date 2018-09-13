
IF /I "%1%" GEQ "1" (
    rem build the dir1 cscope connections
    call build_files.bat
    C:\Work\Tools\bin\cscope.exe -b -c -i my_cscope.files
)

IF /I "%1%" GEQ "2" (
    rem build the dir2 cscope connections
    PUSHD ..\
    call build_files.bat
    C:\Work\Tools\bin\cscope.exe -b -c -i my_cscope.files
    POPD
)

IF /I "%1%" GEQ "3" (
    rem build the dir3 cscope connections
    PUSHD ..\..\..\dir3
    C:\Work\Tools\bin\cscope.exe -b -c -R
    POPD
)

