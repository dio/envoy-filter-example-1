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
        "//source/http/decoder/json_to_xml:filter_config",
        "//source/http/encoder/xml_to_json:filter_config",
        "//source/http/transcoder/json_xml:filter_config",
        "@envoy//source/exe:envoy_main_entry_lib",
    ],
)
