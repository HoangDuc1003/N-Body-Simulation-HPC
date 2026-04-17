#include <iostream>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

struct Body {
    float x, y, z;
    float vx, vy, vz;
    float mass;
};

const float G = 6.67430e-11f;
const float SOFTENING = 1e-9f;
const float dt = 0.01f;

__global__ void calculateForces(Body* bodies, int N) {

    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i >= N) return;

    float fx = 0.0f, fy = 0.0f, fz = 0.0f;
    Body my_body = bodies[i]; 
    for (int j = 0; j < N; ++j) {
        Body other_body = bodies[j];
        
        float dx = other_body.x - my_body.x;
        float dy = other_body.y - my_body.y;
        float dz = other_body.z - my_body.z;
        
        float distSqr = dx*dx + dy*dy + dz*dz + SOFTENING;
  
        float invDist = rsqrtf(distSqr); 
        float invDist3 = invDist * invDist * invDist;
        
        float F = G * my_body.mass * other_body.mass * invDist3;
        fx += F * dx;
        fy += F * dy;
        fz += F * dz;
    }

    bodies[i].vx += (fx / my_body.mass) * dt;
    bodies[i].vy += (fy / my_body.mass) * dt;
    bodies[i].vz += (fz / my_body.mass) * dt;
}

__global__ void updatePositions(Body* bodies, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i >= N) return;

    bodies[i].x += bodies[i].vx * dt;
    bodies[i].y += bodies[i].vy * dt;
    bodies[i].z += bodies[i].vz * dt;
}


void initBodies(vector<Body>& bodies) {
    mt19937 gen(42);
    uniform_real_distribution<float> dist(-1e9f, 1e9f);
    uniform_real_distribution<float> mass_dist(1e20f, 1e30f);
    for (auto& b : bodies) {
        b.x = dist(gen); b.y = dist(gen); b.z = dist(gen);
        b.vx = 0.0f; b.vy = 0.0f; b.vz = 0.0f;
        b.mass = mass_dist(gen);
    }
}

int main() {

    int TOTAL_BODIES = 1000000; 
    int NUM_STEPS = 10;
    size_t bytes = TOTAL_BODIES * sizeof(Body);

    cout << "Starting CUDA N-Body simulation with " << TOTAL_BODIES << " bodies..." << endl;


    vector<Body> h_bodies(TOTAL_BODIES);
    initBodies(h_bodies);

    Body* d_bodies;
    cudaMalloc(&d_bodies, bytes); 
  
    cudaMemcpy(d_bodies, h_bodies.data(), bytes, cudaMemcpyHostToDevice);


    int threadsPerBlock = 256;
    int blocksPerGrid = (TOTAL_BODIES + threadsPerBlock - 1) / threadsPerBlock;

    cudaEvent_t start, stop;
    cudaEventCreate(&start); cudaEventCreate(&stop);
    cudaEventRecord(start);

    for (int step = 0; step < NUM_STEPS; ++step) {

        calculateForces<<<blocksPerGrid, threadsPerBlock>>>(d_bodies, TOTAL_BODIES);
        

        updatePositions<<<blocksPerGrid, threadsPerBlock>>>(d_bodies, TOTAL_BODIES);
        

        cudaDeviceSynchronize(); 
    }

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    cudaMemcpy(h_bodies.data(), d_bodies, bytes, cudaMemcpyDeviceToHost);

    cout << "Simulation completed. Total GPU time: " << milliseconds / 1000.0 << " seconds." << endl;


    cudaFree(d_bodies);
    return 0;
}