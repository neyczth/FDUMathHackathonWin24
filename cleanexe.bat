@echo off
setlocal

for /r "%cd%" %%f in (*.exe *.in) do ( del "%%f" )