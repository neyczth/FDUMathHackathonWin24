@echo off
setlocal

for /r %%f in (*.exe *.in *.out) do (
    del "%%f"
    echo Deleted "%%f"
)