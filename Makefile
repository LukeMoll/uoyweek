PREFIX ?= /usr/local
CPPFLAGS ?= -Wall -Wextra -pedantic

target := uoyweek

.PHONY: all run install clean

%: %.cpp
	$(CXX) $(CPPFLAGS) -o $@ $<

all: $(target)

run: $(target)
	./$(target) $(ARGS)

install: $(target)
	mkdir -p $(PREFIX)/bin
	cp $^ $(PREFIX)/bin

clean:
	$(RM) $(target)
