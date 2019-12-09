PREFIX ?= .
BUILD ?= build
INCLUDEDIR ?= $(PREFIX)/include
LIBDIR ?= $(PREFIX)/lib

# Clear default suffix rules
.SUFFIXES :

all : $(BUILD)/libelastiblob.a

test : $(BUILD)/elastiblob_test
	@($(BUILD)/elastiblob_test && echo "TEST PASSED!") || echo "TEST FAILED!"

install : $(LIBDIR)/libelastiblob.a $(INCLUDEDIR)/elastiblob.h

$(LIBDIR)/%.a : $(BUILD)/%.a
	@mkdir -pv $(@D)
	@cp -fv $< $@

$(INCLUDEDIR)/elastiblob.h : elastiblob.h
	@mkdir -pv $(@D)
	@cp -fv $< $@

$(BUILD)/libelastiblob.a : $(BUILD)/elastiblob.o
	@mkdir -pv $(@D)
	@ar -ruv $@ $^

$(BUILD)/elastiblob_test : elastiblob_test.c $(BUILD)/elastiblob.o
	@mkdir -pv $(@D)
	$(CC) $^ -o $@

$(BUILD)/elastiblob.o : elastiblob.c elastiblob.h
	@mkdir -pv $(@D)
	$(CC) -c -O3 $< -o $@

clean :
	$(RM) $(BUILD)/elastiblob.o
	$(RM) $(BUILD)/elastiblob_test
	$(RM) $(BUILD)/elastiblob.a
