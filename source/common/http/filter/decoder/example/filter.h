#pragma once

#include <string>

#include "server/config/network/http_connection_manager.h"

#include "source/common/http/filter/decoder/example/filter.pb.h"

namespace Envoy {
namespace Http {

class ExampleDecoderFilterConfig {
public:
  ExampleDecoderFilterConfig(const my::api::v1::decoder::Example& proto_config);

  const std::string& key() const { return key_; }
  const std::string& val() const { return val_; }

private:
  const std::string key_;
  const std::string val_;
};

typedef std::shared_ptr<ExampleDecoderFilterConfig> ExampleDecoderFilterConfigSharedPtr;

class ExampleDecoderFilter : public StreamDecoderFilter {
public:
  ExampleDecoderFilter(ExampleDecoderFilterConfigSharedPtr);
  ~ExampleDecoderFilter();

  // Http::StreamFilterBase
  void onDestroy() override;

  // Http::StreamDecoderFilter
  FilterHeadersStatus decodeHeaders(HeaderMap&, bool) override;
  FilterDataStatus decodeData(Buffer::Instance&, bool) override;
  FilterTrailersStatus decodeTrailers(HeaderMap&) override;
  void setDecoderFilterCallbacks(StreamDecoderFilterCallbacks&) override;

private:
  const ExampleDecoderFilterConfigSharedPtr config_;
  StreamDecoderFilterCallbacks* decoder_callbacks_;

  const LowerCaseString headerKey() const;
  const std::string headerValue() const;
};

} // namespace Http
} // namespace Envoy