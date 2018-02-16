#include <string>

#include "http/decoder/json_to_xml/filter.h"

#include "server/config/network/http_connection_manager.h"

#include "rapidxml.hpp"

namespace Envoy {
namespace Http {

JsonToXmlDecoderFilterConfig::JsonToXmlDecoderFilterConfig(
    const example::api::v1::decoder::JsonToXml& proto_config)
    : key_(proto_config.key()), val_(proto_config.val()) {}

JsonToXmlDecoderFilter::JsonToXmlDecoderFilter(JsonToXmlDecoderFilterConfigSharedPtr config)
    : config_(config) {}

JsonToXmlDecoderFilter::~JsonToXmlDecoderFilter() {}

void JsonToXmlDecoderFilter::onDestroy() {}

const LowerCaseString JsonToXmlDecoderFilter::headerKey() const {
  return LowerCaseString(config_->key());
}

const std::string JsonToXmlDecoderFilter::headerValue() const { return config_->val(); }

FilterHeadersStatus JsonToXmlDecoderFilter::decodeHeaders(HeaderMap& headers, bool) {
  // add a header
  headers.addCopy(headerKey(), headerValue());

  return FilterHeadersStatus::Continue;
}

FilterDataStatus JsonToXmlDecoderFilter::decodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus JsonToXmlDecoderFilter::decodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}

void JsonToXmlDecoderFilter::setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) {
  decoder_callbacks_ = &callbacks;
}

FilterHeadersStatus JsonToXmlDecoderFilter::encodeHeaders(HeaderMap&, bool) {
  return FilterHeadersStatus::Continue;
}

FilterHeadersStatus JsonToXmlDecoderFilter::encode100ContinueHeaders(HeaderMap&) {
  return FilterHeadersStatus::Continue;
}

FilterDataStatus JsonToXmlDecoderFilter::encodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus JsonToXmlDecoderFilter::encodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}

void JsonToXmlDecoderFilter::setEncoderFilterCallbacks(StreamEncoderFilterCallbacks& callbacks) {
  encoder_callbacks_ = &callbacks;
}

} // namespace Http
} // namespace Envoy