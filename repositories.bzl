load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def com_google_protobuf():
    protobuf_version = "23.4"
    protobuf_sha = "2c6a36c7b5a55accae063667ef3c55f2642e67476d96d355ff0acb13dbb47f09"

    http_archive(
        name = "com_google_protobuf",
        #        sha256 = protobuf_sha,
        strip_prefix = "protobuf-%s" % protobuf_version,
        urls = ["https://github.com/protocolbuffers/protobuf/releases/download/v%s/protobuf-all-%s.tar.gz" % (protobuf_version, protobuf_version)],
    )

def com_github_grpc_grpc():
    GRPC_VERSION = "1.56.2"
    http_archive(
        name = "com_github_grpc_grpc",
        #        sha256 = "4b64cbc454cc4fd0801a2823111e1d99f519c765dfa116905740f7ca2256d085",
        strip_prefix = "grpc-%s" % GRPC_VERSION,
        url = "https://github.com/grpc/grpc/archive/v%s.zip" % GRPC_VERSION,
    )

def linuxcnc_git():
    LINUXCNC_VERSION = "2.9"

    http_archive(
        name = "linuxcnc",
        build_file = "//third_party/linuxcnc/BUILD",
        strip_prefix = "linuxcnc_%s" % LINUXCNC_VERSION,
        url = "https://github.com/LinuxCNC/linuxcnc/archive/refs/heads/%s.zip" % LINUXCNC_VERSION,
    )

def linuxcnc_local():
    native.new_local_repository(
        name = "linuxcnc",
        path = "/home/dragos/Apps/linuxcnc",
        build_file = "third_party/linuxcnc/BUILD",
    )

def linuxcnc_proto():
    http_archive(
        name = "linuxcnc_proto",
        strip_prefix = "linuxcnc-proto-cleanup",
        url = "https://github.com/dragossusi/linuxcnc-proto/archive/refs/heads/cleanup.zip",
    )
