# Project Name
TARGET = LoopyTunes

# Sources
CPP_SOURCES = LoopyTunes.cpp Mixer.cpp Track.cpp

# Library Locations
LIBDAISY_DIR = ../../../libDaisy/
DAISYSP_DIR = ../../../DaisySP/

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile
