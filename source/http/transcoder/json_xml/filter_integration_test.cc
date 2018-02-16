#include "test/integration/http_integration.h"
#include "test/integration/utility.h"

namespace Envoy {
class JsonXmlTranscoderFilterIntegrationTest
    : public HttpIntegrationTest,
      public testing::TestWithParam<Network::Address::IpVersion> {
public:
  JsonXmlTranscoderFilterIntegrationTest()
      : HttpIntegrationTest(Http::CodecClient::Type::HTTP1, GetParam()) {}

  void SetUp() override { initialize(); }

  void initialize() override {
    config_helper_.addFilter(
        "{ name: json_xml, config: { key: via, val: json-xml } }");
    HttpIntegrationTest::initialize();
  }
};

INSTANTIATE_TEST_CASE_P(IpVersions, JsonXmlTranscoderFilterIntegrationTest,
                        testing::ValuesIn(TestEnvironment::getIpVersionsForTest()));

TEST_P(JsonXmlTranscoderFilterIntegrationTest, Test1) {
  Http::TestHeaderMapImpl headers{{":method", "GET"}, {":path", "/"}, {":authority", "host"}};

  IntegrationCodecClientPtr codec_client;
  FakeHttpConnectionPtr fake_upstream_connection;
  IntegrationStreamDecoderPtr response(new IntegrationStreamDecoder(*dispatcher_));
  FakeStreamPtr request_stream;

  codec_client = makeHttpConnection(lookupPort("http"));
  codec_client->makeHeaderOnlyRequest(headers, *response);
  fake_upstream_connection = fake_upstreams_[0]->waitForHttpConnection(*dispatcher_);
  request_stream = fake_upstream_connection->waitForNewStream(*dispatcher_);
  request_stream->waitForEndStream(*dispatcher_);
  response->waitForEndStream();

  EXPECT_STREQ("json-xml",
               request_stream->headers().get(Http::LowerCaseString("via"))->value().c_str());

  codec_client->close();
}
} // namespace Envoy