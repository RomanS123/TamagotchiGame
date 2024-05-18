# Use an official C++ runtime as a parent image
FROM gcc:latest

# Set the working directory in the container
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Install any needed packages specified in requirements.txt
RUN apt-get update && apt-get install -y \
    libpq-dev \
    cmake \
    make \
    && rm -rf /var/lib/apt/lists/*

# Run cmake and make to build the C++ application
RUN cmake . && make

# Make port 8080 available to the world outside this container
EXPOSE 8080

# Run the executable
CMD ["./bin/main"]
