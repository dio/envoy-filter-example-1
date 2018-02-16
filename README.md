## envoy filter example

This project currently focuses on providing http filter examples, in two types
of it:

#### sync

1. decoder, `client{send:json} -> filter -> {recv:xml}upstream`
2. encoder, `client{send:json} <- filter <- {recv:xml}upstream`
3. transcoder, `client{send:json} <-> filter <-> {recv:xml}upstream`

#### async

1. http auth, follow the behavior of [ngx_http_auth_request_module](http://nginx.org/en/docs/http/ngx_http_auth_request_module.html)

### building

1. get envoy
2. bazel


### testing

1. manual, by config examples
2. bazel
