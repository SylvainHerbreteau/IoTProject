# Makefile for the paho-mqttpp (C++) sample applications

  PAHO_C_LIB_DIR ?= /usr/local/lib
  PAHO_C_INC_DIR ?= /usr/local/include

TGTS  = sync_subscribe

all: $(TGTS)

CXXFLAGS += -Wall -std=c++11
CPPFLAGS += -I.. -I$(PAHO_C_INC_DIR)

LDLIBS += -L../../lib -L$(PAHO_C_LIB_DIR) -lpaho-mqttpp3 -lpaho-mqtt3a

sync_subscribe: sync_subscribe.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $< $(LDLIBS)
# Cleanup

.PHONY: clean distclean

clean:
	rm -f $(TGTS)

distclean: clean
