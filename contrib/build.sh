#!/bin/sh

######################################
#LIBS
OPENSSL=openssl-1.0.1g
BDB=db-4.8.30
BOOST=boost_1_52_0
######################################

export LIBS=$(readlink -f ./libs)

export CC="/usr/local/x86_64-linux-musl/bin/x86_64-linux-musl-gcc"
export CXX="/usr/local/x86_64-linux-musl/bin/x86_64-linux-musl-g++"
export LD=$"/usr/local/x86_64-linux-musl/bin/x86_64-linux-musl-ld"

export CFLAGS=-I$(readlink -f ./toolchain/usr/include)
export LDFLAGS=-L$(readlink -f ./toolchain/usr/lib)
export PATH=$PATH:$(readlink -f ./toolchain/usr/bin)

export BOOST_INCLUDE_PATH=$LIBS/include
export BDB_INCLUDE_PATH=$LIBS/include
export OPENSSL_INCLUDE_PATH=$LIBS/include
export BOOST_LIB_PATH=$LIBS/lib
export BDB_LIB_PATH=$LIBS/lib
export OPENSSL_LIB_PATH=$LIBS/lib

cd src/
make STATIC=all -f makefile.unix-musl
