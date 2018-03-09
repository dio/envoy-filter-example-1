#include <string>

#include "common/http/filter/encoder_decoder/example/filter.h"

#include "server/config/network/http_connection_manager.h"

namespace Envoy {
namespace Http {

ExampleEncoderDecoderFilterConfig::ExampleEncoderDecoderFilterConfig(
    const my::api::v1::encoder_decoder::Example& proto_config)
    : key_(proto_config.key()), val_(proto_config.val()) {}

ExampleEncoderDecoderFilter::ExampleEncoderDecoderFilter(ExampleEncoderDecoderFilterConfigSharedPtr config)
    : config_(config) {}

ExampleEncoderDecoderFilter::~ExampleEncoderDecoderFilter() {}

void ExampleEncoderDecoderFilter::onDestroy() {}

const LowerCaseString ExampleEncoderDecoderFilter::headerKey() const {
  return LowerCaseString(config_->key());
}

const std::string ExampleEncoderDecoderFilter::headerValue() const { return config_->val(); }

FilterHeadersStatus ExampleEncoderDecoderFilter::decodeHeaders(HeaderMap& headers, bool) {
  // add a header
  headers.addCopy(headerKey(), headerValue());

  return FilterHeadersStatus::Continue;
}

FilterDataStatus ExampleEncoderDecoderFilter::decodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus ExampleEncoderDecoderFilter::decodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}

void ExampleEncoderDecoderFilter::setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) {
  decoder_callbacks_ = &callbacks;
}

FilterHeadersStatus ExampleEncoderDecoderFilter::encodeHeaders(HeaderMap& headers, bool) {
  // add a header
  headers.addCopy(headerKey(), headerValue());

  return FilterHeadersStatus::Continue;
}

FilterHeadersStatus ExampleEncoderDecoderFilter::encode100ContinueHeaders(HeaderMap&) {
  return FilterHeadersStatus::Continue;
}

FilterDataStatus ExampleEncoderDecoderFilter::encodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus ExampleEncoderDecoderFilter::encodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}

void ExampleEncoderDecoderFilter::setEncoderFilterCallbacks(StreamEncoderFilterCallbacks& callbacks) {
  encoder_callbacks_ = &callbacks;
}

} // namespace Http
} // namespace Envoy