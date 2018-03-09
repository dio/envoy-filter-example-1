#include <string>

#include "common/http/filter/transcoder/example/filter.h"

#include "server/config/network/http_connection_manager.h"

namespace Envoy {
namespace Http {

ExampleTranscoderFilterConfig::ExampleTranscoderFilterConfig(
    const my::api::v1::transcoder::Example& proto_config)
    : key_(proto_config.key()), val_(proto_config.val()) {}

ExampleTranscoderFilter::ExampleTranscoderFilter(ExampleTranscoderFilterConfigSharedPtr config)
    : config_(config) {}

ExampleTranscoderFilter::~ExampleTranscoderFilter() {}

void ExampleTranscoderFilter::onDestroy() {}

const LowerCaseString ExampleTranscoderFilter::headerKey() const {
  return LowerCaseString(config_->key());
}

const std::string ExampleTranscoderFilter::headerValue() const { return config_->val(); }

FilterHeadersStatus ExampleTranscoderFilter::decodeHeaders(HeaderMap& headers, bool) {
  // add a header
  headers.addCopy(headerKey(), headerValue());

  return FilterHeadersStatus::Continue;
}

FilterDataStatus ExampleTranscoderFilter::decodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus ExampleTranscoderFilter::decodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}

void ExampleTranscoderFilter::setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) {
  decoder_callbacks_ = &callbacks;
}

FilterHeadersStatus ExampleTranscoderFilter::encodeHeaders(HeaderMap& headers, bool) {
  // add a header
  headers.addCopy(headerKey(), headerValue());

  return FilterHeadersStatus::Continue;
}

FilterHeadersStatus ExampleTranscoderFilter::encode100ContinueHeaders(HeaderMap&) {
  return FilterHeadersStatus::Continue;
}

FilterDataStatus ExampleTranscoderFilter::encodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus ExampleTranscoderFilter::encodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}

void ExampleTranscoderFilter::setEncoderFilterCallbacks(StreamEncoderFilterCallbacks& callbacks) {
  encoder_callbacks_ = &callbacks;
}

} // namespace Http
} // namespace Envoy