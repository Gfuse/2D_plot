ROOT_DIR=`pwd`

if [ -d "$ROOT_DIR/qwt" ]; then
    if [ -d "$ROOT_DIR/build" ]; then
       echo "deleting build"
       rm -r build
    fi
    mkdir -p build && cd build && \
    cmake ../
    make
else
    git clone https://github.com/opencor/qwt.git
    cd qwt
    qmake qwt.pro
    sudo make install
    cd ..
    if [ -d "$ROOT_DIR/build" ]; then
       echo "deleting build"
       rm -r build
    fi
    mkdir -p build && cd build && \
    cmake ../
    make
fi


