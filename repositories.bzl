load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def com_github_grpc_grpc():
    GRPC_VERSION = "1.66.0"
    http_archive(
        name = "com_github_grpc_grpc",
        strip_prefix = "grpc-%s" % GRPC_VERSION,
        url = "https://github.com/grpc/grpc/archive/refs/tags/v%s.zip" % GRPC_VERSION,
    )

def linuxcnc_git():
    LINUXCNC_VERSION = "2.9.2"

    http_archive(
        name = "linuxcnc",
        build_file = "//third_party/linuxcnc/BUILD.bazel",
        strip_prefix = "linuxcnc_%s" % LINUXCNC_VERSION,
        url = "https://github.com/LinuxCNC/linuxcnc/archive/refs/heads/%s.zip" % LINUXCNC_VERSION,
    )

def linuxcnc_local():
    native.new_local_repository(
        name = "linuxcnc",
        path = "/home/dragos/Apps/linuxcnc",
        build_file = "//third_party/linuxcnc:BUILD.bazel",
    )

def linuxcnc_proto():
    BRANCH = "main"
    http_archive(
        name = "linuxcnc_proto",
        strip_prefix = "linuxcnc-proto-%s" % BRANCH,
        url = "https://github.com/dragossusi/linuxcnc-proto/archive/refs/heads/%s.zip" % BRANCH,
    )
