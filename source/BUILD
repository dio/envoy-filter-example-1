package(default_visibility = ["//visibility:public"])

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_binary",
)

load("@envoy_api//bazel:api_build_system.bzl", "api_proto_library")

envoy_cc_binary(
    name = "envoy",
    repository = "@envoy",
    deps = [
        "//source/common/http/filter/decoder/example:filter_config",
        "//source/common/http/filter/encoder/example:filter_config",
        "//source/common/http/filter/encoder_decoder/example:filter_config",
        "@envoy//source/exe:envoy_main_entry_lib",
    ],
)
