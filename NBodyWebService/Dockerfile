FROM golang:latest AS builder

WORKDIR /api
COPY . .
RUN make build

FROM golang:latest

WORKDIR /api
COPY --from=builder /api/build/* .
EXPOSE 6969

ENTRYPOINT ["/api/webservice"]