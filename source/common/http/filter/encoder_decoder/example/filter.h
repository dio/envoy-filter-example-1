#pragma once

#include <string>

#include "server/config/network/http_connection_manager.h"

#include "source/common/http/filter/encoder_decoder/example/filter.pb.h"

namespace Envoy {
namespace Http {

class ExampleEncoderDecoderFilterConfig {
public:
  ExampleEncoderDecoderFilterConfig(
      const my::api::v1::encoder_decoder::Example& proto_config);

  const std::string& key() const { return key_; }
  const std::string& val() const { return val_; }

private:
  const std::string key_;
  const std::string val_;
};

typedef std::shared_ptr<ExampleEncoderDecoderFilterConfig> ExampleEncoderDecoderFilterConfigSharedPtr;

class ExampleEncoderDecoderFilter : public StreamFilter {
public:
  ExampleEncoderDecoderFilter(ExampleEncoderDecoderFilterConfigSharedPtr);
  ~ExampleEncoderDecoderFilter();

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
  const ExampleEncoderDecoderFilterConfigSharedPtr config_;
  StreamDecoderFilterCallbacks* decoder_callbacks_;
  StreamEncoderFilterCallbacks* encoder_callbacks_;

  const LowerCaseString headerKey() const;
  const std::string headerValue() const;
};

} // namespace Http
} // namespace Envoy