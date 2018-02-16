#include <string>

#include "http/encoder/xml_to_json/filter.h"

#include "server/config/network/http_connection_manager.h"

#include "rapidxml.hpp"

namespace Envoy {
namespace Http {

XmlToJsonEncoderFilterConfig::XmlToJsonEncoderFilterConfig(
    const example::api::v1::encoder::XmlToJson& proto_config)
    : key_(proto_config.key()), val_(proto_config.val()) {}

XmlToJsonEncoderFilter::XmlToJsonEncoderFilter(XmlToJsonEncoderFilterConfigSharedPtr config)
    : config_(config) {}

XmlToJsonEncoderFilter::~XmlToJsonEncoderFilter() {}

void XmlToJsonEncoderFilter::onDestroy() {}

const LowerCaseString XmlToJsonEncoderFilter::headerKey() const {
  return LowerCaseString(config_->key());
}

const std::string XmlToJsonEncoderFilter::headerValue() const { return config_->val(); }

FilterHeadersStatus XmlToJsonEncoderFilter::decodeHeaders(HeaderMap& headers, bool) {
  // add a header
  headers.addCopy(headerKey(), headerValue());

  return FilterHeadersStatus::Continue;
}

FilterDataStatus XmlToJsonEncoderFilter::decodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus XmlToJsonEncoderFilter::decodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}

void XmlToJsonEncoderFilter::setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) {
  decoder_callbacks_ = &callbacks;
}

FilterHeadersStatus XmlToJsonEncoderFilter::encodeHeaders(HeaderMap&, bool) {
  return FilterHeadersStatus::Continue;
}

FilterHeadersStatus XmlToJsonEncoderFilter::encode100ContinueHeaders(HeaderMap&) {
  return FilterHeadersStatus::Continue;
}

FilterDataStatus XmlToJsonEncoderFilter::encodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus XmlToJsonEncoderFilter::encodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}

void XmlToJsonEncoderFilter::setEncoderFilterCallbacks(StreamEncoderFilterCallbacks& callbacks) {
  encoder_callbacks_ = &callbacks;
}

} // namespace Http
} // namespace Envoy