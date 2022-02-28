default: stage10

bin:
	mkdir -p bin

bin/ebrew.o: ebrew.s | bin
	as -o $@ -c $^

bin/ebrew: bin/ebrew.o | bin
	ld -o $@ $^

# stage1: stage1/ebrew
# stage1/ebrew.s: ebrew.eb bin/ebrew
# 	mkdir -p $(dir $@)
# 	cat ebrew.eb | ./bin/ebrew > $@
# stage1/ebrew.o: stage1/ebrew.s
# 	as -o $@ -c $^
# stage1/ebrew: stage1/ebrew.o
# 	ld -o $@ $^ 

STAGE.s = cat ebrew.eb | $$LAST > $$NEXT.s
STAGE.o = as -o $$NEXT.o -c $$NEXT.s
STAGE = ld -o $$NEXT $$NEXT.o

stage%: ebrew.eb bin/ebrew
	@LAST=bin/ebrew; \
	for i in $$(seq 1 $(@:stage%=%)); do \
		NEXT=stage$$i/ebrew; \
			mkdir -p stage$$i; \
			echo "$(STAGE.s)"; $(STAGE.s); \
			echo "$(STAGE.o)"; $(STAGE.o); \
			echo "$(STAGE)"; $(STAGE); \
		 LAST=$$NEXT; \
	done

clean:
	@: rm -r bin
	@: rm -r stage*
