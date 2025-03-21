@echo off

D:
cd D:\HMView\bin\

start "" "D:\HMView\bin\HmViewApp.exe"

cd D:\HmXlWebManager\HmXliWeb\
start /min python "D:\HmXlWebManager\HmXliWeb\HmMain.py"

exit