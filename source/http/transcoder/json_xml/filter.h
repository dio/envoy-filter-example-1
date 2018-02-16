#pragma once

#include <string>

#include "server/config/network/http_connection_manager.h"

#include "source/http/transcoder/json_xml/filter.pb.h"

namespace Envoy {
namespace Http {

class JsonXmlTranscoderFilterConfig {
public:
  JsonXmlTranscoderFilterConfig(
      const example::api::v1::transcoder::JsonXml& proto_config);

  const std::string& key() const { return key_; }
  const std::string& val() const { return val_; }

private:
  const std::string key_;
  const std::string val_;
};

typedef std::shared_ptr<JsonXmlTranscoderFilterConfig> JsonXmlTranscoderFilterConfigSharedPtr;

class JsonXmlTranscoderFilter : public StreamFilter {
public:
  JsonXmlTranscoderFilter(JsonXmlTranscoderFilterConfigSharedPtr);
  ~JsonXmlTranscoderFilter();

  // Http::StreamFilterBase
  void onDestroy() override;

  // Http::StreamDecoderFilter
  FilterHeadersStatus decodeHeaders(HeaderMap&, bool) override;
  FilterDataStatus decodeData(Buffer::Instance&, bool) override;
  FilterTrailersStatus decodeTrailers(HeaderMap&) override;
  void setDecoderFilterCallbacks(StreamDecoderFilterCallbacks&) override;

  // Http::StreamEncoderFilter
  FilterHeadersStatus encodeHeaders(HeaderMap&, bool) override;
  FilterHeadersStatus encode100ContinueHeaders(HeaderMap& headers) override;
  FilterDataStatus encodeData(Buffer::Instance&, bool) override;
  FilterTrailersStatus encodeTrailers(HeaderMap&) override;
  void setEncoderFilterCallbacks(StreamEncoderFilterCallbacks&) override;

private:
  const JsonXmlTranscoderFilterConfigSharedPtr config_;
  StreamDecoderFilterCallbacks* decoder_callbacks_;
  StreamEncoderFilterCallbacks* encoder_callbacks_;

  const LowerCaseString headerKey() const;
  const std::string headerValue() const;
};

} // namespace Http
} // namespace Envoy