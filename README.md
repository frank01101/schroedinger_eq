# Numerical simulation of the Schrödinger equation
This repository shows various methods of numerical integration of the Schrödinger equation in the positional representation

![image](https://github.com/frank01101/schroedinger_eq/assets/144745744/222397c7-6ec5-422a-b257-e9ee9afd18f9)

in either one or two dimensions with various potentials. The whole system is an infinite well, so the boundary conditions are zeros.

![Screenshot_20240625_205011](https://github.com/frank01101/schroedinger_eq/assets/144745744/8510f925-518c-451a-bec3-b3d65f7f6ff7)

![Screenshot_20240625_210029](https://github.com/frank01101/schroedinger_eq/assets/144745744/d488bff0-3afd-45dd-95a2-a195836e1fde)


## Content
### One-dimensional simulations
The code files for the one-dimensional case are `schrod_*_1d.c`. They utilize various integrating methods, including:
- `schrod_a_1d.c`: **model 1** – approximating evolution using a sort of canonical analytical solution. Rather something to start from than the generic method of numerical integration of any differential equations (I stumbled across this method in literature and just wanted to try it). Anyway, this method is ***stable*** for a reasonably small time step.
- `schrod_e_1d.c`: **model 2** – Euler's method. This method is ***unstable*** when you use any non-zero potential.
- `schrod_2s_1d.c`: **model 3** – two-step explicit method. This method is ***stable*** for a reasonable time step.
- `schrod_2s_5p_1d.c`: **model 3a** – two-step explicit method with five-point formula for Laplacian. This method is ***stable*** but has higher numerical diffusion than the previous method with the three-point formula.
- `schrod_rk4_1d.c`: **model 4** – fourth-order Runge-Kutta method. This method is crazy because of having very long expressions for coefficients, which I derived in Mathematica (the notebook is printed to `wsp_rk4.pdf` and the final formulas are in `wzory.txt` and `wzory_kopia.txt`). This method is ***stable*** for a reasonable time step.
- `schrod_lw_1d.c`: **model 5** – Lax-Wendroff method. This method has very high dispersion in this case and the solution behaves differently than the others (because it was a bit “over-engineered”) – ***unstable***.
- `schrod_cn_1d.c`: **model 6** – second-order implicit method (Crack-Nicholson) with solution of the system of equations using the Jacobi iterative method. This method is ***stable*** for the reasonable time step (e.g., when dx==1, dt<0.03).

### Two-dimensional simulations
The code files for the two-dimensional simulations are `schrod_*_2d.c`. They are the two-dimensional extensions of the successful one-dimensional models. They include:
- `schrod_a_2d.c`: **model 1** – approximating evolution using a sort of canonical analytical solution. This method is ***unstable*** for reasonable time steps (e.g., dt>0.01 with dx==1).
- `schrod_2s_2d.c`: **model 3** – two-step explicit method. This method is ***unstable*** for dt>0.01 with dx==1.
- `schrod_2s_2d_9p.c`: **model 3a** – two-step explicit method using the nine-point formula for Laplacian. Similarly to the five-point formula (model 3), this method is ***unstable*** for dt>0.01 with dx==1.
- `schrod_cn_2d.c`: **model 6** – second-order implicit method (Cranck-Nicholson) with solution of the system of equations using the Jacobi iterative method. This is the only 2D method here which is ***stable***.
- `schrod_cn2_2d.c`: **model 6a** – second-order implicit method (Cranck-Nicholson) with solution of the system of equations using the Jacobi iterative method. This is some experimental form of model 6.

### Potential generating programs
The programs which generate chosen potential are `potencjal_1d.c` and `potencjal_2d.c`, respectively, for the 1D and 2D cases.

### Initial state generating programs
The programs generating the initial states for all simulation models are:
- `schrod_init_1_1d.c`: generates one Gauss packet for the 1D case.
- `schrod_init_2_1d.c`: generates two Gauss packets for the 1D case.
- `schrod_init_2d.c`: generates one, two or three Gauss packets for the 2D case, depending on the number passed as the command-line argument `argv[1]`.

### Gnuplot scripts for running and visualizing the simulation
The scripts `run.gnu` and `run2.gnu` (for 1D and 2D, respectively) run the loops in which consecutive iterational steps of a chosen simulation model are performed and plotted. The 1D script plots the real and imaginary parts of the wave function and the probability amplitude along with the potential. The 2D script plots the probability amplitude along with the potential.

## Usage
To run the simulation, first run the compiled `potencjal_2d.out` program and, following the instructions displayed on the screen, select the appropriate potential, which will be saved in the file `potencjal_2d.dat`. Then, run Gnuplot and plot the result of compiled `schrod_init_2d.out` with the command-line argument 1, 2 or 3, indicating the number of wave packets. You are going to be interested in the 1:2:5 output columns to plot the probability amplitude. It will plot the initial state of the system and save it in the files `schrod_*_2d.dat` so that all the simulation models can use it. Finally, set the number of repetition of iterations n and run the run.gnu script which does the loop executing the chosen model of simulation until the given number of repetition is satisfied. The simulation models programs, at each iteration, read the state of the system from the `schrod_*_2d.dat` files, calculate the evolution of the system in the current time step and save the result to the same file.

So, in short, after generating the potential with `potencjal_2d.out` and saving the desired model within `run.gnu`, run Gnuplot and type, for example:
```
splot "< ./schrod_init_2d.out 3" u 1:2:5 pt -1 w pm3d
n=200
load "run.gnu"
```
This describes the usage in the two-dimensional case. For the one-dimensional models you should proceed in an analogous way.

## Discussion
The Schrödinger equation has, excluding the term with potential and the imaginary unit, similar form to the difussion equation, and the diffusion is visible in the simulation. This seems to be the manifestation of the Heisenberg's indeterminacy principle.
