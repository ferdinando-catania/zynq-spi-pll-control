
# ----------------------------------------------------------------------------
# SPI - Pmod JA1 (Fila Superiore)
# ----------------------------------------------------------------------------
# SCLK - Pin 1 del Pmod JA1
set_property PACKAGE_PIN Y11 [get_ports PLL1_SCK]
set_property IOSTANDARD LVCMOS33 [get_ports PLL1_SCK]

# MOSI - Pin 2 del Pmod JA1
set_property PACKAGE_PIN AA11 [get_ports PLL1_MUX_OUT_FMC]
set_property IOSTANDARD LVCMOS33 [get_ports PLL1_MUX_OUT_FMC]

# MISO - Pin 3 del Pmod JA1 (Corretto: Y10 invece di Y19)
set_property PACKAGE_PIN Y10 [get_ports PLL1_SDI]
set_property IOSTANDARD LVCMOS33 [get_ports PLL1_SDI]

# CS - Pin 4 del Pmod JA1
set_property PACKAGE_PIN AA9 [get_ports PLL1_CSB]
set_property IOSTANDARD LVCMOS33 [get_ports PLL1_CSB]

# ----------------------------------------------------------------------------
# LED - PL (User LEDs)
# ----------------------------------------------------------------------------leds_2bits_tri_o
# LD0 - Pin T22
set_property PACKAGE_PIN T22 [get_ports {leds_2bits_tri_o[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {leds_2bits_tri_o[0]}]

# LD1 - Pin T21
set_property PACKAGE_PIN T21 [get_ports {leds_2bits_tri_o[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {leds_2bits_tri_o[1]}]
