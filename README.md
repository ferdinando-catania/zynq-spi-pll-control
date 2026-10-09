# Zynq-7000 SPI control of a TI LMX2820 PLL (ZedBoard)

Exam project for **System on Chip** (M.Sc. Electronic Engineering, University of Naples Federico II, prof. N. Petra), 2025/2026.

A Zynq-7000 SoC (ZedBoard, XC7Z020) programs a **TI LMX2820** wideband PLL over SPI. Two push-buttons on the board load two complete register configurations (2 GHz and 4 GHz output); LEDs confirm the configuration, and the result is verified on the bench with an oscilloscope (SPI bus) and a spectrum analyser (PLL output).

> **Note on IP.** The SPI master in the programmable logic is a proprietary AXI4-Lite IP core provided by the company where I work. Its HDL and documentation are **not** part of this repository and are treated here as a black box. Everything published here is my own work.

## Architecture

```
 ┌──────────────── Zynq-7000 (ZedBoard) ────────────────┐
 │  PS: ARM Cortex-A9 (bare-metal app)                  │
 │    ├─ PS GPIO (MIO 50/51) ← push-buttons             │        LMX2820-EVM
 │    ├─ UART  → status messages                        │      ┌───────────┐
 │    └─ M_AXI_GP0 ── AXI interconnect ──┐              │ SPI  │           │
 │                                       │              │ ───▶ │ CSB  SCK  │
 │  PL: Artix-7 fabric                   ▼              │ PMOD │ SDI       │
 │    ├─ AXI GPIO → LD0/LD1                             │  JA  │ MUXOUT ◀──│
 │    └─ AXI4-Lite SPI master (proprietary, not incl.) ─┼───── └───────────┘
 └──────────────────────────────────────────────────────┘
```

- **SPI clock**: AXI clock (100 MHz) ÷ 8 = **12.5 MHz** (LMX2820 max 40 MHz), fixed 8:1 ratio between the AXI and SPI domains.
- **SPI frame**: 24 bit = R/W flag + 7-bit address + 16-bit data, MSB first, CSB active low.
- **I/O**: SPI on PMOD JA (LVCMOS33), status on LD0/LD1.

## Repository layout

| Path | Content |
| --- | --- |
| `sw/main.c` | Bare-metal application (Vitis): button edge detection on PS GPIO, LED feedback on AXI GPIO, UART log |
| `constraints/pll.xdc` | Pin-out and I/O standards for the SPI lines and LEDs |
| `pll_config/conf1_2GHz.txt`, `conf2_4GHz.txt` | Full LMX2820 register maps (R0–R122) exported from TI TICS Pro, written by the PS through the SPI core |

## Flow

1. **Vivado**: Zynq PS configuration (clocks, MIO/EMIO), block design with AXI interconnect, AXI GPIO and the SPI IP; constraints; synthesis, implementation, timing and power reports; bitstream and `.xsa` export.
2. **Vitis**: platform + BSP from the `.xsa`, standalone (no OS) application.
3. **Validation**: SPI waveforms (SCK = 12.5 MHz, SDI, CSB) measured on the PMOD pins with an oscilloscope; 2 GHz / 4 GHz carrier checked with a spectrum analyser.

## Skills

Zynq-7000 SoC · Vivado block design · AXI4-Lite · SPI · PLL / RF synthesizers · bare-metal C (Vitis) · XDC constraints · lab validation (oscilloscope, spectrum analyser)
