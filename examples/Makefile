all:
	set -e; \
	for i in */Makefile */*/Makefile; do \
		echo '==== Making:' $$(dirname $$i); \
		$(MAKE) -C $$(dirname $$i) -j; \
	done

clean:
	set -e; \
	for i in */Makefile */*/Makefile; do \
		echo '==== Cleaning:' $$(dirname $$i); \
		$(MAKE) -C $$(dirname $$i) clean; \
	done
