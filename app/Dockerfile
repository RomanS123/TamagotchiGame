# Use an official C++ runtime as a parent image
FROM ubuntu:20.04

# Set the working directory in the container
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Update the package list and install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    libpq-dev \
    libpqxx-dev \
    cmake \
    g++ \
	python3

# Create the build directory if it doesn't exist
RUN mkdir -p build

# Set the working directory to /app/build
WORKDIR /app/build

# Run CMake and Make to build the application
RUN cmake ..
RUN make

# Change directory to /app/bin
WORKDIR /app/bin

# Run the executable from the bin directory
CMD ["./main"]
