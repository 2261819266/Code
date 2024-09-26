@echo off
:: 打印1234
:start
set /a var+=1
echo var = %var%
if %var% leq 3 goto start
pause
