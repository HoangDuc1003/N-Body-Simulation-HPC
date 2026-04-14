#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <omp.h>//Initial libraries OPENMP to calculate 

using namespace std;

struct Body {
    double x, y, z;
    double vx, vy, vz;
    double mass;
};

const double G = 6.67430e-11;
const double dt = 0.01;
const double SOFTENING = 1e-9;

void calculateForces(vector<Body>& bodies);
void updatePositions(vector<Body>& bodies);

void initBodies(vector<Body>& bodies) {
    mt19937 gen(42);
    uniform_real_distribution<double> dist(-100.0, 100.0);
    uniform_real_distribution<double> massDist(1.0, 1e5);

    for (auto& b : bodies) {
        b.x = dist(gen); b.y = dist(gen); b.z = dist(gen);
        b.vx = 0.0; b.vy = 0.0; b.vz = 0.0;
        b.mass = massDist(gen);
    }
}

void calculateForces(vector<Body>& bodies) {
    int n = bodies.size();
    //devide for loops for CPUs free
    #pragma omp parallel for schedule(dynamic)

    for (int i = 0; i < n; ++i) {
        double fx = 0.0, fy = 0.0, fz = 0.0;
        
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            double dx = bodies[j].x - bodies[i].x;
            double dy = bodies[j].y - bodies[i].y;
            double dz = bodies[j].z - bodies[i].z;

            double distSqr = dx*dx + dy*dy + dz*dz + SOFTENING;
            double dist = sqrt(distSqr);

            double force = (G * bodies[j].mass) / (distSqr * dist);

            fx += force * dx;
            fy += force * dy;
            fz += force * dz;
        }
        
        bodies[i].vx += fx * dt;
        bodies[i].vy += fy * dt;
        bodies[i].vz += fz * dt;
    }
}

void updatePositions(vector<Body>& bodies) {
    for (auto& b : bodies) {
        b.x += b.vx * dt;
        b.y += b.vy * dt;
        b.z += b.vz * dt;
    }
}

int main() {
    int NUM_BODIES = 10000;
    int NUM_STEPS = 10;

    vector<Body> bodies(NUM_BODIES);
    initBodies(bodies);

    cout << "Starting simulation of " << NUM_BODIES << " bodies for " << NUM_STEPS << " steps..." << endl;

    double start_time = omp_get_wtime();

    for (int step = 0; step < NUM_STEPS; ++step) {
        calculateForces(bodies);
        updatePositions(bodies);
    }

    double end_time = omp_get_wtime();

    cout << "Simulation completed" << endl;
    cout << "Time to run: "<<(end_time-start_time)<<" second"<<endl;
    return 0;
}