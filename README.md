# Game of Life — Final Submission  
**Developer:** Robert Poore  
**Framework:** .NET / C#  
**Status:** Fully Completed – Meets All Rubric Requirements

---

##  Overview
This project is a full implementation of **Conway’s Game of Life** built as a .NET Windows Forms application using C++. The simulation renders a dynamic grid of living and dead cells that evolve according to Conway’s four canonical rules. This project fully satisfies all basic and advanced features required by the final submission rubric.

---

##  Features Implemented

###  Basic Feature Set (All Completed)
- **Interactive Grid Rendering**  
  A resizable universe that visually displays individual cells. Users may toggle cells on/off by clicking.
  
- **Simulation Controls**  
  Start, Pause, and Next controls implemented through both menu items and toolbar buttons.

- **Game Rules**  
  Full implementation of Conway’s rules:
  - Live cells with <2 neighbors die
  - Live cells with >3 neighbors die
  - Live cells with 2–3 neighbors survive
  - Dead cells with exactly 3 neighbors become alive

- **Randomization Tools**  
  Universe can be randomized via:
  - A time-based seed  
  - A user-defined seed entered through a dialog box

- **Clearing the Universe**  
  “New” or “Clear” menu options remove all live cells.

- **File Saving & Loading**  
  Supports saving universe size + living cells to a text file and loading any valid file to restore the simulation.

- **Status Bar**  
  Displays generation count and total living cells.

- **Adjustable Simulation Speed**  
  Milliseconds-per-generation can be set through a dialog box.

- **Dynamic Universe Size**  
  Users may choose the grid dimensions via a modal settings dialog.

- **Neighbor Count Display**  
  Numbers appear inside cells showing their neighbor count, toggleable through the View menu.

- **View Menu Implementation**  
  Includes toggles for:
  - Grid visibility  
  - Universe type  
  - Neighbor count  
  - Heads-up display (HUD)

---

##  Advanced Features (All Completed)
- **Customizable Colors**  
  Separate color pickers for:
  - Grid lines  
  - Background  
  - Living cells  

- **Universe Boundary Behavior**  
  User may choose:
  - **Toroidal** (wrapping edges)  
  - **Finite** (dead beyond bounds)

- **HUD System**  
  Displays:
  - Current generation  
  - Living cell count  
  - Universe type  
  - Universe size  
  - Timer interval  

- **Persistent Settings**  
  All key settings persist between sessions using .NET configuration files.  
  Includes:
  - **Reload** (load last saved settings)  
  - **Reset** (restore default values)

---

##  Technical Notes
- Written in **C++ using .NET Windows Forms**
- Settings stored using `Properties.Settings`
- Universe represented with 2D boolean arrays
- File IO uses standard `StreamReader` / `StreamWriter` workflows
- Grid uses GDI+ drawing with adjustable styling

---

##  FINAL SUBMISSION  
This project was submitted with the commit message: