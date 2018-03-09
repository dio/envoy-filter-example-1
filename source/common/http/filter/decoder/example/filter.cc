#include <string>

#include "common/http/filter/decoder/example/filter.h"

#include "server/config/network/http_connection_manager.h"

namespace Envoy {
namespace Http {

ExampleDecoderFilterConfig::ExampleDecoderFilterConfig(
    const my::api::v1::decoder::Example& proto_config)
    : key_(proto_config.key()), val_(proto_config.val()) {}

ExampleDecoderFilter::ExampleDecoderFilter(ExampleDecoderFilterConfigSharedPtr config)
    : config_(config) {}

ExampleDecoderFilter::~ExampleDecoderFilter() {}

void ExampleDecoderFilter::onDestroy() {}

const LowerCaseString ExampleDecoderFilter::headerKey() const {
  return LowerCaseString(config_->key());
}

const std::string ExampleDecoderFilter::headerValue() const { return config_->val(); }

FilterHeadersStatus ExampleDecoderFilter::decodeHeaders(HeaderMap& headers, bool) {
  // add a header
  headers.addCopy(headerKey(), headerValue());

  return FilterHeadersStatus::Continue;
}

FilterDataStatus ExampleDecoderFilter::decodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus ExampleDecoderFilter::decodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}

void ExampleDecoderFilter::setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) {
  decoder_callbacks_ = &callbacks;
}

} // namespace Http
} // namespace Envoy