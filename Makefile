# Project Name
TARGET = LoopyTunes

# Compiler
CXX = gcc
CXXFLAGS += -fPIC

# Sources
CPP_SOURCES = LoopyTunes.cpp DSP/Mixer.cpp Track.cpp DSP/FX/Delay.cpp Waveshaper.cpp DSP/FX/PitchShift.cpp DSP/FX/Reverb/Reverb.cpp revmodel.cpp comb.cpp allpass.cpp

# Library Locations
LIBDAISY_DIR = ../../../libDaisy/
DAISYSP_DIR = ../../../DaisySP/

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

# Bootloader / optimisation
OPT = -Os
#APP_TYPE = BOOT_QSPI

# Custom linker scripts
LDSCRIPT = ./STM32H750IB_my_flash.lds

# Debug
DEBUG = 1

# Flags
LDFLAGS += -u _printf_float

