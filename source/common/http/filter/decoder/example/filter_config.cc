#include <string>

#include "common/http/filter/decoder/example/filter.h"

#include "common/config/json_utility.h"
#include "envoy/registry/registry.h"

#include "source/common/http/filter/decoder/example/filter.pb.h"
#include "source/common/http/filter/decoder/example/filter.pb.validate.h"

namespace Envoy {
namespace Server {
namespace Configuration {

class ExampleDecoderFilterConfig : public NamedHttpFilterConfigFactory {
public:
  HttpFilterFactoryCb createFilterFactory(const Json::Object& json_config, const std::string&,
                                          FactoryContext& context) override {

    my::api::v1::decoder::Example proto_config;
    translate(json_config, proto_config);

    return createFilter(proto_config, context);
  }

  HttpFilterFactoryCb createFilterFactoryFromProto(const Protobuf::Message& proto_config,
                                                   const std::string&,
                                                   FactoryContext& context) override {

    return createFilter(
        Envoy::MessageUtil::downcastAndValidate<const my::api::v1::decoder::Example&>(
            proto_config),
        context);
  }

  ProtobufTypes::MessagePtr createEmptyConfigProto() override {
    return ProtobufTypes::MessagePtr{new my::api::v1::decoder::Example()};
  }

  std::string name() override { return "my.decoder.example"; }

private:
  HttpFilterFactoryCb createFilter(const my::api::v1::decoder::Example& proto_config,
                                   FactoryContext& context) {

    Http::ExampleDecoderFilterConfigSharedPtr config =
        std::make_shared<Http::ExampleDecoderFilterConfig>(
            Http::ExampleDecoderFilterConfig(proto_config));

    return [&context, config](Http::FilterChainFactoryCallbacks& callbacks) -> void {
      auto filter = new Http::ExampleDecoderFilter(config);
      callbacks.addStreamDecoderFilter(Http::StreamDecoderFilterSharedPtr{filter});
    };
  }

  void translate(const Json::Object& json_config,
                 my::api::v1::decoder::Example& proto_config) {

    // normally we want to validate the json_config againts a defined
    // json-schema here.
    JSON_UTIL_SET_STRING(json_config, proto_config, key);
    JSON_UTIL_SET_STRING(json_config, proto_config, val);
  }
};

static Registry::RegisterFactory<ExampleDecoderFilterConfig, NamedHttpFilterConfigFactory>
    register_;

} // namespace Configuration
} // namespace Server
} // namespace Envoy