@echo off

del /s *.x *.in *.out *.exe

for /d /r %%d in (*.cph) do rmdir /s /q "%%d"