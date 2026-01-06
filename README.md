# High-Performance IPC: Python & C++ Shared Memory Integration  

### Project Description  
This Proof of Concept (PoC) implements low-latency inter-process communication (IPC) using POSIX Shared Memory (SHM). The system enables a Python orchestrator and a high-performance C++ driver to share data directly, bypassing the overhead typically associated with local sockets, pipes, or message queues.  

The development is rooted in the context of industrial embedded systems (**NVIDIA Jetson Nano**), where efficient sensor data ingestion is critical for maintaining sub-millisecond response times. This work serves as a technical foundation for my transition into **high-frequency quantitative finance**, a field where I aim to apply my 6 years of personal portfolio management experience alongside high-speed software development.  

**Key Technical Highlights:**  
* **Direct Memory Access:** Integration of `shm_open` and `mmap` (C++) with Python’s `multiprocessing.shared_memory`.  
* **Resource Optimization:** Zero-copy data sharing for real-time processing.  
* **Cross-Platform Naming:** Implementation of specific naming conventions to ensure compatibility between Linux and macOS.  

---

### 🔍 Technical Insights: POSIX Naming Conventions  
A critical aspect of this PoC is handling shared memory segment names across different operating systems:  

1. **Linux:** The system requires the shared memory object name to begin with a forward slash (`/name`). This creates a node in `/dev/shm/`, allowing both the Python host and the C++ client to identify the same memory block.  
2. **macOS:** While the underlying POSIX standard is similar, the kernel handles these namespaces differently. In C++, the leading slash is mandatory for the system to correctly locate and map the resource, treating it similarly to a file path within the shared memory namespace.  

This project ensures that the C++ client correctly connects to the `/shmprueba` segment created by the Python host.  

---  

### 🛠 Tech Stack  
* **Languages:** C++ (Standard 11), Python 3.8+  
* **Operating Systems:** Linux (Ubuntu/Jetson Nano), macOS.  
* **Build System:** CMake (Multi-platform support).  

---  

### Getting Started

1. **Compile the C++ Client:**
   ```bash  
   mkdir build && cd build  
   cmake ..  
   make  
     
2. **Launch the Host (Python):**  
Note: This process must start first to create the memory segment.  
   ```bash  
   python3 host.py  

4. **Launch the Client (C++):**  
    Run this in a separate terminal.  
   ```bash
   ./cliente_cpp
