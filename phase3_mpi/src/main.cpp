#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <mpi.h>

using namespace std;

const double G = 6.67430e-11;
const double SOFTENING = 1e-9;
const double dt = 0.01;

struct Body {
    double x, y, z;
    double vx, vy, vz;
    double mass;
};

void initBodies(vector<Body>& bodies) {
    mt19937 gen(42);
    uniform_real_distribution<double> dist(-1e9, 1e9);
    uniform_real_distribution<double> mass_dist(1e20, 1e30);
    
    for (auto& b : bodies) {
        b.x = dist(gen); b.y = dist(gen); b.z = dist(gen);
        b.vx = 0.0; b.vy = 0.0; b.vz = 0.0;
        b.mass = mass_dist(gen);
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    const int TOTAL_BODIES = 10000;
    const int NUM_STEPS = 10;
    const int local_N = TOTAL_BODIES / world_size;
    
    vector<Body> all_bodies(TOTAL_BODIES);

    if (world_rank == 0) {
        cout << "Starting distributed N-Body simulation on " << world_size << " nodes..." << endl;
        initBodies(all_bodies);
    }

    // Broadcast initial state to all nodes
    MPI_Bcast(all_bodies.data(), TOTAL_BODIES * sizeof(Body), MPI_BYTE, 0, MPI_COMM_WORLD);

    double start_time = MPI_Wtime();

    for (int step = 0; step < NUM_STEPS; ++step) {
        int offset = world_rank * local_N;

        // 1. Calculate forces ONLY for assigned bodies
        for (int i = offset; i < offset + local_N; ++i) {
            double fx = 0.0, fy = 0.0, fz = 0.0;
            for (int j = 0; j < TOTAL_BODIES; ++j) {
                if (i == j) continue;
                
                double dx = all_bodies[j].x - all_bodies[i].x;
                double dy = all_bodies[j].y - all_bodies[i].y;
                double dz = all_bodies[j].z - all_bodies[i].z;
                
                double distSqr = dx*dx + dy*dy + dz*dz + SOFTENING;
                double invDist = 1.0 / sqrt(distSqr);
                double invDist3 = invDist * invDist * invDist;
                
                double F = G * all_bodies[i].mass * all_bodies[j].mass * invDist3;
                fx += F * dx;
                fy += F * dy;
                fz += F * dz;
            }
            
            all_bodies[i].vx += (fx / all_bodies[i].mass) * dt;
            all_bodies[i].vy += (fy / all_bodies[i].mass) * dt;
            all_bodies[i].vz += (fz / all_bodies[i].mass) * dt;
        }

        // 2. Update positions ONLY for assigned bodies
        for (int i = offset; i < offset + local_N; ++i) {
            all_bodies[i].x += all_bodies[i].vx * dt;
            all_bodies[i].y += all_bodies[i].vy * dt;
            all_bodies[i].z += all_bodies[i].vz * dt;
        }

        // 3. Network Sync: Gather updated bodies from all nodes
        MPI_Allgather(
            MPI_IN_PLACE, 0, MPI_DATATYPE_NULL,
            all_bodies.data(), local_N * sizeof(Body), MPI_BYTE,
            MPI_COMM_WORLD
        );
    }

    double end_time = MPI_Wtime();

    if (world_rank == 0) {
        cout << "Simulation completed. Total time: " << (end_time - start_time) << " seconds." << endl;
    }

    MPI_Finalize();
    return 0;
}