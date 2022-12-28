load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# For use with maven_install's artifacts.
# maven_install(
#     ...
#     artifacts = [
#         # Your own deps
#     ] + IO_GRPC_GRPC_KOTLIN_ARTIFACTS + IO_GRPC_GRPC_JAVA_ARTIFACTS,
# )
IO_GRPC_GRPC_KOTLIN_ARTIFACTS = [
    "com.google.guava:guava:30.1.1-android",
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

#    if not native.existing_rule("com_github_grpc_grpc"):
#        com_github_grpc_grpc()

def io_bazel_rules_kotlin():
    rules_kotlin_version = "1.7.0"
    rules_kotlin_sha = "15afe2d727f0dba572e0ce58f1dac20aec1441422ca65f7c3f7671b47fd483bf"
    http_archive(
        name = "io_bazel_rules_kotlin",
        urls = ["https://github.com/bazelbuild/rules_kotlin/releases/download/%s/rules_kotlin_release.tgz" % rules_kotlin_version],
        sha256 = rules_kotlin_sha,
    )

def com_google_protobuf():
    protobuf_version = "21.12"
    protobuf_sha = "2c6a36c7b5a55accae063667ef3c55f2642e67476d96d355ff0acb13dbb47f09"

    http_archive(
        name = "com_google_protobuf",
        sha256 = protobuf_sha,
        strip_prefix = "protobuf-%s" % protobuf_version,
        urls = ["https://github.com/protocolbuffers/protobuf/releases/download/v%s/protobuf-all-%s.tar.gz" % (protobuf_version, protobuf_version)],
    )

def io_grpc_grpc_java():
    http_archive(
        name = "io_grpc_grpc_java",
        sha256 = "75e5994ca18ae3ffaf67a2f08d0274215916b0ff56d62e9e5b447095e622714b",
        strip_prefix = "grpc-java-%s" % GRPC_VERSION,
        url = "https://github.com/grpc/grpc-java/archive/v%s.zip" % GRPC_VERSION,
    )

def com_github_grpc_grpc():
    http_archive(
        name = "com_github_grpc_grpc",
        sha256 = "4b64cbc454cc4fd0801a2823111e1d99f519c765dfa116905740f7ca2256d085",
        strip_prefix = "grpc-%s" % GRPC_VERSION,
        url = "https://github.com/grpc/grpc/archive/v%s.zip" % GRPC_VERSION,
    )
