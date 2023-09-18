all:= build

build:
    @echo "Build Started"
    g++ -o sampleapp ./src/MakeMeAFile.cpp -I.
    @echo "Build Complete"
    ./sampleapp

clean:
    @echo "Cleaning up"
    rm *.o