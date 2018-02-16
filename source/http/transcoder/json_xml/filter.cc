#include <string>

#include "http/transcoder/json_xml/filter.h"

#include "server/config/network/http_connection_manager.h"

#include "rapidxml.hpp"

namespace Envoy {
namespace Http {

JsonXmlTranscoderFilterConfig::JsonXmlTranscoderFilterConfig(
    const example::api::v1::transcoder::JsonXml& proto_config)
    : key_(proto_config.key()), val_(proto_config.val()) {}

JsonXmlTranscoderFilter::JsonXmlTranscoderFilter(JsonXmlTranscoderFilterConfigSharedPtr config)
    : config_(config) {}

JsonXmlTranscoderFilter::~JsonXmlTranscoderFilter() {}

void JsonXmlTranscoderFilter::onDestroy() {}

const LowerCaseString JsonXmlTranscoderFilter::headerKey() const {
  return LowerCaseString(config_->key());
}

const std::string JsonXmlTranscoderFilter::headerValue() const { return config_->val(); }

FilterHeadersStatus JsonXmlTranscoderFilter::decodeHeaders(HeaderMap& headers, bool) {
  // add a header
  headers.addCopy(headerKey(), headerValue());

  return FilterHeadersStatus::Continue;
}

FilterDataStatus JsonXmlTranscoderFilter::decodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus JsonXmlTranscoderFilter::decodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}

void JsonXmlTranscoderFilter::setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) {
  decoder_callbacks_ = &callbacks;
}

FilterHeadersStatus JsonXmlTranscoderFilter::encodeHeaders(HeaderMap&, bool) {
  return FilterHeadersStatus::Continue;
}

FilterHeadersStatus JsonXmlTranscoderFilter::encode100ContinueHeaders(HeaderMap&) {
  return FilterHeadersStatus::Continue;
}

FilterDataStatus JsonXmlTranscoderFilter::encodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus JsonXmlTranscoderFilter::encodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}

void JsonXmlTranscoderFilter::setEncoderFilterCallbacks(StreamEncoderFilterCallbacks& callbacks) {
  encoder_callbacks_ = &callbacks;
}

} // namespace Http
} // namespace Envoy