# Project Name
TARGET = LoopyTunes

# Sources
CPP_SOURCES = LoopyTunes.cpp DSP/Mixer.cpp Track.cpp DSP/FX/Delay.cpp Waveshaper.cpp

# Library Locations
LIBDAISY_DIR = ../../../libDaisy/
DAISYSP_DIR = ../../../DaisySP/

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

# Flags
LDFLAGS += -u _printf_float