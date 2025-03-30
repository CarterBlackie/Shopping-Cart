FROM ubuntu:latest

# Install dependencies
RUN apt-get update && \
    apt-get install -y g++ cmake libboost-all-dev git python3 wget libasio-dev

# Set working directory
WORKDIR /usr/src/app

# Copy project files
COPY . .

# Clone Crow and generate crow_all.h
RUN git clone https://github.com/CrowCpp/Crow.git
RUN python3 Crow/scripts/merge_all.py Crow/include crow_all.h

# Make include folder and move crow_all.h there
RUN mkdir -p /usr/src/app/include
RUN cp crow_all.h /usr/src/app/include/

# Build the app
RUN cmake . && make

# Run the app
CMD ["./your_app"]
