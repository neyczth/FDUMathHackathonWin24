@echo off
setlocal

for /r %%f in (*.exe *.in) do (
    del "%%f"
    echo Deleted "%%f"
)