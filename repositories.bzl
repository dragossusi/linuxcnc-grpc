load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def com_github_grpc_grpc():
    GRPC_VERSION = "1.60.0"
    http_archive(
        name = "com_github_grpc_grpc",
        sha256 = "09640607a340ff0d97407ed22fe4adb177e5bb85329821122084359cd57c3dea",
        strip_prefix = "grpc-%s" % GRPC_VERSION,
        url = "https://github.com/grpc/grpc/archive/refs/tags/v%s.zip" % GRPC_VERSION,
    )

def linuxcnc_git():
    LINUXCNC_VERSION = "2.9.2"

    http_archive(
        name = "linuxcnc",
        build_file = "//third_party/linuxcnc/BUILD.bazel.bazel",
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
        strip_prefix = "linuxcnc-proto-main",
        url = "https://github.com/dragossusi/linuxcnc-proto/archive/refs/heads/main.zip",
    )
