# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Piimps\Documents\PSoC Creator\Project_Elec\Project_Final.cydsn\Project_Final.cyprj
# Date: Wed, 01 Apr 2020 10:05:31 GMT
#set_units -time ns
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\Piimps\Documents\PSoC Creator\Project_Elec\Project_Final.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Piimps\Documents\PSoC Creator\Project_Elec\Project_Final.cydsn\Project_Final.cyprj
# Date: Wed, 01 Apr 2020 10:05:26 GMT
