Docker build/run

This project includes a Dockerfile to build and run the SimuRide++ binary inside a container. Use this if you don't want to install CMake or a C++ toolchain locally.

Build the image (from project root):

```powershell
docker build -t simuride .
```

Run the container (it will execute the sample `simuride` binary):

```powershell
docker run --rm simuride
```

Notes:
- The Docker image uses Ubuntu 22.04 and installs build-essential and cmake. The build occurs during image build, so the first step may take a few minutes.
- CI uses a similar flow to build and exercise the binary inside a container.
