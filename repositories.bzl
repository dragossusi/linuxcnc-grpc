load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# For use with maven_install's artifacts.
# maven_install(
#     ...
#     artifacts = [
#         # Your own deps
#     ] + IO_GRPC_GRPC_KOTLIN_ARTIFACTS + IO_GRPC_GRPC_JAVA_ARTIFACTS,
# )
IO_GRPC_GRPC_KOTLIN_ARTIFACTS = [
    "com.google.guava:guava:31.1-android",
    "com.squareup:kotlinpoet:1.12.0",
    "org.jetbrains.kotlinx:kotlinx-coroutines-core:1.6.4",
    "org.jetbrains.kotlinx:kotlinx-coroutines-core-jvm:1.6.4",
    "org.jetbrains.kotlinx:kotlinx-coroutines-debug:1.6.4",
]

# For use with maven_install's override_targets.
# maven_install(
#     ...
#     override_targets = dict(
#         IO_GRPC_GRPC_JAVA_OVERRIDE_TARGETS.items() +
#         IO_GRPC_GRPC_KOTLIN_OVERRIDE_TARGETS.items(),
#         "your.target:artifact": "@//third_party/artifact",
#     )
IO_GRPC_GRPC_KOTLIN_OVERRIDE_TARGETS = dict()

GRPC_VERSION = "1.51.1"

# Call this after compat_repositories() to load all dependencies.
def grpc_kt_repositories():
    """Imports dependencies for kt_jvm_grpc.bzl"""
    if not native.existing_rule("io_bazel_rules_kotlin"):
        io_bazel_rules_kotlin()
    if not native.existing_rule("com_google_protobuf"):
        com_google_protobuf()
    if not native.existing_rule("io_grpc_grpc_java"):
        io_grpc_grpc_java()

def rules_jvm_external():
    jvm_external_version = "4.5"
    jvm_external_sha = "b17d7388feb9bfa7f2fa09031b32707df529f26c91ab9e5d909eb1676badd9a6"
    http_archive(
        name = "rules_jvm_external",
        sha256 = jvm_external_sha,
        strip_prefix = "rules_jvm_external-4.5",
        url = "https://github.com/bazelbuild/rules_jvm_external/archive/%s.zip" % jvm_external_version,
    )

def io_bazel_rules_kotlin():
    rules_kotlin_version = "1.8"
    rules_kotlin_sha = "01293740a16e474669aba5b5a1fe3d368de5832442f164e4fbfc566815a8bc3a"
    http_archive(
        name = "io_bazel_rules_kotlin",
        urls = ["https://github.com/bazelbuild/rules_kotlin/releases/download/v%s/rules_kotlin_release.tgz" % rules_kotlin_version],
        sha256 = rules_kotlin_sha,
    )

def com_google_protobuf():
    protobuf_version = "23.4"
    protobuf_sha = "2c6a36c7b5a55accae063667ef3c55f2642e67476d96d355ff0acb13dbb47f09"

    http_archive(
        name = "com_google_protobuf",
        #        sha256 = protobuf_sha,
        strip_prefix = "protobuf-%s" % protobuf_version,
        urls = ["https://github.com/protocolbuffers/protobuf/releases/download/v%s/protobuf-all-%s.tar.gz" % (protobuf_version, protobuf_version)],
    )

def com_github_grpc_grpc_kotlin():
    grpc_kotlin_version = "1.3.0"

    http_archive(
        name = "com_github_grpc_grpc_kotlin",
        strip_prefix = "grpc-kotlin-%s" % grpc_kotlin_version,
        urls = ["https://github.com/grpc/grpc-kotlin/archive/refs/tags/v%s.tar.gz" % (grpc_kotlin_version)],
    )

def io_grpc_grpc_java():
    http_archive(
        name = "io_grpc_grpc_java",
        #        sha256 = "75e5994ca18ae3ffaf67a2f08d0274215916b0ff56d62e9e5b447095e622714b",
        strip_prefix = "grpc-java-%s" % GRPC_VERSION,
        url = "https://github.com/grpc/grpc-java/archive/v%s.zip" % GRPC_VERSION,
    )

def com_github_grpc_grpc():
    http_archive(
        name = "com_github_grpc_grpc",
        #        sha256 = "4b64cbc454cc4fd0801a2823111e1d99f519c765dfa116905740f7ca2256d085",
        strip_prefix = "grpc-%s" % GRPC_VERSION,
        url = "https://github.com/grpc/grpc/archive/v%s.zip" % GRPC_VERSION,
    )

def rules_foreign_cc():
    FOREIGN_CC_VERSION = "0.9.0"

    http_archive(
        name = "rules_foreign_cc",
        sha256 = "2a4d07cd64b0719b39a7c12218a3e507672b82a97b98c6a89d38565894cf7c51",
        strip_prefix = "rules_foreign_cc-%s" % FOREIGN_CC_VERSION,
        url = "https://github.com/bazelbuild/rules_foreign_cc/archive/refs/tags/%s.tar.gz" % FOREIGN_CC_VERSION,
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
        strip_prefix = "linuxcnc-proto-main",
        url = "https://github.com/dragossusi/linuxcnc-proto/archive/refs/heads/main.zip",
    )
