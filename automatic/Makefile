#
# Copyright 2021 xhr-git
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

BUILD_OUTPUT = _build
BUILD_SRC    = 
# Application name
BUILD_EXE    = test.exe

# Add a search directory for header files other than the $(BUILD_SRC) directory
INCLUDES = 
# Add a search directory for libraries
LD_DIRS = 
# Add required libraries
LD_LIBS = -lpthread

CFLAGS = -g -O2

CPP       = $(CC) -E
CC        = $(CROSS_COMPILE)gcc
LD        = $(CROSS_COMPILE)ld
AR        = $(CROSS_COMPILE)ar
NM        = $(CROSS_COMPILE)nm
OBJCOPY   = $(CROSS_COMPILE)objcopy
OBJDUMP   = $(CROSS_COMPILE)objdump
READELF   = $(CROSS_COMPILE)readelf
STRIP     = $(CROSS_COMPILE)strip

export CPP CC LD AR NM OBJCOPY OBJDUMP READELF STRIP

COMPILE_CFLAGS  := -Wall -Wundef -Werror=strict-prototypes -Wno-trigraphs \
		   -fno-strict-aliasing -fno-common -fshort-wchar -std=gnu89 \
		   -Werror=implicit-function-declaration -Werror=implicit-int \
		   -Werror=return-type -Wno-format-security

rwildcard = $(foreach d,$(wildcard $(addsuffix *,$(1))), \
	    $(call rwildcard,$(d)/,$(2))$(filter $(subst *,%,$(2)),$(d)))

ifdef BUILD_OUTPUT
  BUILD_OUTPUT := $(BUILD_OUTPUT)/
endif

ifndef BUILD_SRC
  BUILD_SRC := ./
endif

SOURCES = $(sort $(call rwildcard,$(BUILD_SRC),*.c))
OBJECTS = $(addprefix $(BUILD_OUTPUT),$(patsubst %.c,%.o,$(SOURCES)))
DEPENDS = $(OBJECTS:.o=.d)

INCLUDES_DIR = $(sort \
	       $(foreach d,$(call rwildcard,$(BUILD_SRC),*.h),$(dir -I$d)) \
	       $(INCLUDES))

ALL_FLAGS = $(INCLUDES_DIR) $(CFLAGS) $(COMPILE_CFLAGS)

PHONY := __all__
__all__: $(BUILD_EXE)
	@:


$(BUILD_EXE): $(OBJECTS)
	@echo "    LD  $@"
	@$(CC) $(ALL_FLAGS) -o $@ $(OBJECTS) $(LD_LIBS)
	@echo
	@echo ">>>  successful !!"
	@echo


ifeq ($(MAKECMDGOALS),)
$(BUILD_OUTPUT)%.d: %.c
	@mkdir -p $(dir $@)
	@set -e; rm -f $@; \
	$(CC) $(INCLUDES_DIR) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($(*F)\)\.o[ :]*,$(@:.d=.o) $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(DEPENDS)
endif

$(BUILD_OUTPUT)%.o: %.c
	@echo "    CC  $@"
	@$(CC) $(ALL_FLAGS) -c -o $@ $<


PHONY := clean
clean:
	@-rm -f $(BUILD_EXE)
ifdef BUILD_OUTPUT
	@-rm -rf $(BUILD_OUTPUT)
else
	@-rm -f $(OBJECTS) $(DEPENDS)
endif

PHONY := show_vars
show_vars:
	@echo "  BUILD_OUTPUT = $(BUILD_OUTPUT)"
	@echo "  BUILD_SRC = $(BUILD_SRC)"
	@echo "  SOURCES = $(SOURCES)"
	@echo "  OBJECTS = $(OBJECTS)"
	@echo "  DEPENDS = $(DEPENDS)"
	@echo "  INCLUDES_DIR = $(INCLUDES_DIR)"
	@echo "  CFLAGS = $(CFLAGS)"
	@echo "  LD_LIBS = $(LD_LIBS)"


# Declare the contents of the PHONY variable as phony.  We keep that
# information in a variable so we can use it in if_changed and friends.
.PHONY: $(PHONY)
