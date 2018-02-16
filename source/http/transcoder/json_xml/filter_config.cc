#include <string>

#include "http/transcoder/json_xml/filter.h"

#include "common/config/json_utility.h"
#include "envoy/registry/registry.h"

#include "source/http/transcoder/json_xml/filter.pb.h"
#include "source/http/transcoder/json_xml/filter.pb.validate.h"

namespace Envoy {
namespace Server {
namespace Configuration {

class JsonXmlTranscoderFilterConfig : public NamedHttpFilterConfigFactory {
public:
  HttpFilterFactoryCb createFilterFactory(const Json::Object& json_config, const std::string&,
                                          FactoryContext& context) override {

    example::api::v1::transcoder::JsonXml proto_config;
    translate(json_config, proto_config);

    return createFilter(proto_config, context);
  }

  HttpFilterFactoryCb createFilterFactoryFromProto(const Protobuf::Message& proto_config,
                                                   const std::string&,
                                                   FactoryContext& context) override {

    return createFilter(Envoy::MessageUtil::downcastAndValidate<
                            const example::api::v1::transcoder::JsonXml&>(proto_config),
                        context);
  }

  ProtobufTypes::MessagePtr createEmptyConfigProto() override {
    return ProtobufTypes::MessagePtr{new example::api::v1::transcoder::JsonXml()};
  }

  std::string name() override { return "json_xml"; }

private:
  HttpFilterFactoryCb
  createFilter(const example::api::v1::transcoder::JsonXml& proto_config,
               FactoryContext& context) {

    Http::JsonXmlTranscoderFilterConfigSharedPtr config =
        std::make_shared<Http::JsonXmlTranscoderFilterConfig>(
            Http::JsonXmlTranscoderFilterConfig(proto_config));

    return [&context, config](Http::FilterChainFactoryCallbacks& callbacks) -> void {
      auto filter = new Http::JsonXmlTranscoderFilter(config);
      callbacks.addStreamFilter(Http::StreamFilterSharedPtr{filter});
    };
  }

  void
  translate(const Json::Object& json_config,
                                   example::api::v1::transcoder::JsonXml& proto_config) {

    // normally we want to validate the json_config againts a defined
    // json-schema here.
    JSON_UTIL_SET_STRING(json_config, proto_config, key);
    JSON_UTIL_SET_STRING(json_config, proto_config, val);
  }
};

static Registry::RegisterFactory<JsonXmlTranscoderFilterConfig, NamedHttpFilterConfigFactory>
    register_;

} // namespace Configuration
} // namespace Server
} // namespace Envoy