@echo off
setlocal enabledelayedexpansion

for /r %%d in (.) do (
    for %%f in ("%%d\*.x" "%%d\*.in" "%%d\*.exe" "%%d\*.out") do (
        del "%%f"
        echo Deleted "%%f"
    )
    if exist "%%d\.cph\" (
        rmdir /s /q "%%d\.cph\"
        set "dirpath=%%d"
        echo Deleted "!dirpath:~0,-2!\.cph\"
    )
)