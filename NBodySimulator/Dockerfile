FROM gcc:14.1 AS builder

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    rsync

COPY . .
RUN make VERBOSE=1

FROM gcc:14.1

COPY --from=builder /build/nbodysimapp /usr/local/bin

CMD ["nbodysimapp"]