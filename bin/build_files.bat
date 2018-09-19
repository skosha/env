del my_cscope.files
dir /b /s /A:-D *.c *.h *.s *.xml | findstr /v /I "bin\ arch\ unity\" >> my_cscope.files
