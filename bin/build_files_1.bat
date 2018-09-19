del my_cscope.files
dir /b /s .\builds\*.c .\builds\*.h .\builds\*.xml | findstr /v /I "bin\ arch\ unity\" >> my_cscope.files
dir /b /s .\common\*.c .\common\*.h .\common\*.s .\common\*.xml | findstr /v /I "bin\ arch\ unity\" >> my_cscope.files
