#!/usr/bin/sh
protoc -I ./proto --grpc_out=./proto --plugin=protoc-gen-grpc=`which grpc_cpp_plugin`  proto/linuxcnc.proto
protoc -I ./proto --cpp_out=./proto proto/linuxcnc.proto