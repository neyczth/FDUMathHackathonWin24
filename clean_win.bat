@echo off
setlocal enabledelayedexpansion

for /r %%f in (*.exe *.in *.out) do (
    del "%%f"
    echo Deleted "%%f"
)

for /r %%d in (.) do (
    if exist "%%d\.cph\" (
        rmdir /s /q "%%d\.cph\"
        set "dirpath=%%d"
        echo Deleted "!dirpath:~0,-2!\.cph\"
    )
)