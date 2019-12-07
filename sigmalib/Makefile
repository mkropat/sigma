build/sigmalib.so: JAVA_HOME = $(shell echo 'System.out.println(java.lang.System.getProperty("java.home"));' | jshell -)

build/sigmalib.so: src/sigmalib.c src/sigmalib-jni.c
	mkdir -p build
	gcc -shared -fPIC \
		-o $@ \
		$^ \
		$(shell pkg-config --cflags --libs x11) \
		$(shell pkg-config --cflags --libs cairo) \
		-I"$(JAVA_HOME)/include" \
		-I"$(JAVA_HOME)/include/linux"

.PHONY: clean
clean:
	rm -rf build/
