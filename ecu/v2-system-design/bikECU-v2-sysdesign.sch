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
L Device:Battery BT?
U 1 1 617BAFFA
P 900 1300
F 0 "BT?" H 1008 1346 50  0000 L CNN
F 1 "Li-Po 2S" H 1008 1255 50  0000 L CNN
F 2 "" V 900 1360 50  0001 C CNN
F 3 "~" V 900 1360 50  0001 C CNN
	1    900  1300
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Reed SW?
U 1 1 617BB8D7
P 10200 900
F 0 "SW?" H 10200 1122 50  0000 C CNN
F 1 "SW_Reed" H 10200 1031 50  0000 C CNN
F 2 "" H 10200 900 50  0001 C CNN
F 3 "~" H 10200 900 50  0001 C CNN
	1    10200 900 
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 617BC4B1
P 10300 1350
F 0 "J?" H 10380 1342 50  0000 L CNN
F 1 "Conn_01x04" H 10380 1251 50  0000 L CNN
F 2 "" H 10300 1350 50  0001 C CNN
F 3 "~" H 10300 1350 50  0001 C CNN
	1    10300 1350
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW?
U 1 1 617BD0AF
P 9750 2050
F 0 "SW?" H 9750 2285 50  0000 C CNN
F 1 "SW_SPST" H 9750 2194 50  0000 C CNN
F 2 "" H 9750 2050 50  0001 C CNN
F 3 "~" H 9750 2050 50  0001 C CNN
	1    9750 2050
	1    0    0    -1  
$EndComp
Text Notes 10150 1900 0    50   ~ 0
Switch for front light
Text Notes 10150 2400 0    50   ~ 0
Switch for rear light
Text Notes 10150 2850 0    50   ~ 0
Screen cycle button
$Comp
L Relay:G5Q-1 K?
U 1 1 617BDE2A
P 1850 3450
F 0 "K?" H 2280 3496 50  0000 L CNN
F 1 "G5Q-1" H 2280 3405 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_Omron-G5Q-1" H 2300 3400 50  0001 L CNN
F 3 "https://www.omron.com/ecb/products/pdf/en-g5q.pdf" H 1850 3450 50  0001 L CNN
	1    1850 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 617BFDEA
P 10000 5650
F 0 "R?" H 10070 5696 50  0000 L CNN
F 1 "R" H 10070 5605 50  0000 L CNN
F 2 "" V 9930 5650 50  0001 C CNN
F 3 "~" H 10000 5650 50  0001 C CNN
	1    10000 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 617C02ED
P 10000 6150
F 0 "R?" H 10070 6196 50  0000 L CNN
F 1 "R" H 10070 6105 50  0000 L CNN
F 2 "" V 9930 6150 50  0001 C CNN
F 3 "~" H 10000 6150 50  0001 C CNN
	1    10000 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 6000 10000 5900
Wire Wire Line
	10000 5900 10750 5900
Connection ~ 10000 5900
Wire Wire Line
	10000 5900 10000 5800
Text Label 10200 5900 0    50   ~ 0
VBAT_MEAS
$Comp
L Switch:SW_SPST SW?
U 1 1 617C2539
P 9750 2500
F 0 "SW?" H 9750 2735 50  0000 C CNN
F 1 "SW_SPST" H 9750 2644 50  0000 C CNN
F 2 "" H 9750 2500 50  0001 C CNN
F 3 "~" H 9750 2500 50  0001 C CNN
	1    9750 2500
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW?
U 1 1 617C2829
P 9750 3000
F 0 "SW?" H 9750 3235 50  0000 C CNN
F 1 "SW_SPST" H 9750 3144 50  0000 C CNN
F 2 "" H 9750 3000 50  0001 C CNN
F 3 "~" H 9750 3000 50  0001 C CNN
	1    9750 3000
	1    0    0    -1  
$EndComp
$Comp
L Power_Management:INA3221 U?
U 1 1 617C3B2E
P 3100 1600
F 0 "U?" H 3400 1000 50  0000 C CNN
F 1 "INA3221" H 3500 900 50  0000 C CNN
F 2 "Package_DFN_QFN:Texas_RGV_S-PVQFN-N16_EP2.1x2.1mm" H 3100 2700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/ina3221.pdf" H 3100 2300 50  0001 C CNN
	1    3100 1600
	1    0    0    -1  
$EndComp
Text Notes 550  6800 0    50   ~ 0
SSR alternatives:\nSSR SOIC: CPC1907B\nSSR SIP: CPC1706
$Comp
L Diode:1N4007 D?
U 1 1 617BDF24
P 1250 3450
F 0 "D?" V 1200 3250 50  0000 L CNN
F 1 "1N4007" V 1300 3050 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 1250 3275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 1250 3450 50  0001 C CNN
	1    1250 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	1650 3750 1650 3800
Wire Wire Line
	1650 3800 1250 3800
Wire Wire Line
	1250 3800 1250 3600
Wire Wire Line
	1650 3150 1650 3050
Wire Wire Line
	1650 3050 1250 3050
Wire Wire Line
	1250 3050 1250 3300
$Comp
L Timer_RTC:DS3231M U?
U 1 1 617BD428
P 5350 7000
F 0 "U?" H 5850 6800 50  0000 C CNN
F 1 "DS3231M" H 5950 6700 50  0000 C CNN
F 2 "Package_SO:SOIC-16W_7.5x10.3mm_P1.27mm" H 5350 6400 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS3231.pdf" H 5620 7050 50  0001 C CNN
	1    5350 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 6800 4850 6800
Wire Wire Line
	4400 6900 4850 6900
Wire Wire Line
	5250 6350 5250 6600
$Comp
L Device:Battery_Cell BT?
U 1 1 617BFD3C
P 6250 7000
F 0 "BT?" H 6368 7096 50  0000 L CNN
F 1 "Battery_Cell" H 6368 7005 50  0000 L CNN
F 2 "" V 6250 7060 50  0001 C CNN
F 3 "~" V 6250 7060 50  0001 C CNN
	1    6250 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 6500 6250 6500
Wire Wire Line
	6250 6500 6250 6800
Wire Wire Line
	5350 6500 5350 6600
Wire Wire Line
	5350 7400 5350 7500
Wire Wire Line
	5350 7500 6250 7500
Wire Wire Line
	6250 7500 6250 7100
Text Label 9600 1250 0    50   ~ 0
GND_OLED
Text Label 9600 1450 0    50   ~ 0
SDA_OLED
Text Label 9600 1350 0    50   ~ 0
+3V3_OLED
Text Label 9600 1550 0    50   ~ 0
SCL_OLED
Wire Wire Line
	9600 1250 10100 1250
Wire Wire Line
	9600 1350 10100 1350
Wire Wire Line
	9600 1450 10100 1450
Wire Wire Line
	9600 1550 10100 1550
Text Label 9450 900  0    50   ~ 0
REED_IN
Text Label 10650 900  0    50   ~ 0
REED_OUT
Text Label 6000 2100 0    50   ~ 0
SW_L_R
Text Label 8150 2900 0    50   ~ 0
SW_L_R_OUT
Text Label 6000 2200 0    50   ~ 0
SW_L_F
Text Label 8150 3150 0    50   ~ 0
SW_L_F_OUT
Wire Wire Line
	9450 900  10000 900 
Wire Wire Line
	10400 900  11050 900 
Text Label 6000 2300 0    50   ~ 0
BTN_A
Text Label 8150 2800 0    50   ~ 0
SW_L_R_IN
Text Label 8150 3050 0    50   ~ 0
SW_L_F_IN
Text Label 8150 3300 0    50   ~ 0
BTN_A_IN
Text Label 8150 3400 0    50   ~ 0
BTN_A_OUT
Text Label 8600 1700 0    50   ~ 0
GND_OLED
Text Label 8600 1900 0    50   ~ 0
SDA_OLED
Text Label 8600 1800 0    50   ~ 0
+3V3_OLED
Text Label 8600 2000 0    50   ~ 0
SCL_OLED
Text Label 6000 1700 0    50   ~ 0
+3V3
Text Label 6000 1800 0    50   ~ 0
SDA
Text Label 6000 1900 0    50   ~ 0
SCL
Text Label 6000 1500 0    50   ~ 0
REED
Text Label 8100 800  0    50   ~ 0
REED_IN
Text Label 8100 900  0    50   ~ 0
REED_OUT
$Comp
L power:GND #PWR?
U 1 1 617D8C86
P 5950 1400
F 0 "#PWR?" H 5950 1150 50  0001 C CNN
F 1 "GND" V 5955 1272 50  0000 R CNN
F 2 "" H 5950 1400 50  0001 C CNN
F 3 "" H 5950 1400 50  0001 C CNN
	1    5950 1400
	0    1    1    0   
$EndComp
Text Label 6000 2000 0    50   ~ 0
L_F_+
Text Label 6000 1600 0    50   ~ 0
L_R_+
Text Label 8150 3650 0    50   ~ 0
L_F_+
Text Label 8150 3750 0    50   ~ 0
L_F_-
Text Label 8300 1600 0    50   ~ 0
L_R_+
Text Label 8300 1500 0    50   ~ 0
L_R_-
$Comp
L power:GND #PWR?
U 1 1 617DB785
P 6600 750
F 0 "#PWR?" H 6600 500 50  0001 C CNN
F 1 "GND" V 6605 622 50  0000 R CNN
F 2 "" H 6600 750 50  0001 C CNN
F 3 "" H 6600 750 50  0001 C CNN
	1    6600 750 
	0    -1   -1   0   
$EndComp
$Comp
L power:+BATT #PWR?
U 1 1 617DE2C6
P 8450 6250
F 0 "#PWR?" H 8450 6100 50  0001 C CNN
F 1 "+BATT" V 8450 6500 50  0000 C CNN
F 2 "" H 8450 6250 50  0001 C CNN
F 3 "" H 8450 6250 50  0001 C CNN
	1    8450 6250
	0    1    1    0   
$EndComp
$Comp
L power:-BATT #PWR?
U 1 1 617E013F
P 8450 6350
F 0 "#PWR?" H 8450 6200 50  0001 C CNN
F 1 "-BATT" V 8465 6478 50  0000 L CNN
F 2 "" H 8450 6350 50  0001 C CNN
F 3 "" H 8450 6350 50  0001 C CNN
	1    8450 6350
	0    1    1    0   
$EndComp
Text Notes 7750 6250 0    50   ~ 0
Batt conn
Text Notes 8100 650  0    50   ~ 0
Reed harness\n2xAWG22 50cm
Text Notes 8900 1600 0    50   ~ 0
OLED harness\n4xAWG26 70cm
Text Notes 8200 1400 0    50   ~ 0
Rear harness\n2xAWG22\nto fit EDAC
Text Notes 7600 4800 0    50   ~ 0
Main power switch
$Comp
L power:+BATT #PWR?
U 1 1 617F4762
P 900 1100
F 0 "#PWR?" H 900 950 50  0001 C CNN
F 1 "+BATT" H 915 1273 50  0000 C CNN
F 2 "" H 900 1100 50  0001 C CNN
F 3 "" H 900 1100 50  0001 C CNN
	1    900  1100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 617F51C8
P 900 1500
F 0 "#PWR?" H 900 1250 50  0001 C CNN
F 1 "GND" H 905 1327 50  0000 C CNN
F 2 "" H 900 1500 50  0001 C CNN
F 3 "" H 900 1500 50  0001 C CNN
	1    900  1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 617F5C03
P 5350 7500
F 0 "#PWR?" H 5350 7250 50  0001 C CNN
F 1 "GND" H 5355 7327 50  0000 C CNN
F 2 "" H 5350 7500 50  0001 C CNN
F 3 "" H 5350 7500 50  0001 C CNN
	1    5350 7500
	1    0    0    -1  
$EndComp
Connection ~ 5350 7500
$Comp
L power:+3V3 #PWR?
U 1 1 617F6770
P 5250 6350
F 0 "#PWR?" H 5250 6200 50  0001 C CNN
F 1 "+3V3" H 5265 6523 50  0000 C CNN
F 2 "" H 5250 6350 50  0001 C CNN
F 3 "" H 5250 6350 50  0001 C CNN
	1    5250 6350
	1    0    0    -1  
$EndComp
Text Label 4400 6800 0    50   ~ 0
MCU_SCL
Text Label 4400 6900 0    50   ~ 0
MCU_SDA
$Comp
L power:+BATT #PWR?
U 1 1 617F89D0
P 2050 3750
F 0 "#PWR?" H 2050 3600 50  0001 C CNN
F 1 "+BATT" H 2065 3923 50  0000 C CNN
F 2 "" H 2050 3750 50  0001 C CNN
F 3 "" H 2050 3750 50  0001 C CNN
	1    2050 3750
	-1   0    0    1   
$EndComp
Wire Wire Line
	2150 3050 2150 3150
Text Label 2250 3050 0    50   ~ 0
AUX1_CS+
Text Label 3700 1800 0    50   ~ 0
MCU_SCL
Text Label 3700 1700 0    50   ~ 0
MCU_SDA
Wire Wire Line
	4100 1700 3600 1700
Wire Wire Line
	4100 1800 3600 1800
$Comp
L power:GND #PWR?
U 1 1 617FBE8C
P 3000 2250
F 0 "#PWR?" H 3000 2000 50  0001 C CNN
F 1 "GND" H 3005 2077 50  0000 C CNN
F 2 "" H 3000 2250 50  0001 C CNN
F 3 "" H 3000 2250 50  0001 C CNN
	1    3000 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 2250 3000 2200
$Comp
L power:+VDC #PWR?
U 1 1 618019E2
P 2500 1300
F 0 "#PWR?" H 2500 1200 50  0001 C CNN
F 1 "+VDC" V 2500 1529 50  0000 L CNN
F 2 "" H 2500 1300 50  0001 C CNN
F 3 "" H 2500 1300 50  0001 C CNN
	1    2500 1300
	0    -1   -1   0   
$EndComp
$Comp
L power:+VDC #PWR?
U 1 1 61803AA4
P 1650 2850
F 0 "#PWR?" H 1650 2750 50  0001 C CNN
F 1 "+VDC" H 1650 3125 50  0000 C CNN
F 2 "" H 1650 2850 50  0001 C CNN
F 3 "" H 1650 2850 50  0001 C CNN
	1    1650 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1300 2600 1300
Wire Wire Line
	2550 1200 2550 1050
Wire Wire Line
	2550 1200 2600 1200
Text Label 2150 1600 0    50   ~ 0
AUX1
Text Label 2150 1500 0    50   ~ 0
AUX1_CS+
Wire Wire Line
	2150 1500 2600 1500
Wire Wire Line
	2150 1600 2600 1600
Wire Wire Line
	2150 3050 2650 3050
Text Label 2150 1800 0    50   ~ 0
AUX2_CS+
Wire Wire Line
	2150 1800 2600 1800
Wire Wire Line
	2150 1900 2600 1900
Text Label 2150 1900 0    50   ~ 0
AUX2
$Comp
L power:+3V3 #PWR?
U 1 1 618179CA
P 3000 850
F 0 "#PWR?" H 3000 700 50  0001 C CNN
F 1 "+3V3" H 3015 1023 50  0000 C CNN
F 2 "" H 3000 850 50  0001 C CNN
F 3 "" H 3000 850 50  0001 C CNN
	1    3000 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 900  3000 850 
Text Label 550  4050 0    50   ~ 0
AUX1_CTL
Wire Wire Line
	1000 4050 550  4050
Wire Wire Line
	1650 4350 1650 4250
$Comp
L power:GND #PWR?
U 1 1 617C22BF
P 1650 4350
F 0 "#PWR?" H 1650 4100 50  0001 C CNN
F 1 "GND" H 1655 4177 50  0000 C CNN
F 2 "" H 1650 4350 50  0001 C CNN
F 3 "" H 1650 4350 50  0001 C CNN
	1    1650 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 4050 1350 4050
$Comp
L Device:R R?
U 1 1 617BCFF4
P 1150 4050
F 0 "R?" H 1220 4096 50  0000 L CNN
F 1 "1k" H 1220 4005 50  0000 L CNN
F 2 "" V 1080 4050 50  0001 C CNN
F 3 "~" H 1150 4050 50  0001 C CNN
	1    1150 4050
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:BC547 Q?
U 1 1 617BC492
P 1550 4050
F 0 "Q?" H 1741 4096 50  0000 L CNN
F 1 "BC547" H 1741 4005 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 1750 3975 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BC550-D.pdf" H 1550 4050 50  0001 L CNN
	1    1550 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 3850 1650 3800
Connection ~ 1650 3800
Wire Wire Line
	1650 2850 1650 3050
Connection ~ 1650 3050
$Comp
L Relay:G5Q-1 K?
U 1 1 6183720C
P 1850 5650
F 0 "K?" H 2280 5696 50  0000 L CNN
F 1 "G5Q-1" H 2280 5605 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_Omron-G5Q-1" H 2300 5600 50  0001 L CNN
F 3 "https://www.omron.com/ecb/products/pdf/en-g5q.pdf" H 1850 5650 50  0001 L CNN
	1    1850 5650
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D?
U 1 1 61837216
P 1250 5650
F 0 "D?" V 1200 5450 50  0000 L CNN
F 1 "1N4007" V 1300 5250 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 1250 5475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 1250 5650 50  0001 C CNN
	1    1250 5650
	0    1    1    0   
$EndComp
Wire Wire Line
	1650 5950 1650 6000
Wire Wire Line
	1650 6000 1250 6000
Wire Wire Line
	1250 6000 1250 5800
Wire Wire Line
	1650 5350 1650 5250
Wire Wire Line
	1650 5250 1250 5250
Wire Wire Line
	1250 5250 1250 5500
$Comp
L power:+BATT #PWR?
U 1 1 61837226
P 2050 5950
F 0 "#PWR?" H 2050 5800 50  0001 C CNN
F 1 "+BATT" H 2065 6123 50  0000 C CNN
F 2 "" H 2050 5950 50  0001 C CNN
F 3 "" H 2050 5950 50  0001 C CNN
	1    2050 5950
	-1   0    0    1   
$EndComp
Wire Wire Line
	2150 5250 2150 5350
Text Label 2250 5250 0    50   ~ 0
AUX2_CS+
$Comp
L power:+VDC #PWR?
U 1 1 61837232
P 1650 5050
F 0 "#PWR?" H 1650 4950 50  0001 C CNN
F 1 "+VDC" H 1650 5325 50  0000 C CNN
F 2 "" H 1650 5050 50  0001 C CNN
F 3 "" H 1650 5050 50  0001 C CNN
	1    1650 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 5250 2650 5250
Text Label 550  6250 0    50   ~ 0
AUX2_CTL
Wire Wire Line
	1000 6250 550  6250
Wire Wire Line
	1650 6550 1650 6450
$Comp
L power:GND #PWR?
U 1 1 61837240
P 1650 6550
F 0 "#PWR?" H 1650 6300 50  0001 C CNN
F 1 "GND" H 1655 6377 50  0000 C CNN
F 2 "" H 1650 6550 50  0001 C CNN
F 3 "" H 1650 6550 50  0001 C CNN
	1    1650 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 6250 1350 6250
$Comp
L Device:R R?
U 1 1 6183724B
P 1150 6250
F 0 "R?" H 1220 6296 50  0000 L CNN
F 1 "1k" H 1220 6205 50  0000 L CNN
F 2 "" V 1080 6250 50  0001 C CNN
F 3 "~" H 1150 6250 50  0001 C CNN
	1    1150 6250
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:BC547 Q?
U 1 1 61837255
P 1550 6250
F 0 "Q?" H 1741 6296 50  0000 L CNN
F 1 "BC547" H 1741 6205 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 1750 6175 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BC550-D.pdf" H 1550 6250 50  0001 L CNN
	1    1550 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 6050 1650 6000
Connection ~ 1650 6000
Wire Wire Line
	1650 5050 1650 5250
Connection ~ 1650 5250
Wire Notes Line
	9200 500  9200 6450
Wire Notes Line
	4250 2500 600  2500
Wire Notes Line
	600  2500 600  600 
Wire Notes Line
	600  600  4250 600 
Wire Notes Line
	4250 600  4250 2500
$Comp
L MCU_RaspberryPi_and_Boards:RP2040_Connect U?
U 1 1 617D8CFF
P 3700 4150
F 0 "U?" H 3675 5115 50  0000 C CNN
F 1 "RP2040_Connect" H 3675 5024 50  0000 C CNN
F 2 "" V 3700 3900 50  0001 C CNN
F 3 "" H 3700 3900 50  0001 C CNN
	1    3700 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D?
U 1 1 6185AA73
P 9700 3500
F 0 "D?" V 9739 3382 50  0000 R CNN
F 1 "LED" V 9648 3382 50  0000 R CNN
F 2 "" H 9700 3500 50  0001 C CNN
F 3 "~" H 9700 3500 50  0001 C CNN
	1    9700 3500
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D?
U 1 1 6185C13A
P 10650 3500
F 0 "D?" V 10689 3382 50  0000 R CNN
F 1 "LED" V 10598 3382 50  0000 R CNN
F 2 "" H 10650 3500 50  0001 C CNN
F 3 "~" H 10650 3500 50  0001 C CNN
	1    10650 3500
	0    -1   -1   0   
$EndComp
Text Label 9700 3350 0    50   ~ 0
L_F_+
Text Label 9700 3800 0    50   ~ 0
L_F_-
Text Label 10650 3350 0    50   ~ 0
L_R_+
Text Label 10650 3800 0    50   ~ 0
L_R_-
Wire Wire Line
	10650 3650 10650 3800
Wire Wire Line
	9700 3800 9700 3650
Wire Wire Line
	9700 3800 9950 3800
Wire Wire Line
	10900 3800 10650 3800
Wire Wire Line
	9700 3350 9950 3350
Wire Wire Line
	10650 3350 10900 3350
Text Notes 5500 5050 0    50   ~ 0
ECU side: 10 distinct signals\n7 if I2C buttons\n-> SP21-12P initially
Text Notes 6750 5350 0    50   ~ 0
PWR_EXT ?
Text Notes 8550 6950 0    50   ~ 0
Protoboard:\n60x60mm\nRaster 20x20 holes, missing corners, but + rails on the sides\nM3 mounthing holes 51.5mm apart
$Comp
L Switch:SW_SPST_LED SW?
U 1 1 61AA91AE
P 7900 5300
F 0 "SW?" H 7900 5635 50  0000 C CNN
F 1 "SW_SPST_LED" H 7900 5544 50  0000 C CNN
F 2 "" H 7900 5600 50  0001 C CNN
F 3 "~" H 7900 5600 50  0001 C CNN
	1    7900 5300
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR?
U 1 1 61AB6DBF
P 7550 5200
F 0 "#PWR?" H 7550 5050 50  0001 C CNN
F 1 "+BATT" H 7565 5373 50  0000 C CNN
F 2 "" H 7550 5200 50  0001 C CNN
F 3 "" H 7550 5200 50  0001 C CNN
	1    7550 5200
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61AB7F70
P 7550 5300
F 0 "#PWR?" H 7550 5050 50  0001 C CNN
F 1 "GND" H 7555 5127 50  0000 C CNN
F 2 "" H 7550 5300 50  0001 C CNN
F 3 "" H 7550 5300 50  0001 C CNN
	1    7550 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 5200 7700 5200
Wire Wire Line
	7700 5300 7550 5300
Text Label 2500 1050 2    50   ~ 0
VBAT_SW
Wire Wire Line
	2100 1050 2550 1050
Text Label 8200 5200 0    50   ~ 0
VBAT_SW
Wire Wire Line
	8550 5200 8100 5200
$Comp
L power:+VDC #PWR?
U 1 1 61AC13B9
P 8550 5300
F 0 "#PWR?" H 8550 5200 50  0001 C CNN
F 1 "+VDC" V 8550 5529 50  0000 L CNN
F 2 "" H 8550 5300 50  0001 C CNN
F 3 "" H 8550 5300 50  0001 C CNN
	1    8550 5300
	0    1    1    0   
$EndComp
Wire Wire Line
	8550 5300 8100 5300
$Comp
L Connector_Generic:Conn_01x12 J?
U 1 1 61ACE863
P 7250 1900
F 0 "J?" H 7168 2617 50  0000 C CNN
F 1 "Conn_01x12" H 7168 2526 50  0000 C CNN
F 2 "" H 7250 1900 50  0001 C CNN
F 3 "~" H 7250 1900 50  0001 C CNN
	1    7250 1900
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x12 J?
U 1 1 61AD111B
P 6700 1900
F 0 "J?" H 6650 2650 50  0000 L CNN
F 1 "Conn_01x12" H 6400 2550 50  0000 L CNN
F 2 "" H 6700 1900 50  0001 C CNN
F 3 "~" H 6700 1900 50  0001 C CNN
	1    6700 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 1400 6500 1400
Wire Wire Line
	7900 1400 7900 800 
Wire Wire Line
	7450 1500 8000 1500
Wire Wire Line
	8000 1500 8000 900 
Wire Wire Line
	7900 800  8550 800 
Wire Wire Line
	8000 900  8550 900 
Wire Wire Line
	6000 1500 6500 1500
Wire Wire Line
	6000 1700 6500 1700
Wire Wire Line
	6500 1800 6000 1800
Wire Wire Line
	6000 1900 6500 1900
Text Notes 8300 2650 0    50   ~ 0
Front harness\n 2xAWG22\n(4xAWG26 for btns)
Wire Wire Line
	7450 1400 7900 1400
Wire Wire Line
	7850 1800 9100 1800
Wire Wire Line
	7900 1400 8150 1400
Connection ~ 7900 1400
Wire Wire Line
	8150 1500 8150 1400
Wire Wire Line
	8150 1500 8700 1500
Wire Wire Line
	7450 1600 8700 1600
Wire Wire Line
	6000 1600 6500 1600
Wire Wire Line
	7450 1700 7850 1700
Wire Wire Line
	7850 1700 7850 1800
Wire Wire Line
	7450 1800 7800 1800
Wire Wire Line
	7800 1800 7800 1900
Wire Wire Line
	7800 1900 9100 1900
Wire Wire Line
	7450 1900 7750 1900
Wire Wire Line
	7750 1900 7750 2000
Wire Wire Line
	7750 2000 9100 2000
Wire Wire Line
	7900 1700 7900 1400
Wire Wire Line
	7900 1700 9100 1700
Text Label 2500 4150 0    50   ~ 0
MCU_SDA
Text Label 2500 4250 0    50   ~ 0
MCU_SCL
Wire Wire Line
	2500 4250 2900 4250
Wire Wire Line
	2500 4150 2900 4150
Wire Wire Line
	2500 4050 2900 4050
Text Label 2500 4050 0    50   ~ 0
AUX1_CTL
Text Label 4600 4450 0    50   ~ 0
REED
Wire Wire Line
	4800 4450 4550 4450
Text Notes 7900 5550 0    50   ~ 0
LED: 2.8 mA @ 9.5 V
Text Notes 3350 5100 0    50   ~ 0
Arduino: 12 mA @ 9.5 V
Text Notes 2950 5350 0    50   ~ 0
Arduino SCH:\nhttps://content.arduino.cc/assets/ABX00053-schematics.pdf
Wire Wire Line
	2500 3850 2900 3850
Text Label 2500 3850 0    50   ~ 0
BTN_CASE
$EndSCHEMATC
