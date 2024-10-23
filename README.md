## Ray Tracing Project

This project is a ray tracing engine developed in C++, focusing on rendering scenes with realistic lighting and reflections using core principles of ray tracing. It supports various materials and recursive reflections, showcasing how basic geometric shapes like spheres can be rendered in 3D space.

<p align="center">
  <img src="https://github.com/user-attachments/assets/bc23d3b3-5987-4de8-aa84-2da7a895d908" alt="ray tracing output"/>
</p>

### Overview
This ray tracer implements key features including:
- Ray-sphere intersections
- Recursive reflections and refractions for realistic lighting effects
- Support for various materials like diffuse (Lambertian), metal, and dielectric (transparent)
- Anti-aliasing for smoother image quality
- Multi-threaded rendering using OpenMP (available in the `openmp-support` branch)

It was designed to explore the fundamentals of ray tracing, with additional optimizations such as OpenMP for faster performance.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/mirzaim/ray-tracing.git
   cd ray-tracing
   ```

2. Create a `build` folder for the compiled output:
   ```bash
   mkdir build
   ```

3. Use the provided Makefile to compile the project:
   ```bash
   make
   ```

For OpenMP support, switch to the `openmp-support` branch and compile using the same process.

### Usage

Run the ray tracer with the default scene:
```bash
./build/main > image.ppm
```

For a high-quality scene (this takes much longer and uses OpenMP for faster performance):
```bash
./build/main 1 > image.ppm
```

Open the `image.ppm` file with an image viewer to see the rendered result.

### Useful Resources

During the development of this project, I found several resources helpful in understanding ray tracing concepts and improving the implementation. The following is a list of materials I used:

1. [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
2. [The Ray Tracer Challenge](https://pragprog.com/titles/jbtracer/the-ray-tracer-challenge/)
3. [Computer Graphics from Scratch](https://www.gabrielgambetta.com/computer-graphics-from-scratch/)
