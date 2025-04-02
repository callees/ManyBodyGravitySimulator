FROM golang:latest AS builder

WORKDIR /app
COPY . .
RUN make build

FROM golang:latest

WORKDIR /app
COPY --from=builder /app/build/* .
EXPOSE 6969

ENTRYPOINT ["/app/webservice"]