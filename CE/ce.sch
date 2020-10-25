EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GNDREF #PWR07
U 1 1 5F959AC3
P 4000 5350
F 0 "#PWR07" H 4000 5100 50  0001 C CNN
F 1 "GNDREF" H 4005 5177 50  0000 C CNN
F 2 "" H 4000 5350 50  0001 C CNN
F 3 "" H 4000 5350 50  0001 C CNN
	1    4000 5350
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR05
U 1 1 5F959D3B
P 3500 5350
F 0 "#PWR05" H 3500 5100 50  0001 C CNN
F 1 "GNDREF" H 3505 5177 50  0000 C CNN
F 2 "" H 3500 5350 50  0001 C CNN
F 3 "" H 3500 5350 50  0001 C CNN
	1    3500 5350
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BF199 Q1
U 1 1 5F95B400
P 3900 4650
F 0 "Q1" H 4090 4696 50  0000 L CNN
F 1 "BF199" H 4090 4605 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4100 4575 50  0001 L CIN
F 3 "http://www.micropik.com/PDF/BF199.pdf" H 3900 4650 50  0001 L CNN
	1    3900 4650
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR06
U 1 1 5F95BD3C
P 4000 4000
F 0 "#PWR06" H 4000 3850 50  0001 C CNN
F 1 "VCC" H 4015 4173 50  0000 C CNN
F 2 "" H 4000 4000 50  0001 C CNN
F 3 "" H 4000 4000 50  0001 C CNN
	1    4000 4000
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR04
U 1 1 5F95C431
P 3500 4000
F 0 "#PWR04" H 3500 3850 50  0001 C CNN
F 1 "VCC" H 3515 4173 50  0000 C CNN
F 2 "" H 3500 4000 50  0001 C CNN
F 3 "" H 3500 4000 50  0001 C CNN
	1    3500 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5F95CFC3
P 4000 4200
F 0 "R3" H 4070 4246 50  0000 L CNN
F 1 "R" H 4070 4155 50  0000 L CNN
F 2 "" V 3930 4200 50  0001 C CNN
F 3 "~" H 4000 4200 50  0001 C CNN
	1    4000 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5F95D4EC
P 3500 4200
F 0 "R1" H 3570 4246 50  0000 L CNN
F 1 "R" H 3570 4155 50  0000 L CNN
F 2 "" V 3430 4200 50  0001 C CNN
F 3 "~" H 3500 4200 50  0001 C CNN
	1    3500 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5F95D7F6
P 3500 5100
F 0 "R2" H 3570 5146 50  0000 L CNN
F 1 "R" H 3570 5055 50  0000 L CNN
F 2 "" V 3430 5100 50  0001 C CNN
F 3 "~" H 3500 5100 50  0001 C CNN
	1    3500 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5F95D973
P 4000 5100
F 0 "R4" H 4070 5146 50  0000 L CNN
F 1 "R" H 4070 5055 50  0000 L CNN
F 2 "" V 3930 5100 50  0001 C CNN
F 3 "~" H 4000 5100 50  0001 C CNN
	1    4000 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5F95E6B5
P 4300 5100
F 0 "C2" H 4415 5146 50  0000 L CNN
F 1 "C" H 4415 5055 50  0000 L CNN
F 2 "" H 4338 4950 50  0001 C CNN
F 3 "~" H 4300 5100 50  0001 C CNN
	1    4300 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5F95EEAB
P 3250 4650
F 0 "C1" V 2998 4650 50  0000 C CNN
F 1 "C" V 3089 4650 50  0000 C CNN
F 2 "" H 3288 4500 50  0001 C CNN
F 3 "~" H 3250 4650 50  0001 C CNN
	1    3250 4650
	0    1    1    0   
$EndComp
$Comp
L Device:C C3
U 1 1 5F960133
P 4450 4400
F 0 "C3" V 4198 4400 50  0000 C CNN
F 1 "C" V 4289 4400 50  0000 C CNN
F 2 "" H 4488 4250 50  0001 C CNN
F 3 "~" H 4450 4400 50  0001 C CNN
	1    4450 4400
	0    1    1    0   
$EndComp
Wire Wire Line
	3500 4350 3500 4650
Wire Wire Line
	3400 4650 3500 4650
Connection ~ 3500 4650
Wire Wire Line
	3500 4650 3500 4950
Wire Wire Line
	3700 4650 3500 4650
Wire Wire Line
	3500 4000 3500 4050
Wire Wire Line
	4000 4000 4000 4050
Wire Wire Line
	4000 4350 4000 4400
Wire Wire Line
	4000 4850 4000 4900
Wire Wire Line
	4300 4950 4300 4900
Wire Wire Line
	4300 4900 4000 4900
Connection ~ 4000 4900
Wire Wire Line
	4000 4900 4000 4950
Wire Wire Line
	4300 4400 4000 4400
Connection ~ 4000 4400
Wire Wire Line
	4000 4400 4000 4450
Wire Wire Line
	3500 5250 3500 5350
Wire Wire Line
	4000 5250 4000 5350
$Comp
L power:GNDREF #PWR08
U 1 1 5F962E70
P 4300 5350
F 0 "#PWR08" H 4300 5100 50  0001 C CNN
F 1 "GNDREF" H 4305 5177 50  0000 C CNN
F 2 "" H 4300 5350 50  0001 C CNN
F 3 "" H 4300 5350 50  0001 C CNN
	1    4300 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 5250 4300 5350
$Comp
L power:GNDREF #PWR03
U 1 1 5F9632B2
P 3050 5350
F 0 "#PWR03" H 3050 5100 50  0001 C CNN
F 1 "GNDREF" H 3055 5177 50  0000 C CNN
F 2 "" H 3050 5350 50  0001 C CNN
F 3 "" H 3050 5350 50  0001 C CNN
	1    3050 5350
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR09
U 1 1 5F963866
P 4700 5350
F 0 "#PWR09" H 4700 5100 50  0001 C CNN
F 1 "GNDREF" H 4705 5177 50  0000 C CNN
F 2 "" H 4700 5350 50  0001 C CNN
F 3 "" H 4700 5350 50  0001 C CNN
	1    4700 5350
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 5F9651CF
P 4900 4400
F 0 "J3" H 4980 4392 50  0000 L CNN
F 1 "Conn_01x02" H 4980 4301 50  0000 L CNN
F 2 "" H 4900 4400 50  0001 C CNN
F 3 "~" H 4900 4400 50  0001 C CNN
	1    4900 4400
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 5F965E02
P 2850 4750
F 0 "J2" H 2768 4425 50  0000 C CNN
F 1 "Conn_01x02" H 2768 4516 50  0000 C CNN
F 2 "" H 2850 4750 50  0001 C CNN
F 3 "~" H 2850 4750 50  0001 C CNN
	1    2850 4750
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5F966B79
P 2400 4050
F 0 "J1" H 2480 4042 50  0000 L CNN
F 1 "Conn_01x02" H 2480 3951 50  0000 L CNN
F 2 "" H 2400 4050 50  0001 C CNN
F 3 "~" H 2400 4050 50  0001 C CNN
	1    2400 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR02
U 1 1 5F968094
P 2200 4250
F 0 "#PWR02" H 2200 4000 50  0001 C CNN
F 1 "GNDREF" H 2205 4077 50  0000 C CNN
F 2 "" H 2200 4250 50  0001 C CNN
F 3 "" H 2200 4250 50  0001 C CNN
	1    2200 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 4150 2200 4250
$Comp
L power:VCC #PWR01
U 1 1 5F968D7E
P 2200 4000
F 0 "#PWR01" H 2200 3850 50  0001 C CNN
F 1 "VCC" H 2215 4173 50  0000 C CNN
F 2 "" H 2200 4000 50  0001 C CNN
F 3 "" H 2200 4000 50  0001 C CNN
	1    2200 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 4000 2200 4050
Wire Wire Line
	4700 4400 4600 4400
Wire Wire Line
	3050 4750 3050 5350
Wire Wire Line
	3050 4650 3100 4650
Wire Wire Line
	4700 4500 4700 5350
$EndSCHEMATC