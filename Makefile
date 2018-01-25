PREFIX ?= /usr/local/bin

target := uoyweek
source := uoyweek.cpp

.DEFAULT_GOAL := $(target)

.PHONY: run install clean

$(target): $(source)
	$(CXX) -Wall -Wextra -pedantic $< -o $@
	chmod +x $@

run: $(target)
	./$(target) $(ARGS)

install: $(target)
	cp $^ $(PREFIX)

clean:
	$(RM) $(target)
