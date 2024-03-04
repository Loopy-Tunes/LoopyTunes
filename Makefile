# Project Name
TARGET = LoopyTunes

# Sources
CPP_SOURCES = LoopyTunes.cpp DSP/Mixer.cpp Track.cpp DSP/FX/Delay.cpp Waveshaper.cpp Reverb/Reverb.cpp

# Library Locations
LIBDAISY_DIR = ../../../libDaisy/
DAISYSP_DIR = ../../../DaisySP/

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

# Bootloader / optimisation
OPT = -O3
APP_TYPE = BOOT_QSPI

# Debug
DEBUG = 1

# Flags
LDFLAGS += -u _printf_float