@echo off
setlocal enabledelayedexpansion

for /r %%f in (*.exe *.in *.out) do (
    del "%%f"
)

for /r %%d in (.) do (
    if exist "%%d\.cph\" (
        rmdir /s /q "%%d\.cph\"
    )
)