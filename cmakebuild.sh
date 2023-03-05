build() {
    mkdir -p build
    cd build
    cmake ..
    make wtc
    cd ..
}


help_function() {
    echo "aled"
}

run() {
    ./bin/wtc
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
