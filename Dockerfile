FROM gcc:4.9
COPY "./dockerTest/" /usr/src/testProgram/
WORKDIR /usr/src/testProgram/
RUN make
CMD ["./testProgram"]
