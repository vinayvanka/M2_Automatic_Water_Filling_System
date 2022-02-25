# Test Plans

|  Test ID | Description  | Input  | Output  | Status |
|---|---|---|---|---|
| TID_01  | Manual Mode  | Mode Switch = 1| Mode Switch = 1| PASS  |
| TID_02  | Manual OFF pump  | push button = 0| push button = 0 | PASS  |
| TID_03  | Pump OFF indication  | push button = 0 | LED = 0 | PASS  |
| TID_04  | Manual ON pump  | push button=1| push button=1 | PASS  |
| TID_05  | Pump ON indication  | push button=1 | LED = 1 | PASS  |
| TID_06  | Automatic mode | Mode Switch = 0| Mode Switch = 0  | PASS  |
| TID_07  | Automatic Pump ON | float switch 1 = 0 | PUMP = 1  | PASS  |
| TID_08  | Automatic Pump OFF | float switch 5 = 1 | PUMP = 0 | PASS  |
| TID_09  | LCD Display | float switch 1 = 0 | LOW water level | PASS  |
| TID_09  | LCD Display | float switch 1 = 1 | 20% water level | PASS  |
| TID_09  | LCD Display | float switch 2 = 1 | 40% water level | PASS  |
| TID_09  | LCD Display | float switch 3 = 1 | 60% water level | PASS  |
| TID_09  | LCD Display | float switch 4 = 1 | 80% water level | PASS  |
| TID_09  | LCD Display | float switch 5 = 1 | TANK FULL !!!   | PASS  |