ALL := test

all: $(ALL)

test:

clean:
	rm -f $(ALL)

.PHONY: all clean
