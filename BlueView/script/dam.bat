@echo off
taskkill /f /im HMDam_stm.exe /t
taskkill /f /im HMDam.exe
D:
cd D:\HMView\bin\
%del C:\Users\Administrator\AppData\Local\Temp\*.*  /s /q%
rd C:\Users\Administrator\AppData\Local\Temp /s /q
md C:\Users\Administrator\AppData\Local\Temp
cd D:\HMView\bin\
start /min HMDam_stm.exe


exit