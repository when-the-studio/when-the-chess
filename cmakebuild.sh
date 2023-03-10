build() {
	mkdir -p build
	cd build
	cmake ..
	make wtc
	compilation_result=$?
	cd ..

	if [ $compilation_result -ne 0 ]
	then
		# Compilation failed, we probably want to stop here in that case.
		echo "\e[31m\e[1mCompilation failed >.<\e[21m\e[39m"
		exit 1
	fi
}


help_function() {
	echo "aled"
}

run() {
	cd bin
	./wtc
	cd ..
}


build
## Parsing Command Line arguments
while getopts 'rh?' a
do
	case $a in
		r) run;;
		h) help_function;;
	esac
done
