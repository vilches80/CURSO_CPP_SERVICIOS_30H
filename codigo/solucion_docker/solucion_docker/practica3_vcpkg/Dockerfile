# Stage 1: Build

# partimos de una imagen ya hecha
FROM mcr.microsoft.com/devcontainers/cpp:ubuntu-22.04 AS builder

# Establecer la carpeta de trabajo:
WORKDIR /src

# Copiar el proyecto completo:
COPY . .

# Instalar dependencias declaradas en vcpkg.json
RUN vcpkg install --triplet x64-linux

# Configurar y compilar con CMake usando el toolchain de vcpkg
RUN cmake -B build -S . \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE=/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake

RUN cmake --build build --config Release


###################################################################

# Stage 2: Runtime

# Nos basamos en el S.O. Ubuntu
FROM ubuntu:22.04

# Establecer la carpeta de trabajo:
WORKDIR /app

# Solo copiamos el binario final:
COPY  --from=builder /src/build/practica3_vcpkg .

# Ejecutar el binario:
CMD ["./practica3_vcpkg"]
